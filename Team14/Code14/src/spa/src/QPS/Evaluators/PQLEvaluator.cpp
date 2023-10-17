#include <numeric>
#include <stdexcept>

#include "PQLEvaluator.h"
#include "QPS/QPSTypes.h"
#include "QPS/QPSUtil.h"
#include "QPS/QueryEntity.h"

PQLEvaluator::PQLEvaluator(std::shared_ptr<PkbReader> pkbReader)
        : pkbReader(pkbReader), clauseHandler(std::make_shared<ClauseHandler>(pkbReader)),
          resultHandler(std::make_shared<ResultHandler>()) {}

ResultList PQLEvaluator::formatResult(Query &query, Result &result) {
    std::vector<Synonym> selects = query.getSelect();
    ResultSet results;

    if (result.getType() == ResultType::Tuples) {
        for (auto &tuple: result.getTuples()) {
            std::vector<std::string> tmp;
            if (tuple.empty()) { continue; }
            for (Synonym &syn: selects) {
                SynonymMap indicesMap = result.getSynIndices();
                if (indicesMap.find(syn) != indicesMap.end()) {
                    int idx = indicesMap.at(syn);
                    std::string value = tuple[idx].getEntityValue();
                    tmp.emplace_back(value);
                }
            }
            FormattedResult concat =
                    std::accumulate(tmp.begin(), tmp.end(), std::string(), [](std::string &a, const std::string &b) {
                        return a += (a.empty() ? "" : " ") + b;
                    });// handles formatting of more than two variables in select clause

            if (!concat.empty() && results.find(concat) == results.end()) { results.insert(concat); }
        }
    }
    ResultList list_results(results.begin(), results.end());
    return list_results;
}

Result PQLEvaluator::evaluate(Query &query) {
    std::shared_ptr<Result> result = evaluateConstraintClauses(query);
    if (!result) {
        result = evaluateSelect(query);
        return *result;
    }

    // CASE FALSE
    if (result->isFalse()) { return *result; }

    // CASE SYN IN RESULT TABLE, check if synonym in select is in result table
    Synonym syn = query.getSelect()[0];
    SynonymMap indicesMap = result->getSynIndices();
    if (indicesMap.find(syn) != indicesMap.end()) { return *result; }

    // CASE TRUE OR NON-EMPTY TABLE, evaluate select independently
    result = evaluateSelect(query);
    return *result;
}

std::shared_ptr<Result> PQLEvaluator::evaluateClause(const std::shared_ptr<Clause> clause) {
    std::shared_ptr<Strategy> strategy = QPSUtil::strategyCreatorMap[clause->getType()](pkbReader);
    clauseHandler->setStrategy(strategy);
    std::shared_ptr<Result> result = clauseHandler->executeClause(clause);
    return result;
}

std::shared_ptr<Result> PQLEvaluator::evaluateConstraintClauses(const Query &query) {
    if (query.getSuchThat().empty() && query.getPattern().empty()) { return nullptr; }

    std::vector<std::shared_ptr<Result>> results;
    for (const auto &clause: query.getSuchThat()) { results.push_back(evaluateClause(clause)); }
    for (const auto &clause: query.getPattern()) { results.push_back(evaluateClause(clause)); }
    auto result = resultHandler->cast(results[0]);// Initialize with the first element
    for (size_t i = 1; i < results.size(); ++i) { // Combine with next until end of list
        result = resultHandler->getCombined(result, results[i]);
    }
    return result;
}

std::shared_ptr<Result> PQLEvaluator::evaluateSelect(const Query &query) {
    std::shared_ptr<Result> result = std::make_shared<Result>();
    result->setType(query.getSelect());

    Synonym selectSyn = query.getSelect()[0];
    std::shared_ptr<QueryEntity> entity = query.getEntity(selectSyn);
    result->setTuples(getAll(entity));

    return result;
}

std::vector<Entity> PQLEvaluator::getAll(const std::shared_ptr<QueryEntity> &queryEntity) {
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
        case QueryEntityType::Call:
            return pkbReader->getAllCall();
        default:
            throw std::runtime_error("Not supported entity type in query select clause");
    }
}
