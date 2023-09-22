#include <numeric>
#include <stdexcept>
#include <unordered_set>

#include "PQLEvaluator.h"
#include "QueryEntity.h"
#include "UsesSuchThatStrategy.h"
#include "FollowsSuchThatStrategy.h"
#include "QPSTypes.h"

PQLEvaluator::PQLEvaluator(std::shared_ptr<PkbReader> pkbReader) :pkbReader(pkbReader),clauseHandler(std::make_shared<ClauseHandler>(pkbReader)){}

ResultList PQLEvaluator::formatResult(Query& query, Result& result) {
    std::vector<EntityPtr> selects = query.getSelect();
    ResultSet results;

    if (result.getType() == ResultType::Tuples) {
        for (auto& tuple : result.getTuples()) {
            std::vector<std::string> tmp;
            if (tuple.empty()) {
                continue;
            }
            for (EntityPtr & entity : selects) {
                Synonym syn = entity->getSynonym();
                SynonymMap indicesMap = result.getSynIndices();
                if (indicesMap.find(syn) != indicesMap.end()) {
                    int idx = indicesMap.at(syn);
                    std::string value = *tuple[idx].getEntityValue();
                    tmp.emplace_back(value);
                }
            }
            FormattedResult concat = std::accumulate(tmp.begin(), tmp.end(), std::string(),
                                                 [](std::string& a, const std::string& b) {
                                                     return a += (a.empty() ? "" : " ") + b;
                                                 }); // handles formatting of more than two variables in select clause
            if (!concat.empty() && results.find(concat) == results.end()) {
                results.insert(concat);
            }
        }
    }
    ResultList list_results(results.begin(),results.end());
    return list_results;
}

Result PQLEvaluator::evaluate(Query& query) {
    Result sResult;
    // if query is a such that query
    if (!query.getSuchThat().empty()) {
        if (query.getSuchThat()[0]->getType() == ClauseType::Uses) {
            clauseHandler->setStrategy(std::make_shared<UsesSuchThatStrategy>(UsesSuchThatStrategy()));
        } else if (query.getSuchThat()[0]->getType() == ClauseType::Follows) {
            clauseHandler->setStrategy(std::make_shared<FollowsSuchThatStrategy>(FollowsSuchThatStrategy()));
        }
        clauseHandler->executeClause(query.getSuchThat()[0], sResult);
        if (sResult.getType() == ResultType::Boolean && !sResult.getBoolResult()) {
            return sResult;
        }
    }

    Result pResult;
    // if query is an assign pattern query
    if (!query.getPattern().empty()) {
        clauseHandler->setStrategy(std::make_shared<AssignPatternStrategy>(AssignPatternStrategy()));
        clauseHandler-> executeClause(query.getPattern()[0], pResult);
        if (pResult.getType() == ResultType::Boolean && !pResult.getBoolResult()) {
            return pResult;
        }
    }

    Result result = getCombined(sResult, pResult);

    // check if synonym in select is in result
//     ASSUMES ONLY ONE SELECT VARIABLE RETURNED
    Synonym syn = query.getSelect()[0]->getSynonym();
    SynonymMap indicesMap = result.getSynIndices();
    if (indicesMap.find(syn) != indicesMap.end()) {
        return result;
    }

    // else query is just select
    EntityPtr entity = query.getSelect()[0];
    std::vector<Entity> entities = getAll(entity);

    // set Result fields
    result.setTuples(entities);
    ResultType type = ResultType::Tuples;
    result.setType(type);
    SynonymMap map {{entity->getSynonym(), 0}};
    result.setSynIndices(map);

    return result;
}

