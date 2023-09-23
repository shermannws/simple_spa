#include <numeric>
#include <stdexcept>
#include <unordered_set>

#include "PQLEvaluator.h"
#include "QueryEntity.h"
#include "UsesSuchThatStrategy.h"
#include "FollowsSuchThatStrategy.h"
#include "QPSTypes.h"

PQLEvaluator::PQLEvaluator(std::shared_ptr<PkbReader> pkbReader) :
    pkbReader(pkbReader),
    clauseHandler(std::make_shared<ClauseHandler>(pkbReader)),
    resultHandler(std::make_shared<ResultHandler>()) {}

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

    // if query has Such that Clause
    Result sResult;
    if (!query.getSuchThat().empty()) {
        evaluateSuchThat(query.getSuchThat()[0], sResult);
        if (sResult.getType() == ResultType::Boolean && !sResult.getBoolResult()) {
            return sResult;
        }
    }

    // if query is an assign pattern query
    Result pResult;
    if (!query.getPattern().empty()) {
        evaluatePattern(query.getPattern()[0], pResult);
        if (pResult.getType() == ResultType::Boolean && !pResult.getBoolResult()) {
            return pResult;
        }
    }

    Result result = resultHandler->getCombined(sResult, pResult);

    // CASE EMPTY TABLE terminate early
    if (result.getType()==ResultType::Tuples && result.getTuples().empty()) {
        return result; //OR do we need to return a FALSE result?
    }

    // CASE NON-EMPTY TABLE, check if synonym in select is in result table
    Synonym syn = query.getSelect()[0]->getSynonym();
    SynonymMap indicesMap = result.getSynIndices();
    if (indicesMap.find(syn) != indicesMap.end()) { //if yes, return
        return result;
    }

    // CASE BOOLEAN TRUE OR NON-EMPTY TABLE, evaluate select independently

    // else query is just select
    Result selectResult;
    EntityPtr entity = query.getSelect()[0];
    std::vector<Entity> entities = getAll(entity);

    // set Result fields
    selectResult.setTuples(entities);
    SynonymMap map {{entity->getSynonym(), 0}};
    selectResult.setSynIndices(map);

    return selectResult;
}

void PQLEvaluator::evaluateSuchThat(const std::shared_ptr<SuchThatClause> clause, Result& result) {
    if (clause->getType() == ClauseType::Uses) {
        clauseHandler->setStrategy(std::make_shared<UsesSuchThatStrategy>(UsesSuchThatStrategy()));
    } else if (clause->getType() == ClauseType::Follows) {
        clauseHandler->setStrategy(std::make_shared<FollowsSuchThatStrategy>(FollowsSuchThatStrategy()));
    }
    clauseHandler->executeClause(clause, result);
}

void PQLEvaluator::evaluatePattern(const std::shared_ptr<PatternClause> clause, Result& result) {
    clauseHandler->setStrategy(std::make_shared<AssignPatternStrategy>(AssignPatternStrategy()));
    clauseHandler-> executeClause(clause, result);
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
