#include <numeric>
#include <stdexcept>

#include "PQLEvaluator.h"
#include "QPS/QueryEntity.h"
#include "QPS/QPSTypes.h"
#include "QPS/QPSUtil.h"

PQLEvaluator::PQLEvaluator(std::shared_ptr<PkbReader> pkbReader) :
    pkbReader(pkbReader),
    clauseHandler(std::make_shared<ClauseHandler>(pkbReader)),
    resultHandler(std::make_shared<ResultHandler>()) {}

ResultList PQLEvaluator::formatResult(Query& query, Result& result) {
    std::vector<Synonym> selects = query.getSelect();
    ResultSet results;

    if (result.getType() == ResultType::Tuples) {
        for (auto& tuple : result.getTuples()) {
            std::vector<std::string> tmp;
            if (tuple.empty()) {
                continue;
            }
            for (Synonym & syn : selects) {
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
    std::shared_ptr<Result> result = evaluateConstraintClauses(query);

    // CASE FALSE
    if (result->isFalse()){
        return *result;
    }

    //TRUE OR NON-EMPTY RESULT TABLE
    // CASE RESULT-CLAUSE IN RESULT TABLE, check if ALL synonym in select is in result table
    std::vector<Synonym> unevaluatedSyn = getUnevaluatedSyn(query.getSelect(), result);
    if (unevaluatedSyn.empty()){
        return *result;
    }

    // CASE SOME RESULT-CLAUSE NOT IN RESULT TABLE
    auto synResult = evaluateResultClause(query, unevaluatedSyn); // TODO project curr result first before combine?
    auto finalResult = resultHandler->getCombined(result, synResult);
    return *finalResult;

}

std::vector<Synonym> PQLEvaluator::getUnevaluatedSyn (const std::vector<Synonym> resultClause, std::shared_ptr<Result> result) {
    auto synMap = result->getSynIndices();
    std::vector<Synonym> unevaluated;
    for (auto &elem : resultClause) {
        auto syn = QPSUtil::getSyn(elem);
        if (synMap.count(syn) == 0) {
            unevaluated.push_back(syn);
        }
    }
    return unevaluated;
}

std::shared_ptr<Result> PQLEvaluator::evaluateClause(const std::shared_ptr<Clause> clause) {
    std::shared_ptr<Strategy> strategy = QPSUtil::strategyCreatorMap[clause->getType()](pkbReader);
    clauseHandler->setStrategy(strategy);
    std::shared_ptr<Result> result = clauseHandler->executeClause(clause);
    return result;
}

std::shared_ptr<Result> PQLEvaluator::evaluateConstraintClauses(const Query& query) {
    auto result = std::make_shared<Result>(true); // Initialize with TRUE
    if (query.getSuchThat().empty() && query.getPattern().empty()) {
        return result;
    }

    std::vector<std::shared_ptr<Result>> results;
    for (const auto& clause : query.getSuchThat()) {
        results.push_back(evaluateClause(clause));
    }
    for (const auto& clause : query.getPattern()) {
        results.push_back(evaluateClause(clause));
    }
    for (auto const &res: results) { // Combine until end of list
        result = resultHandler->getCombined(result, res);
    }
    return result;
}

std::shared_ptr<Result> PQLEvaluator::evaluateSelect(const std::shared_ptr<QueryEntity> entity) {
    std::shared_ptr<Result> result = std::make_shared<Result>();
    result->setType({entity->getSynonym()});
    result->setTuples(getAll(entity));
    return result;
}

std::shared_ptr<Result> PQLEvaluator::evaluateResultClause(const Query& query, std::vector<Synonym> resultSyns) {
    std::vector<std::shared_ptr<Result>> results;
    for (auto &syn : resultSyns) {
        results.push_back(evaluateSelect(query.getEntity(syn)));
    }
    auto tupleResult = std::make_shared<Result>(true); // Initialize with TRUE
    for (auto const &res: results) { // Combine until end of list
        tupleResult = resultHandler->getCombined(tupleResult, res);
    }
    return tupleResult;
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
        case QueryEntityType::Call:
            return pkbReader->getAllCall();
        default:
            throw std::runtime_error("Not supported entity type in query select clause");
    }
}