std::vector<Entity> PQLEvaluator::getAll(const std::shared_ptr<QueryEntity>& queryEntity) {
    QueryEntityType entityType = queryEntity->getType();
    switch (entityType) {
        case QueryEntityType::Procedure:
            return pkbReader->getAllProcedures();
        case QueryEntityType::Stmt:
            return pkbReader->getAllStatements();
        case QueryEntityType::Assign:
            return pkbReader->getAllAssign();
        case QueryEntityType::Variable:
            return pkbReader->getAllVariables();
        case QueryEntityType::Constant:
            return pkbReader->getAllConstants();
        case QueryEntityType::While:
            return pkbReader->getAllWhile();
        case QueryEntityType::If:
            return pkbReader->getAllIf();
        case QueryEntityType::Read:
            return pkbReader->getAllRead();
        case QueryEntityType::Print:
            return pkbReader->getAllPrint();
        default:
            throw std::runtime_error("Not supported entity type in query select clause");
    }
}

Result PQLEvaluator::getCombined(Result& r1, Result& r2) {
    if (r1.getType() == ResultType::Invalid) {
        return r2;
    }
    if (r2.getType() == ResultType::Invalid) {
        return r1;
    }
    if (r1.getType() == ResultType::Boolean && r1.getBoolResult()) {
        return r2;
    }
    if (r1.getType() == ResultType::Boolean && !r1.getBoolResult()) {
        return r1;
    }
    if (r2.getType() == ResultType::Boolean && r2.getBoolResult()) {
        return r1;
    }
    if (r2.getType() == ResultType::Boolean && !r2.getBoolResult()) {
        return r2;
    }

    return join(r1, r2);
}


Result PQLEvaluator::join(Result& r1, Result& r2) {
    Result final;
    ResultTuples finalTuples;

    // find common columns
    std::unordered_map<int, int> common = getCommonColumns(r1, r2);
    SynonymMap synIndices = buildSynIndices(r1, r2);
    std::vector<Synonym> header = getHeader(synIndices);
    final.setSynIndices(synIndices);

    auto tuples1 = r1.getTuples();
    auto tuples2 = r2.getTuples();

    for (const auto& row1 : tuples1){
        for (const auto& row2 : tuples2) {
            if (isMatch(row1, row2, common)){
                //build row and add to final's tuples
                std::vector<Entity> newRow;
                auto map1 = r1.getSynIndices();
                auto map2 = r2.getSynIndices();
                for (const auto& colName : header) {
                    if (map1.count(colName)){ //if found in r1, add to vector
                        int index = map1[colName];
                        newRow.push_back(row1[index]);
                        continue;
                    }
                    //add from r2
                    int index = map2[colName];
                    newRow.push_back(row2[index]);
                }
                finalTuples.push_back(newRow);
            }
        }
    }
    final.setTuples(finalTuples);
    ResultType type = ResultType::Tuples;
    final.setType(type);
    return final;
}


// returns mapping of {index in r1: index in r2} for common cols
std::unordered_map<int, int> PQLEvaluator::getCommonColumns(Result& r1, Result& r2) {
    std::unordered_map<int, int> commonIndices;
    auto map1 = r1.getSynIndices();
    auto map2 = r2.getSynIndices();

    for (auto& it: map1) {
        Synonym key = it.first;
        if (map2.count(key)) {
            commonIndices[map1[key]] = map2[key];
        }

    }
    return commonIndices;
}

// get combined synIndices
SynonymMap PQLEvaluator::buildSynIndices(Result& r1, Result& r2) {
    SynonymMap combined = r1.getSynIndices();
    SynonymMap other = r2.getSynIndices();
    int mapSize = combined.size();

    for (auto& it: other) {
        Synonym key = it.first;
        if (combined.count(key) == 0) {
           combined[it.first] = mapSize;
           mapSize += 1;
        }
    }
    return combined;
}

std::vector<Synonym> PQLEvaluator::getHeader(SynonymMap map) {
    std::vector<Synonym> header(map.size());
    for (auto& it: map) {
        header[it.second] = it.first;
    }
    return header;
}


bool PQLEvaluator::isMatch(const std::vector<Entity>& row1,
                           const std::vector<Entity>& row2,
                           const std::unordered_map<int, int>& commons) {
    for (auto& it: commons) {
        if (row1[it.first] == row2[it.second]){
            continue;
        }
        return false;
    }
    return true;
}