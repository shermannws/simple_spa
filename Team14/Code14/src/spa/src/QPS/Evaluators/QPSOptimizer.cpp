#include "QPSOptimizer.h"

std::unordered_map<Synonym, std::unordered_set<Synonym>>
QPSOptimizer::buildSynGraph(std::unordered_map<std::string, std::shared_ptr<QueryEntity>> &declarations,
                            const std::vector<std::shared_ptr<Clause>> &clauses) {
    //    auto declarationMap = query.getDeclarations();
    std::unordered_map<Synonym, std::unordered_set<Synonym>> graph;// add all syns into graph as nodes
    for (const auto &node: declarations) { graph[node.first] = {}; }

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

GroupScore getGroupScore(int numClauses, std::unordered_set<Synonym> synonyms, const std::vector<Synonym> &selects) {
    int numSelectSyns = 0;
    int numSyns = synonyms.size();

    for (auto &selectSyn: selects) {
        if (synonyms.find(selectSyn) != synonyms.end()) { numSelectSyns += 1; }
    }

    return std::tuple{numSelectSyns, numSyns, numClauses};
}

bool QPSOptimizer::sortByScore(const std::pair<std::unordered_set<std::shared_ptr<Clause>>, GroupScore> &p1,
                               const std::pair<std::unordered_set<std::shared_ptr<Clause>>, GroupScore> &p2) {
    return p1.second > p2.second;
}

std::vector<std::unordered_set<Synonym>>
QPSOptimizer::getSynGroups(std::unordered_map<Synonym, std::unordered_set<Synonym>> &adjacencyList) {
    std::unordered_set<Synonym> visited;
    std::vector<std::unordered_set<Synonym>> synGroups;
    for (const auto &node: adjacencyList) {// get synonym groups
        Synonym syn = node.first;
        if (visited.find(syn) == visited.end()) {// unvisited Synonym
            std::unordered_set<Synonym> currGroup;
            DFS(adjacencyList, syn, visited, currGroup);
            synGroups.push_back(currGroup);
        }
    }
    return synGroups;
}

std::vector<std::pair<std::unordered_set<std::shared_ptr<Clause>>, GroupScore>>
QPSOptimizer::getGroupScorePairs(Query &query) {
    std::vector<std::pair<std::unordered_set<std::shared_ptr<Clause>>, GroupScore>> groupScorePairs;
    std::unordered_map<Synonym, std::unordered_set<std::shared_ptr<Clause>>> synToClauseMap;
    std::unordered_set<std::shared_ptr<Clause>> noSynClauses;

    auto declarations = query.getDeclarations();
    auto clauses = query.getAllClause();

    auto adjacencyList = buildSynGraph(declarations, clauses);
    auto synGroups = getSynGroups(adjacencyList);

    // add clause to noSynClauses if boolean, else add clause to synToClauseMap
    for (const auto &clause: clauses) {
        auto synonyms = clause->getSynonyms();
        if (synonyms.empty()) { noSynClauses.insert(clause); }
        for (const auto &syn: synonyms) {
            if (!synToClauseMap.count(syn)) { synToClauseMap[syn] = {}; }
            synToClauseMap[syn].insert(clause);
        }
    }

    // add noSynClauses to groupScorePairs
    if (!noSynClauses.empty()) { groupScorePairs.emplace_back(noSynClauses, std::tuple{0, 0, noSynClauses.size()}); }

    auto selects = query.getSelect();
    // get corresponding clauses for each group and add to groupScorePairs
    for (const auto &synGroup: synGroups) {
        std::unordered_set<std::shared_ptr<Clause>> group;
        for (const auto &syn: synGroup) { group.insert(synToClauseMap[syn].begin(), synToClauseMap[syn].end()); }
        if (!group.empty()) { groupScorePairs.emplace_back(group, getGroupScore(group.size(), synGroup, selects)); }
    }

    return groupScorePairs;
}


void QPSOptimizer::DFS(const std::unordered_map<Synonym, std::unordered_set<Synonym>> &adjacency_list,
                       const std::string &current, std::unordered_set<std::string> &visited,
                       std::unordered_set<Synonym> &connected) {
    visited.insert(current);
    connected.insert(current);
    for (const std::string &neighbor: adjacency_list.at(current)) {
        if (visited.find(neighbor) == visited.end()) { DFS(adjacency_list, neighbor, visited, connected); }
    }
}