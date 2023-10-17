#include "ResultHandler.h"

#include <unordered_set>

ResultHandler::ResultHandler(){};

std::shared_ptr<Result> ResultHandler::getCombined(std::shared_ptr<Result> r1, std::shared_ptr<Result> r2) {
    if (r1->isInvalid()) { return cast(r2); }
    if (r2->isInvalid()) { return cast(r1); }
    if (r1->isFalse() || r1->isEmpty() || r2->isTrue()) { return cast(r1); }
    if (r2->isFalse() || r2->isEmpty() || r1->isTrue()) { return cast(r2); }
    return cast(join(r1, r2));// case 2 non-empty Tuple Result
}

std::shared_ptr<Result> ResultHandler::join(std::shared_ptr<Result> r1, std::shared_ptr<Result> r2) {
    std::shared_ptr<Result> final = std::make_shared<Result>();
    ResultTuples finalTuples;

    std::unordered_map<int, int> common = getCommonColumns(r1, r2);
    SynonymMap synIndices = buildSynIndices(r1, r2);
    std::vector<Synonym> header = getHeader(synIndices);
    final->setType(header);

    auto tuples1 = r1->getTuples();
    auto tuples2 = r2->getTuples();

    for (const auto &row1: tuples1) {
        for (const auto &row2: tuples2) {
            if (isMatch(row1, row2, common)) {
                std::vector<Entity> newRow;
                auto map1 = r1->getSynIndices();
                auto map2 = r2->getSynIndices();
                for (const auto &colName: header) {
                    if (map1.count(colName)) {
                        int index = map1[colName];
                        newRow.push_back(row1[index]);
                        continue;
                    }
                    int index = map2[colName];
                    newRow.push_back(row2[index]);
                }
                finalTuples.push_back(newRow);
            }
        }
    }
    final->setTuples(finalTuples);
    return final;
}

std::unordered_map<int, int> ResultHandler::getCommonColumns(std::shared_ptr<Result> r1, std::shared_ptr<Result> r2) {
    std::unordered_map<int, int> commonIndices;
    auto map1 = r1->getSynIndices();
    auto map2 = r2->getSynIndices();

    for (auto &it: map1) {
        Synonym key = it.first;
        if (map2.count(key)) { commonIndices[map1[key]] = map2[key]; }
    }
    return commonIndices;
}

SynonymMap ResultHandler::buildSynIndices(std::shared_ptr<Result> r1, std::shared_ptr<Result> r2) {
    SynonymMap combined = r1->getSynIndices();
    SynonymMap other = r2->getSynIndices();
    int mapSize = combined.size();

    for (auto &it: other) {
        Synonym key = it.first;
        if (combined.count(key) == 0) {
            combined[it.first] = mapSize;
            mapSize += 1;
        }
    }
    return combined;
}

std::vector<Synonym> ResultHandler::getHeader(SynonymMap map) {
    std::vector<Synonym> header(map.size());
    for (auto &it: map) { header[it.second] = it.first; }
    return header;
}


bool ResultHandler::isMatch(const std::vector<Entity> &row1, const std::vector<Entity> &row2,
                            const std::unordered_map<int, int> &commons) {
    for (auto &it: commons) {
        if (row1[it.first] == row2[it.second]) { continue; }
        return false;
    }
    return true;
}

std::shared_ptr<Result> ResultHandler::cast(std::shared_ptr<Result> result) {
    if (result->isEmpty()) { return std::make_shared<Result>(false); }
    return result;
}