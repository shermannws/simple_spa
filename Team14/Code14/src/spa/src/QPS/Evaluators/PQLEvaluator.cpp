#include <numeric>
#include <stdexcept>
#include <unordered_set>

#include "PQLEvaluator.h"
#include "QPS/QueryEntity.h"
#include "Strategies/UsesSSuchThatStrategy.h"
#include "Strategies/UsesPSuchThatStrategy.h"
#include "Strategies/FollowsSuchThatStrategy.h"
#include "QPS/QPSTypes.h"
#include "Strategies/ModifiesSSuchThatStrategy.h"
#include "Strategies/ModifiesPSuchThatStrategy.h"
#include "Strategies/FollowsStarSuchThatStrategy.h"
#include "Strategies/ParentSuchThatStrategy.h"
#include "Strategies/ParentStarSuchThatStrategy.h"

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

    Result sResult;
    if (!query.getSuchThat().empty()) {
        evaluateSuchThat(query.getSuchThat()[0], sResult);
    }

    Result pResult;
    if (!query.getPattern().empty()) {
        evaluatePattern(query.getPattern()[0], pResult);
    }

    Result result = resultHandler->getCombined(sResult, pResult);

    // CASE FALSE OR EMPTY
    if ((result.getType()==ResultType::Boolean && !result.getBoolResult()) ||
        (result.getType()==ResultType::Tuples && result.getTuples().empty()) ){
        return result;
    }

    // CASE SYN IN RESULT TABLE, check if synonym in select is in result table
    Synonym syn = query.getSelect()[0]->getSynonym();
    SynonymMap indicesMap = result.getSynIndices();
    if (indicesMap.find(syn) != indicesMap.end()) {
        return result;
    }

    // CASE TRUE OR NON-EMPTY TABLE OR INVALID, evaluate select independently

    Result selectResult;
    EntityPtr entity = query.getSelect()[0];
    std::vector<Entity> entities = getAll(entity);
    selectResult.setTuples(entities);
    SynonymMap map {{entity->getSynonym(), 0}};
    selectResult.setSynIndices(map);

    return selectResult;
}

void PQLEvaluator::evaluateSuchThat(const std::shared_ptr<SuchThatClause> clause, Result& result) {
    if (clause->getType() == ClauseType::Uses && clause->getFirstParam().isStmtRef()) {
        clauseHandler->setStrategy(std::make_shared<UsesSSuchThatStrategy>(UsesSSuchThatStrategy(pkbReader)));
    } else if (clause->getType() == ClauseType::Uses && clause->getFirstParam().isEntRef()) {
        clauseHandler->setStrategy(std::make_shared<UsesPSuchThatStrategy>(UsesPSuchThatStrategy(pkbReader)));
    } else if (clause->getType() == ClauseType::Modifies && clause->getFirstParam().isStmtRef()) {
        clauseHandler->setStrategy(std::make_shared<ModifiesSSuchThatStrategy>(ModifiesSSuchThatStrategy(pkbReader)));
    } else if (clause->getType() == ClauseType::Modifies && clause->getFirstParam().isEntRef()) {
        clauseHandler->setStrategy(std::make_shared<ModifiesPSuchThatStrategy>(ModifiesPSuchThatStrategy(pkbReader)));
    } else if (clause->getType() == ClauseType::Follows) {
        clauseHandler->setStrategy(std::make_shared<FollowsSuchThatStrategy>(FollowsSuchThatStrategy(pkbReader)));
    } else if (clause->getType() == ClauseType::FollowsStar) {
        clauseHandler->setStrategy(std::make_shared<FollowsStarSuchThatStrategy>(FollowsStarSuchThatStrategy(pkbReader)));
    } else if (clause->getType() == ClauseType::Parent) {
        clauseHandler->setStrategy(std::make_shared<ParentSuchThatStrategy>(ParentSuchThatStrategy(pkbReader)));
    } else if (clause->getType() == ClauseType::ParentStar) {
        clauseHandler->setStrategy(std::make_shared<ParentStarSuchThatStrategy>(ParentStarSuchThatStrategy(pkbReader)));
    }

    clauseHandler->executeClause(clause, result);
}

void PQLEvaluator::evaluatePattern(const std::shared_ptr<PatternClause> clause, Result& result) {
    clauseHandler->setStrategy(std::make_shared<AssignPatternStrategy>(AssignPatternStrategy(pkbReader)));
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
