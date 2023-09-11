#include "PQLEvaluator.h"
#include "QueryEntity.h"

#include <numeric>

// PQLEvaluator::PQLEvaluator() {}
PQLEvaluator::PQLEvaluator(std::shared_ptr<PkbReader> pkbReader) :pkbReader(pkbReader),clauseHandler(std::make_shared<ClauseHandler>(pkbReader)){}

std::list<std::string> PQLEvaluator::formatResult(Query& query, Result& result) {
    std::vector<std::shared_ptr<QueryEntity>> selects = query.getSelect();
    std::list<std::string> results;
    // TODO: add formatter for ResultType::Boolean

    if (result.getType() == ResultType::Tuples) {
        for (auto & tuple_ptr : result.getTuples()) { // tuple_ptr is std::shared_ptr<std::vector<std::shared_ptr<Entity>>>
            std::vector<std::string> tmp;
            for (auto & entity : selects) {
                std::string syn = entity->getSynonym();
                std::unordered_map<std::string, int> indicesMap = result.getSynIndices();
                if (indicesMap.find(syn) != indicesMap.end()) {
                    int idx = indicesMap.at(syn);
                    std::string value = (*(*tuple_ptr)[idx]->getEntityValue());
                    tmp.push_back(value);
                }
            }
            std::string concat = std::accumulate(tmp.begin(), tmp.end(), std::string(),
                                                 [](std::string& a, const std::string& b) {
                                                     return a += (a.empty() ? "" : " ") + b;
                                                 }); // handles formatting of more than two variables in select clause
            if (!concat.empty()) {
                results.push_back(concat);
            }
        }
    }
    return results;
}

Result PQLEvaluator::evaluate(Query& query) {

    // TODO iterate through clauses, get Strategy Type from clause type
    // example :
    // clauseHandler->setStrategy(std::make_unique<AssignPatternStrategy>());
    // Result result;
    // clauseHandler->executeQuery(query, result);

    std::shared_ptr<QueryEntity> entity = query.getSelect()[0];
    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> entities = getAll(entity);

    // set Result fields
    Result result = Result();
    std::vector<std::shared_ptr<std::vector<std::shared_ptr<Entity>>>> mappedEntities;
    for (const auto& entityPtr : *entities) {
        auto mappedEntity = std::make_shared<std::vector<std::shared_ptr<Entity>>>();
        mappedEntity->push_back(entityPtr);
        mappedEntities.push_back(mappedEntity);
    }
    result.setTuples(mappedEntities);
    ResultType type = ResultType::Tuples;
    result.setType(type);
    std::unordered_map<std::string, int> map {{entity->getSynonym(), 0}};
    result.setSynIndices(map);

    return result;
}

std::shared_ptr<std::vector<std::shared_ptr<Entity>>> PQLEvaluator::getAll(std::shared_ptr<QueryEntity> queryEntity) {
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
        default:
            throw std::runtime_error("Not supported entity type in query select clause");
    }
    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> results;
    return results;
}
