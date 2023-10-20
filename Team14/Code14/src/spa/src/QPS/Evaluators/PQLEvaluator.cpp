#include <numeric>
#include <stdexcept>

#include "PQLEvaluator.h"
#include "QPS/QPSTypes.h"
#include "QPS/QPSUtil.h"
#include "QPS/QueryEntity.h"

using transformFunc = std::function<std::string(Entity &)>;

PQLEvaluator::PQLEvaluator(std::shared_ptr<PkbReader> pkbReader)
    : pkbReader(pkbReader), clauseHandler(std::make_shared<ClauseHandler>(pkbReader)),
      resultHandler(std::make_shared<ResultHandler>()) {}


ResultList PQLEvaluator::formatResult(Query &query, Result &result) {
    std::vector<Synonym> selects = query.getSelect();

    if (selects.empty()) {// case BOOLEAN query
        if (result.isFalse() || result.isEmpty()) { return ResultList{"FALSE"}; }
        return ResultList{"TRUE"};
    }

    // case tuple query
    SynonymMap indicesMap = result.getSynIndices();
    ResultSet results;
    auto transformations = getTransformations(indicesMap, selects);
    for (auto &tuple: result.getTuples()) {
        auto tmp = project(tuple, transformations);
        auto formattedResult = concat(tmp);
        if (!formattedResult.empty()) { results.insert(formattedResult); }
    }
    ResultList list_results(results.begin(), results.end());
    return list_results;
}

std::vector<std::pair<int, transformFunc>> PQLEvaluator::getTransformations(SynonymMap inputMap,
                                                                            std::vector<Synonym> resultClause) {
    std::vector<std::pair<int, transformFunc>> transformations;
    for (Synonym &elem: resultClause) {
        auto attrName = QPSUtil::getAttrName(elem);
        std::pair<int, transformFunc> transformation;
        if (attrName.empty()) {// case synonym
            transformation.first = inputMap[elem];
            transformation.second = [](Entity &ent) { return ent.getEntityValue(); };
        } else {                             // case attrRef
            auto syn = QPSUtil::getSyn(elem);// get Syn without attrName
            transformation.first = inputMap[syn];
            transformation.second = QPSUtil::getValueFunc[QPSUtil::strToAttrNameMap[attrName]];
        }
        transformations.push_back(transformation);
    }
    return transformations;
}

std::vector<std::string> PQLEvaluator::project(std::vector<Entity> row,
                                               std::vector<std::pair<int, transformFunc>> transformations) {
    std::vector<std::string> projection;
    for (auto &elem: transformations) {
        auto result = elem.second(row[elem.first]);
        projection.push_back(result);
    }
    return projection;
}

std::string PQLEvaluator::concat(std::vector<std::string> strings) {
    auto result = std::accumulate(strings.begin(), strings.end(), std::string(),
                                  [](std::string &a, const std::string &b) { return a += (a.empty() ? "" : " ") + b; });
    return result;
}

Result PQLEvaluator::evaluate(Query &query) {
    std::shared_ptr<Result> result = evaluateConstraintClauses(query);

    // CASE FALSE
    if (result->isFalse()) { return *result; }

    // TRUE OR NON-EMPTY RESULT TABLE
    //  CASE RESULT-CLAUSE IN RESULT TABLE, check if ALL synonym in select is in result table
    std::vector<Synonym> unevaluatedSyn = getUnevaluatedSyn(query.getSelect(), result);
    if (unevaluatedSyn.empty()) { return *result; }

    // CASE SOME RESULT-CLAUSE NOT IN RESULT TABLE
    auto synResult = evaluateResultClause(query, unevaluatedSyn);
    auto finalResult = resultHandler->getCombined(result, synResult);
    return *finalResult;
}

std::vector<Synonym> PQLEvaluator::getUnevaluatedSyn(const std::vector<Synonym> resultClause,
                                                     std::shared_ptr<Result> result) {
    auto synMap = result->getSynIndices();
    std::vector<Synonym> unevaluated;
    for (auto &elem: resultClause) {
        auto syn = QPSUtil::getSyn(elem);
        if (!synMap.count(syn)) { unevaluated.push_back(syn); }
    }
    return unevaluated;
}

std::shared_ptr<Result> PQLEvaluator::evaluateClause(const std::shared_ptr<Clause> clause) {
    std::shared_ptr<Strategy> strategy = QPSUtil::strategyCreatorMap[clause->getType()](pkbReader);
    clauseHandler->setStrategy(strategy);
    std::shared_ptr<Result> result = clauseHandler->executeClause(clause);
    return result;
}

std::shared_ptr<Result> PQLEvaluator::evaluateConstraintClauses(const Query &query) {
    auto result = std::make_shared<Result>(true);// Initialize with TRUE
    if (query.getSuchThat().empty() && query.getPattern().empty() && query.getWith().empty()) { return result; }

    std::vector<std::shared_ptr<Result>> results;
    for (const auto &clause: query.getSuchThat()) { results.push_back(evaluateClause(clause)); }
    for (const auto &clause: query.getPattern()) { results.push_back(evaluateClause(clause)); }
    for (const auto &clause: query.getWith()) { results.push_back(evaluateClause(clause)); }
    for (auto const &res: results) {// Combine until end of list
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

std::shared_ptr<Result> PQLEvaluator::evaluateResultClause(const Query &query, std::vector<Synonym> resultSyns) {
    std::vector<std::shared_ptr<Result>> results;
    for (auto &syn: resultSyns) { results.push_back(evaluateSelect(query.getEntity(syn))); }
    auto tupleResult = std::make_shared<Result>(true);// Initialize with TRUE
    for (auto const &res: results) {                  // Combine until end of list
        tupleResult = resultHandler->getCombined(tupleResult, res);
    }
    return tupleResult;
}

std::vector<Entity> PQLEvaluator::getAll(const std::shared_ptr<QueryEntity> &queryEntity) {
    QueryEntityType entityType = queryEntity->getType();
    if (QPSUtil::entityGetterMap.find(entityType) == QPSUtil::entityGetterMap.end()) {
        throw std::runtime_error("Not supported entity type in query select clause");
    }
    return QPSUtil::entityGetterMap[entityType](pkbReader);
}
