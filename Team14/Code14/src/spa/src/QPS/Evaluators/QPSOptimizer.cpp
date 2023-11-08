#include "QPSOptimizer.h"
#include "UFDSUtil.h"

std::unordered_map<ClauseType, IntScore> QPSOptimizer::clauseTypeScore = {
        {ClauseType::With, 0},     {ClauseType::If, 1},           {ClauseType::While, 1},
        {ClauseType::Assign, 2},   {ClauseType::Calls, 3},        {ClauseType::Parent, 4},
        {ClauseType::Follows, 5},  {ClauseType::Next, 6},         {ClauseType::Modifies, 7},
        {ClauseType::Uses, 8},     {ClauseType::CallsStar, 9},    {ClauseType::ParentStar, 10},
        {ClauseType::Affects, 11}, {ClauseType::FollowsStar, 12}, {ClauseType::NextStar, 13},
};

std::vector<std::unordered_set<Synonym>>
QPSOptimizer::getSynGroups(const std::vector<std::shared_ptr<Clause>> &clauses) {
    UFDSUtil<Synonym> ufds;

    // process all clauses representing relationships between synonyms
    for (const auto &clause: clauses) {
        std::vector<Synonym> syns = clause->getSynonyms();
        assert(syns.size() <= 2);
        if (syns.size() == 2) { ufds.unionSet(syns[0], syns[1]); }
        if (syns.size() == 1) { ufds.unionSet(syns[0], syns[0]); }
    }

    // extract syn groups from UFDS
    std::unordered_map<Synonym, std::unordered_set<Synonym>> rootToSynGroupsMap;
    auto &parents = ufds.getParent();
    for (const auto &[child, _]: parents) {
        auto root = ufds.findSet(child);
        if (rootToSynGroupsMap.find(root) == rootToSynGroupsMap.end()) {
            rootToSynGroupsMap[root] = std::unordered_set<Synonym>();
        }
        rootToSynGroupsMap[root].insert(child);
    }

    std::vector<std::unordered_set<Synonym>> synGroups;
    synGroups.reserve(rootToSynGroupsMap.size());
    for (auto &[syn, synGroup]: rootToSynGroupsMap) { synGroups.push_back(synGroup); }
    return synGroups;
}

GroupScore QPSOptimizer::getGroupScore(SizeTScore numClauses, std::unordered_set<Synonym> groupSyns,
                                       const std::vector<Synonym> &selects) {
    int numSelectSyns = 0;
    auto numSyns = groupSyns.size();

    for (const auto &select: selects) {
        auto selectSyn = QPSUtil::getSyn(select);
        if (groupSyns.find(selectSyn) != groupSyns.end()) { numSelectSyns += 1; }
    }

    return std::tuple{numSelectSyns, numSyns, numClauses};
}

ClauseScore QPSOptimizer::getClauseScore(const std::shared_ptr<Clause> &clause) {
    int negation = clause->isNegation();
    auto numSyns = clause->getSynonyms().size();
    int typeScore = QPSOptimizer::clauseTypeScore[clause->getType()];

    return std::tuple{negation, numSyns, typeScore};
}

bool QPSOptimizer::intersect(const std::unordered_set<Synonym> &currSynGroup, const std::vector<Synonym> &synonyms) {
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

    auto synGroups = getSynGroups(clauses);

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

std::vector<std::pair<std::shared_ptr<Clause>, ClauseScore>>
QPSOptimizer::getClauseScorePairs(std::vector<std::shared_ptr<Clause>> &clauses) {
    std::vector<std::pair<std::shared_ptr<Clause>, ClauseScore>> pairs;
    pairs.reserve(clauses.size());
    for (const auto &clause: clauses) { pairs.emplace_back(clause, getClauseScore(clause)); }
    return pairs;
}


std::vector<std::shared_ptr<Clause>> QPSOptimizer::sortClauses(std::vector<std::shared_ptr<Clause>> &clauses) {
    std::vector<std::shared_ptr<Clause>> finalClauses;
    finalClauses.reserve(clauses.size());// preallocate memory to reduce reallocation
    auto pairs = getClauseScorePairs(clauses);
    std::priority_queue pq(pairs.begin(), pairs.end(), QPSOptimizer::compareClauseByScore);

    std::vector<std::pair<std::shared_ptr<Clause>, ClauseScore>> tempGroup;
    std::unordered_set<Synonym> currSynGroup;

    auto pair = pq.top();
    auto clause = pair.first;
    pq.pop();
    finalClauses.push_back(clause);
    auto clauseSynonyms = clause->getSynonyms();
    currSynGroup.insert(clauseSynonyms.begin(), clauseSynonyms.end());

    while (!pq.empty()) {
        pair = pq.top();
        clause = pair.first;
        pq.pop();
        clauseSynonyms = clause->getSynonyms();
        while (!intersect(currSynGroup, clauseSynonyms) && !pq.empty()) {
            tempGroup.push_back(pair);
            pair = pq.top();
            clause = pair.first;
            pq.pop();
            clauseSynonyms = clause->getSynonyms();
        }
        finalClauses.push_back(clause);
        currSynGroup.insert(clauseSynonyms.begin(), clauseSynonyms.end());
        for (const auto &tempPair: tempGroup) { pq.push(tempPair); }
        tempGroup.clear();
    }
    return finalClauses;
}

bool QPSOptimizer::compareGroupByScore(const std::pair<std::unordered_set<std::shared_ptr<Clause>>, GroupScore> &p1,
                                       const std::pair<std::unordered_set<std::shared_ptr<Clause>>, GroupScore> &p2) {
    return p1.second > p2.second;
}

bool QPSOptimizer::compareClauseByScore(const std::pair<std::shared_ptr<Clause>, ClauseScore> &p1,
                                        const std::pair<std::shared_ptr<Clause>, ClauseScore> &p2) {
    return p1.second > p2.second;
}
