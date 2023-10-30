#include "QPSOptimizer.h"

std::unordered_map<ClauseType, Score> QPSOptimizer::clauseTypeScore = {
        {ClauseType::With, 0},     {ClauseType::If, 1},           {ClauseType::While, 1},
        {ClauseType::Assign, 2},   {ClauseType::Calls, 3},        {ClauseType::Parent, 4},
        {ClauseType::Follows, 5},  {ClauseType::Next, 6},         {ClauseType::Modifies, 7},
        {ClauseType::Uses, 8},     {ClauseType::CallsStar, 9},    {ClauseType::ParentStar, 10},
        {ClauseType::Affects, 11}, {ClauseType::FollowsStar, 12}, {ClauseType::NextStar, 13},
};

std::unordered_map<Synonym, std::unordered_set<Synonym>>
QPSOptimizer::buildSynGraph(std::unordered_map<std::string, std::shared_ptr<QueryEntity>> &declarations,
                            const std::vector<std::shared_ptr<Clause>> &clauses) {
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

void QPSOptimizer::DFS(const std::unordered_map<Synonym, std::unordered_set<Synonym>> &adjacency_list,
                       const std::string &current, std::unordered_set<std::string> &visited,
                       std::unordered_set<Synonym> &connected) {
    visited.insert(current);
    connected.insert(current);
    for (const std::string &neighbor: adjacency_list.at(current)) {
        if (visited.find(neighbor) == visited.end()) { DFS(adjacency_list, neighbor, visited, connected); }
    }
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

GroupScore QPSOptimizer::getGroupScore(int numClauses, std::unordered_set<Synonym> groupSyns,
                                       const std::vector<Synonym> &selects) {
    int numSelectSyns = 0;
    int numSyns = groupSyns.size();

    for (const auto &select: selects) {
        auto selectSyn = QPSUtil::getSyn(select);
        if (groupSyns.find(selectSyn) != groupSyns.end()) { numSelectSyns += 1; }
    }

    return std::tuple{numSelectSyns, numSyns, numClauses};
}

ClauseScore QPSOptimizer::getClauseScore(const std::shared_ptr<Clause> &clause) {
    int numSyns = clause->getSynonyms().size();
    int typeScore = QPSOptimizer::clauseTypeScore[clause->getType()];

    return std::tuple{numSyns, typeScore};
}

bool QPSOptimizer::intersects(const std::unordered_set<Synonym> &currSynGroup, const std::vector<Synonym> &synonyms) {
    for (const auto &syn: synonyms) {
        if (currSynGroup.find(syn) != currSynGroup.end()) { return true; }
    }
    return false;
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

std::vector<std::shared_ptr<Clause>> QPSOptimizer::sortClauses(std::vector<std::shared_ptr<Clause>> &clauses,
                                                               int numSynonyms) {
    std::vector<std::shared_ptr<Clause>> finalClauses;
    finalClauses.reserve(clauses.size());// preallocate memory to reduce reallocation

    std::priority_queue pq(clauses.begin(), clauses.end(), QPSOptimizer::compareClauseByScore);

    if (!numSynonyms) {// if no synonym
        while (!pq.empty()) {
            auto clause = pq.top();
            finalClauses.push_back(clause);
            pq.pop();
        }
        return finalClauses;
    }


    std::vector<std::shared_ptr<Clause>> tempGroup;
    std::unordered_set<Synonym> currSynGroup;

    auto clause = pq.top();
    pq.pop();
    finalClauses.push_back(clause);
    auto clauseSynonyms = clause->getSynonyms();
    currSynGroup.insert(clauseSynonyms.begin(), clauseSynonyms.end());

    while (!pq.empty()) {
        clause = pq.top();
        pq.pop();
        clauseSynonyms = clause->getSynonyms();
        while (!intersects(currSynGroup, clauseSynonyms) && !pq.empty()) {
            tempGroup.push_back(std::move(clause));
            clause = pq.top();
            pq.pop();
            clauseSynonyms = clause->getSynonyms();
        }
        finalClauses.push_back(clause);
        currSynGroup.insert(clauseSynonyms.begin(), clauseSynonyms.end());
        for (const auto &c: tempGroup) { pq.push(c); }
        tempGroup.clear();
    }
    return finalClauses;
}

bool QPSOptimizer::compareGroupByScore(const std::pair<std::unordered_set<std::shared_ptr<Clause>>, GroupScore> &p1,
                                       const std::pair<std::unordered_set<std::shared_ptr<Clause>>, GroupScore> &p2) {
    return p1.second > p2.second;
}

bool QPSOptimizer::compareClauseByScore(const std::shared_ptr<Clause> &c1, const std::shared_ptr<Clause> &c2) {
    return getClauseScore(c1) > getClauseScore(c2);
}
