#pragma once
#include "QPS/QPSTypes.h"
#include "QPS/QPSUtil.h"
#include "QPS/Query.h"

typedef std::tuple<int, int, int> GroupScore;

class QPSOptimizer {
private:
    static std::unordered_map<Synonym, std::unordered_set<Synonym>>
    buildSynGraph(Query &query, const std::vector<std::shared_ptr<Clause>> &clauses);


    static void DFS(const std::unordered_map<Synonym, std::unordered_set<Synonym>> &adjacency_list,
                    const std::string &current, std::unordered_set<std::string> &visited,
                    std::unordered_set<Synonym> &connected);

    static std::vector<std::unordered_set<Synonym>>
    getSynGroups(std::unordered_map<Synonym, std::unordered_set<Synonym>> &adjacency_list);

public:
    static std::vector<std::pair<std::unordered_set<std::shared_ptr<Clause>>, GroupScore>>
    getGroupScorePairs(Query &query, const std::vector<std::shared_ptr<Clause>> &clauses,
                       const std::vector<Synonym> &selects);

    static bool sortByScore(const std::pair<std::unordered_set<std::shared_ptr<Clause>>, GroupScore> &p1,
                            const std::pair<std::unordered_set<std::shared_ptr<Clause>>, GroupScore> &p2);
};
