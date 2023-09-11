#include "PQLEvaluator.h"
#include "QueryEntity.h"

#include <numeric>

PQLEvaluator::PQLEvaluator(std::shared_ptr<PkbReader> pkbReader) :pkbReader(pkbReader),
                                                                  clauseHandler(std::make_shared<ClauseHandler>(pkbReader)){}

Result PQLEvaluator::Evaluate(Query& query) {

    // TODO iterate through clauses, get Strategy Type from clause type
    // example :
    // clauseHandler->setStrategy(std::make_unique<AssignPatternStrategy>());
    // Result result;
    // clauseHandler->executeQuery(query, result);

    std::shared_ptr<QueryEntity> entity = query.getSelect()[0];
    std::vector<Entity> results = getAll(entity);
    // print results

    Result result;
    return result;
}

std::vector<Entity> PQLEvaluator::getAll(std::shared_ptr<QueryEntity> queryEntity) {
    if (queryEntity->getType() == QueryEntityType::Procedure) {
        return pkbReader->getAllProcedures();
    } else if (queryEntity->getType() == QueryEntityType::Stmt) {
        return pkbReader->getAllStatements();
    } else if (queryEntity->getType() == QueryEntityType::Assign) {
        return pkbReader->getAllAssign();
    } else if (queryEntity->getType() == QueryEntityType::Variable) {
        return pkbReader->getAllVariables();
    } else if (queryEntity->getType() == QueryEntityType::Constant) {
        return pkbReader->getAllConstants();
    }
}

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
