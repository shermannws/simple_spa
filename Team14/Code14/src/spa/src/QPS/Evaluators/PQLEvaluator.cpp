#include <numeric>
#include <queue>
#include <stdexcept>

#include "PQLEvaluator.h"
#include "QPS/QPSTypes.h"
#include "QPS/QPSUtil.h"
#include "QPS/QueryEntity.h"
#include "QPSOptimizer.h"

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
            transformation.second = [](auto ent) { return ent->getEntityValue(); };
        } else {                             // case attrRef
            auto syn = QPSUtil::getSyn(elem);// get Syn without attrName
            transformation.first = inputMap[syn];
            transformation.second = QPSUtil::getValueFunc[QPSUtil::strToAttrNameMap[attrName]];
        }
        transformations.push_back(transformation);
    }
    return transformations;
}

std::vector<std::string> PQLEvaluator::project(ResultTuple row,
                                               std::vector<std::pair<int, transformFunc>> &transformations) {
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

bool PQLEvaluator::evaluateBooleanGroup(const std::vector<std::shared_ptr<Clause>> &clauses) {
    for (auto &clause: clauses) {
        auto res = evaluateClause(clause);
        if (clause->isNegation()) { res->setBoolResult(!res->getBoolResult()); }
        if (res->isFalse()) { return false; }
    }
    return true;
}

bool PQLEvaluator::evaluateIrrelevantGroup(const std::vector<std::shared_ptr<Clause>> &clauses) {
    auto tmp = std::make_shared<Result>(true);
    for (auto &clause: clauses) {
        auto clauseRes = evaluateClause(clause);
        if (clause->isNegation()) {
            tmp = evaluateNegation(tmp, clauseRes);
        } else {
            tmp = resultHandler->getCombined(tmp, clauseRes);
        }
        if (tmp->isFalse()) { return false; }
    }
    return true;
}

Result PQLEvaluator::evaluate(Query &query) {
    setDeclarationMap(query);
    auto pairs = QPSOptimizer::getGroupScorePairs(query);
    std::priority_queue pq(pairs.begin(), pairs.end(), QPSOptimizer::compareGroupByScore);

    auto res = std::make_shared<Result>(true);
    while (!pq.empty()) {
        auto pair = pq.top();
        pq.pop();
        std::vector<std::shared_ptr<Clause>> group(pair.first.begin(), pair.first.end());
        if (!std::get<1>(pair.second)) {// no synonyms
            if (!evaluateBooleanGroup(group)) { return Result(false); }
        } else if (!std::get<0>(pair.second)) {// group with irrelevant synonyms
            group = QPSOptimizer::sortClauses(group);
            if (!evaluateIrrelevantGroup(group)) { return Result(false); }
        } else {// those with selectSyns (and if select has synonym(s)
            group = QPSOptimizer::sortClauses(group);
            for (auto &clause: group) {
                auto clauseRes = evaluateClause(clause);
                if (clause->isNegation()) {
                    res = evaluateNegation(res, clauseRes);
                } else {
                    res = resultHandler->getCombined(res, clauseRes);
                }
                if (res->isFalse()) { return Result(false); }
            }
        }
    }

    //  CASE RESULT-CLAUSE IN RESULT TABLE, check if ALL synonym in select is in result table
    auto selects = query.getSelect();
    std::vector<Synonym> unevaluatedSyn = getUnevaluatedSyn(selects, res);
    if (unevaluatedSyn.empty()) { return *res; }

    // CASE SOME RESULT-CLAUSE NOT IN clauses
    auto synResult = evaluateResultClause(query, unevaluatedSyn);
    auto finalResult = resultHandler->getCombined(res, synResult);
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

std::shared_ptr<Result> PQLEvaluator::evaluateNegation(std::shared_ptr<Result> curr,
                                                       std::shared_ptr<Result> clauseRes) {
    std::vector<Synonym> clauseSyns = clauseRes->getHeader();
    std::vector<Synonym> unevaluatedSyn = getUnevaluatedSyn(clauseSyns, curr);

    if (unevaluatedSyn.empty()) {// all syns present
        return resultHandler->getDiff(curr, clauseRes);
    }

    // not all syns in current result, execute naive approach
    std::shared_ptr<Result> lhs = evaluateAll(clauseSyns);
    clauseRes = resultHandler->getDiff(lhs, clauseRes);
    return resultHandler->getCombined(curr, clauseRes);
}

std::shared_ptr<Result> PQLEvaluator::evaluateResultClause(const Query &query, std::vector<Synonym> resultSyns) {
    std::vector<std::shared_ptr<Result>> results;
    for (auto &syn: resultSyns) { results.push_back(evaluateAll({syn})); }
    auto tupleResult = std::make_shared<Result>(true);// Initialize with TRUE
    for (auto const &res: results) {                  // Combine until end of list
        tupleResult = resultHandler->getCombined(tupleResult, res);
    }
    return tupleResult;
}

std::unordered_set<std::shared_ptr<Entity>> PQLEvaluator::getAll(const std::shared_ptr<QueryEntity> &queryEntity) {
    QueryEntityType entityType = queryEntity->getType();
    if (QPSUtil::entityGetterMap.find(entityType) == QPSUtil::entityGetterMap.end()) {
        throw std::runtime_error("Not supported entity type in query select clause");
    }
    return QPSUtil::entityGetterMap[entityType](pkbReader);
}

std::shared_ptr<Result> PQLEvaluator::evaluateAll(const std::vector<Synonym> &entitySyns) {
    auto tupleSize = entitySyns.size();
    std::vector<EntityPtr> queryEntities(tupleSize);
    for (int i = 0; i < tupleSize; i++) { queryEntities[i] = declarationMap[entitySyns[i]]; }

    auto res = std::make_shared<Result>(entitySyns);
    if (tupleSize == 1) {// tuples are single entity
        auto entities = getAll(queryEntities[0]);
        res->setTuples(entities);
        return res;
    }

    // tuples are pair of entities
    std::unordered_set<ResultTuple> tuples;
    auto sets = std::make_pair(getAll(queryEntities[0]), getAll(queryEntities[1]));
    for (auto &first: sets.first) {
        for (auto &second: sets.second) { tuples.insert({first, second}); }
    }
    res->setTuples(tuples);
    return res;
}

void PQLEvaluator::setDeclarationMap(Query &query) { declarationMap = query.getDeclarations(); }