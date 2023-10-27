#pragma once
#include "QPS/QPSTypes.h"
#include "QPS/QPSUtil.h"
#include "QPS/Query.h"

/** Type alias for the score of a clause group, defined as follows:
 * (number of select synonyms, num of synonyms, num of clauses)
 */
typedef std::tuple<int, int, int> GroupScore;

/**
 * @brief QPS Optimizer class.
 *
 * QPS Optimizer class is responsible for optimizing the evaluation of PQL clauses using grouping and ordering.
 */
class QPSOptimizer {
private:
    /**
     * builds a graph with synonyms as nodes and edges representing synonyms that are connected by clause(s)
     * @declarations the map of declared synonyms in the query
     * @param clauses vector of clauses that defines the edges in the graph
     * @return an unordered map representing a adjacency list
     */
    static std::unordered_map<Synonym, std::unordered_set<Synonym>>
    buildSynGraph(std::unordered_map<Synonym, std::shared_ptr<QueryEntity>> &declarations,
                  const std::vector<std::shared_ptr<Clause>> &clauses);

    /**
     * performs depth first search on a adjacency graph of synonyms from current as the starting node
     * @param adjacency_list An unordered map representing the adjacency list of synonym graph
     * @param current The current synonym being explored in the graph
     * @param visited A set of visited synonyms
     * @param connected A set of synonyms that are reachable from current
     */
    static void DFS(const std::unordered_map<Synonym, std::unordered_set<Synonym>> &adjacency_list,
                    const std::string &current, std::unordered_set<std::string> &visited,
                    std::unordered_set<Synonym> &connected);

    /**
     * Groups connected synonyms based on the adjacency list given
     * @param adjacency_list The adjacency list on which the synonym groups depend
     * @return A vector of sets of Synonyms
     */
    static std::vector<std::unordered_set<Synonym>>
    getSynGroups(std::unordered_map<Synonym, std::unordered_set<Synonym>> &adjacency_list);

    /**
     * Calculates the score of the clause group based on the number of select synonyms, the number of synonyms
     * and the number of clauses
     * @param numClauses The number of clauses in the group
     * @param groupSyns The set of synonyms that the group involves
     * @param selects The vector of synonyms in the select clause
     * @return The GroupScore defined as follows: (number of select synonyms, num of synonyms, num of clauses)
     */
    static GroupScore getGroupScore(int numClauses, std::unordered_set<Synonym> groupSyns,
                                    const std::vector<Synonym> &selects);

public:
    /**
     * Groups connected clauses based on their collective synonyms and calculates their scores
     * @param query The query containing all the clauses
     * @return A vector of pairs (clause group, score)
     */
    static std::vector<std::pair<std::unordered_set<std::shared_ptr<Clause>>, GroupScore>>
    getGroupScorePairs(Query &query);

    /**
     * Sorts two pairs by the GroupScore of the clause group for a min-heap priority queue
     * @param p1 The first pair of (clause group, score) to compare
     * @param p2 The second pair of (clause group, score) to compare
     * @return true if the first pair has a higher score, otherwise false
     */
    static bool sortByScore(const std::pair<std::unordered_set<std::shared_ptr<Clause>>, GroupScore> &p1,
                            const std::pair<std::unordered_set<std::shared_ptr<Clause>>, GroupScore> &p2);
};
