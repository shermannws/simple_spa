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

std::unordered_map<Synonym, std::unordered_set<Synonym>>
PQLEvaluator::buildSynGraph(Query &query, std::vector<std::shared_ptr<Clause>> clauses) {
    auto declarationMap = query.getDeclarations();
    std::unordered_map<Synonym, std::unordered_set<Synonym>> graph;// add all syns into graph as nodes
    for (const auto &node: declarationMap) { graph[node.first] = {}; }

    for (const auto &clause: clauses) {
        auto group = clause->getSynonyms();
        for (size_t i = 0; i < group.size(); ++i) {
            for (size_t j = 0; j < group.size(); ++j) {
                if (i != j) { graph[group[i]].insert(group[j]); }
            }
        }
    }
    return graph;
}


std::vector<std::unordered_set<std::shared_ptr<Clause>>>
PQLEvaluator::groupClauses(std::unordered_map<Synonym, std::unordered_set<Synonym>> &adjacency_list,
                           std::vector<std::shared_ptr<Clause>> clauses) {
    std::unordered_set<Synonym> visited;
    std::vector<std::unordered_set<std::shared_ptr<Clause>>> clauseGroups;
    std::vector<std::unordered_set<Synonym>> synGroups;
    std::unordered_map<Synonym, std::unordered_set<std::shared_ptr<Clause>>> synToClauseMaps;
    for (const auto &clause: clauses) {
        auto syns = clause->getSynonyms();
        if (syns.empty()) {// for clauses with no syn, add to own group
            clauseGroups.push_back({clause});
            continue;
        }
        for (const auto &syn: syns) {
            if (!synToClauseMaps.count(syn)) { synToClauseMaps[syn] = {}; }
            synToClauseMaps[syn].insert(clause);
        }
    }

    for (const auto &node: adjacency_list) {// get synonym groups
        Synonym syn = node.first;
        if (visited.find(syn) == visited.end()) {// unvisited Synonym
            std::unordered_set<Synonym> currGroup;
            DFS(adjacency_list, syn, visited, currGroup);
            synGroups.push_back(currGroup);
        }
    }

    for (const auto &synGroup: synGroups) {// get corresponding clauses for each group
        std::unordered_set<std::shared_ptr<Clause>> clauses;
        for (const auto &syn: synGroup) { clauses.insert(synToClauseMaps[syn].begin(), synToClauseMaps[syn].end()); }
        clauseGroups.push_back(clauses);
    }
    return clauseGroups;
}

void PQLEvaluator::DFS(const std::unordered_map<Synonym, std::unordered_set<Synonym>> &adjacency_list,
                       const std::string &current, std::unordered_set<std::string> &visited,
                       std::unordered_set<Synonym> &connected) {
    visited.insert(current);
    connected.insert(current);
    for (const std::string &neighbor: adjacency_list.at(current)) {
        if (visited.find(neighbor) == visited.end()) { DFS(adjacency_list, neighbor, visited, connected); }
    }
}


bool PQLEvaluator::intersect(std::vector<Synonym> selects, std::shared_ptr<Result> res) {
    auto map = res->getSynIndices();
    for (const auto &elem: selects) {
        auto syn = QPSUtil::getSyn(elem);
        if (map.count(syn)) { return true; }
    }
    return false;
}

Result PQLEvaluator::evaluate(Query &query) {
    auto clauses = query.getAllClause();
    auto synGraph = buildSynGraph(query, clauses);
    auto clauseGroups = groupClauses(synGraph, clauses);
    auto selects = query.getSelect();

    std::vector<std::shared_ptr<Result>> boolResults;
    std::vector<std::shared_ptr<Result>> selectResults;

    for (const auto &group: clauseGroups) {
        std::vector<std::shared_ptr<Clause>> clauses(group.begin(), group.end());
        auto res = evaluateClauses(clauses);
        if (intersect(selects, res)) {// if intersect with select, add to selectRes
            selectResults.push_back(res);
        } else {
            boolResults.push_back(res);
        }
    }

    // evaluate non-SELECT clauses first
    bool boolResult = evaluateBoolResults(boolResults);
    if (!boolResult) { return Result(false); }
    if (query.getSelect().empty()) { return Result(boolResult); }// end of evaluation for BOOLEAN queries

    // TRUE OR NON-EMPTY bool clause results, continue evaluating SELECT clauses
    std::shared_ptr<Result> result = evaluateMainResults(selectResults);

    //  CASE RESULT-CLAUSE IN RESULT TABLE, check if ALL synonym in select is in result table
    std::vector<Synonym> unevaluatedSyn = getUnevaluatedSyn(query.getSelect(), result);
    if (unevaluatedSyn.empty()) { return *result; }

    // CASE SOME RESULT-CLAUSE NOT IN clauses
    auto synResult = evaluateResultClause(query, unevaluatedSyn);
    auto finalResult = resultHandler->getCombined(result, synResult);
    return *finalResult;
}

bool PQLEvaluator::evaluateBoolResults(std::vector<std::shared_ptr<Result>> results) {
    for (auto const r: results) {
        if (r->isFalse() || r->isEmpty()) { return false; }
    }
    return true;
}

std::shared_ptr<Result> PQLEvaluator::evaluateMainResults(std::vector<std::shared_ptr<Result>> results) {
    auto result = std::make_shared<Result>(true);// Initialize with TRUE
    for (auto const &res: results) {             // Combine until end of list
        result = resultHandler->getCombined(result, res);
    }
    return result;
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

std::shared_ptr<Result> PQLEvaluator::evaluateClauses(std::vector<std::shared_ptr<Clause>> clauseGroup) {
    auto result = std::make_shared<Result>(true);// Initialize with TRUE

    for (auto const clause: clauseGroup) {
        auto clauseResult = evaluateClause(clause);
        result = resultHandler->getCombined(result, clauseResult);
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
