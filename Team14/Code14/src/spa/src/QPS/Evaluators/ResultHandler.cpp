#include "ResultHandler.h"

#include <unordered_set>

ResultHandler::ResultHandler() = default;

std::shared_ptr<Result> ResultHandler::getCombined(std::shared_ptr<Result> r1, std::shared_ptr<Result> r2) {
    if (r1->isInvalid()) { return cast(r2); }
    if (r2->isInvalid()) { return cast(r1); }
    if (r1->isFalse() || r1->isEmpty() || r2->isTrue()) { return cast(r1); }
    if (r2->isFalse() || r2->isEmpty() || r1->isTrue()) { return cast(r2); }
    return cast(join(r1, r2));// case 2 non-empty Tuple Result
}

std::shared_ptr<Result> ResultHandler::getDiff(std::shared_ptr<Result> r1, std::shared_ptr<Result> r2) {
    auto mainSet = r1->getTuples();
    auto minusSet = r2->getTuples();

    if (r1->getSynIndices() == r2->getSynIndices()) {// if columns match exactly, remove in-place
        for (const auto &tuple: minusSet) { r1->getTuples().erase(tuple); }
    } else {
        auto commonSyns = r2->getHeader();
        auto keyIndices = getKeyIndices(commonSyns, r1);

        ResultTuples filteredSet;
        for (auto &tuple: mainSet) {
            std::vector<EntityPointer> key;
            for (const auto &idx: keyIndices) { key.push_back(tuple[idx]); }        // build hash key
            if (minusSet.find(key) == minusSet.end()) { filteredSet.insert(tuple); }// add if not in minusSet
        }
        r1->setTuples(filteredSet);
    }
    return cast(r1);
}

std::shared_ptr<Result> ResultHandler::project(std::shared_ptr<Result> result, std::vector<Synonym> projection) {
    if (projection.empty()) { return cast(result); }

    auto res = std::make_shared<Result>(projection);

    std::vector<idx> indices;
    indices.reserve(projection.size());
    for (auto &syn: projection) { indices.push_back(result->getSynIndices()[syn]); }

    std::unordered_set<ResultTuple> projectedTuples;
    auto tuples = result->getTuples();
    for (const auto tuple: tuples) {
        ResultTuple projectedTuple;
        projectedTuple.reserve(projection.size());
        for (auto idx: indices) { projectedTuple.push_back(tuple[idx]); }
        projectedTuples.insert(projectedTuple);
    }
    res->setTuples(projectedTuples);
    return res;
}

std::shared_ptr<Result> ResultHandler::join(std::shared_ptr<Result> r1, std::shared_ptr<Result> r2) {
    auto synLists = getSynonyms(r1, r2);
    auto commonSyns = synLists.first;
    auto header = synLists.second;

    if (commonSyns.empty()) { return nestedLoopJoin(r1, r2, header); }
    return hashJoin(r1, r2, header, commonSyns);
}

std::shared_ptr<Result> ResultHandler::hashJoin(std::shared_ptr<Result> r1, std::shared_ptr<Result> r2,
                                                std::vector<Synonym> &header, std::vector<Synonym> &commonSyns) {
    std::shared_ptr<Result> finalResult = std::make_shared<Result>(header);
    std::unordered_set<ResultTuple> finalTuples;

    // build hashtable
    auto hashtable = partition(commonSyns, r1);

    RowTemplate rowTemplate = getRowTemplate(r1, r2, header);

    auto keyIndices = getKeyIndices(commonSyns, r2);
    auto tuples2 = r2->getTuples();
    // probe
    for (auto &row2: tuples2) {
        ResultTuple key;
        for (const auto &idx: keyIndices) { key.push_back(row2[idx]); }// build hash key

        if (!hashtable.count(key)) { continue; }// skip if no matching bucket

        auto tuples1 = hashtable[key];
        for (const auto &row1: tuples1) { finalTuples.insert(buildRow(rowTemplate, row1, row2)); }
    }
    finalResult->setTuples(finalTuples);

    return finalResult;
}

std::shared_ptr<Result> ResultHandler::nestedLoopJoin(std::shared_ptr<Result> r1, std::shared_ptr<Result> r2,
                                                      std::vector<Synonym> &header) {
    std::shared_ptr<Result> finalResult = std::make_shared<Result>(header);
    std::unordered_set<ResultTuple> finalTuples;

    auto tuples1 = r1->getTuples();
    auto tuples2 = r2->getTuples();
    RowTemplate rowTemplate = getRowTemplate(r1, r2, header);

    for (const auto &row1: tuples1) {
        for (const auto &row2: tuples2) { finalTuples.insert(buildRow(rowTemplate, row1, row2)); }
    }
    finalResult->setTuples(finalTuples);

    return finalResult;
}

std::pair<std::vector<Synonym>, std::vector<Synonym>> ResultHandler::getSynonyms(std::shared_ptr<Result> r1,
                                                                                 std::shared_ptr<Result> r2) {
    auto map1 = r1->getSynIndices();
    auto map2 = r2->getSynIndices();
    std::vector<Synonym> commonSyns;
    std::vector<Synonym> finalSyns;

    for (auto &it: map1) {
        Synonym key = it.first;
        finalSyns.push_back(key);
        if (map2.count(key)) { commonSyns.push_back(key); }
    }
    for (auto &it: map2) {
        Synonym key = it.first;
        if (!map1.count(key)) { finalSyns.push_back(key); }
    }
    return {commonSyns, finalSyns};
}

RowTemplate ResultHandler::getRowTemplate(std::shared_ptr<Result> r1, std::shared_ptr<Result> r2,
                                          const std::vector<Synonym> &header) {
    auto map1 = r1->getSynIndices();
    auto map2 = r2->getSynIndices();
    RowTemplate rowTemplate;
    for (const auto &column: header) {
        if (map1.count(column)) {
            rowTemplate.emplace_back(std::make_pair(0, map1[column]));
            continue;
        }
        rowTemplate.emplace_back(std::make_pair(1, map2[column]));
    }
    return rowTemplate;
}

ResultTuple ResultHandler::buildRow(const RowTemplate &temp, const ResultTuple &row1, const ResultTuple &row2) {
    std::vector<ResultTuple> src = {row1, row2};
    ResultTuple newRow;
    for (const auto &idx: temp) { newRow.push_back(src[idx.first][idx.second]); }
    return newRow;
}

std::vector<idx> ResultHandler::getKeyIndices(std::vector<Synonym> &synonyms, std::shared_ptr<Result> result) {
    auto synMap = result->getSynIndices();
    std::vector<idx> keyIndices(synonyms.size());
    for (int i = 0; i < synonyms.size(); i++) { keyIndices[i] = synMap[synonyms[i]]; }
    return keyIndices;
}


hashTable ResultHandler::partition(std::vector<Synonym> &synonyms, std::shared_ptr<Result> result) {
    auto keyIndices = getKeyIndices(synonyms, result);
    auto rows = result->getTuples();
    hashTable buckets;
    for (const auto &row: rows) {
        ResultTuple key;
        for (const auto &idx: keyIndices) {// build key of join attributes
            key.push_back(row[idx]);
        }
        buckets[key].insert(row);
    }
    return buckets;
}

std::shared_ptr<Result> ResultHandler::cast(std::shared_ptr<Result> result) {
    if (result->isEmpty()) { return std::make_shared<Result>(false); }
    return result;
}