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
    Result result;
    // if query is a such that query
    if (!query.getSuchThat().empty()) {
        if (query.getSuchThat()[0]->getType() == ClauseType::Uses) {
            clauseHandler->setStrategy(std::make_shared<UsesSuchThatStrategy>(UsesSuchThatStrategy()));
        } else if (query.getSuchThat()[0]->getType() == ClauseType::Follows) {
            clauseHandler->setStrategy(std::make_shared<FollowsSuchThatStrategy>(FollowsSuchThatStrategy()));
        }
        clauseHandler->executeClause(query.getSuchThat()[0], result);
        if (result.getType() == ResultType::Boolean && !result.getBoolResult()) {
            return result;
        }
    }

    // if query is an assign pattern query
    if (!query.getPattern().empty()) {
        clauseHandler->setStrategy(std::make_shared<AssignPatternStrategy>(AssignPatternStrategy()));
        clauseHandler-> executeClause(query.getPattern()[0], result);
        if (result.getType() == ResultType::Boolean && !result.getBoolResult()) {
            return result;
        }
    }

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
    ResultTuples mappedEntities;
    for (const Entity& resEntity : entities) {
        std::vector<Entity> mappedEntity {resEntity};
        mappedEntities.push_back(mappedEntity);
    }
    result.setTuples(mappedEntities);
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
        default:
            throw std::runtime_error("Not supported entity type in query select clause");
    }
}
