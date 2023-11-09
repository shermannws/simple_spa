#pragma once
#include "QPS/QPSTypes.h"
#include "QPS/QPSUtil.h"
#include "QPS/Query.h"
#include <queue>

/* Type alias for a non-negative integer value representing a score */
typedef int IntScore;

/* Type alias for a non-negative size_t value representing a score */
typedef size_t SizeTScore;

/** Type alias for the score of a clause group, defined as follows:
 * (number of select synonyms, num of synonyms, num of clauses)
 */
typedef std::tuple<IntScore, SizeTScore, IntScore> GroupScore;

/** Type alias for the score of a Clause, defined as follows:
 * (whether it's a negated clause, no of synonyms, score of ClauseType)
 */
typedef std::tuple<IntScore, SizeTScore, IntScore> ClauseScore;

/**
 * @brief QPS Optimizer class.
 *
 * QPS Optimizer class is responsible for optimizing the evaluation of PQL clauses using grouping and ordering.
 */
class QPSOptimizer {
private:
    /**
     * An unordered map that maps ClauseType to a Score
     */
    static std::unordered_map<ClauseType, IntScore> clauseTypeScore;

    /**
     * Groups connected synonyms based on the clauses given.
     * @param clauses The vector of clauses
     * @return A vector of sets of Synonyms
     */
    static std::vector<std::unordered_set<Synonym>> getSynGroups(const std::vector<std::shared_ptr<Clause>> &clauses);

    /**
     * Calculates the score of the clause group based on the number of select synonyms, the number of synonyms
     * and the number of clauses
     * @param numClauses The number of clauses in the group
     * @param groupSyns The set of synonyms that the group involves
     * @param selects The vector of synonyms in the select clause
     * @return The GroupScore defined as follows: (number of select synonyms, num of synonyms, num of clauses)
     */
    static GroupScore getGroupScore(SizeTScore numClauses, std::unordered_set<Synonym> groupSyns,
                                    const std::vector<Synonym> &selects);

    /**
     * Calculates the score of the Clause based on the number of synonyms and the ClauseType
     * @param clause the Clause which score to calculate
     * @return The ClauseScore defined as follows: (whether it's a negated clause, number of synonyms, the ClauseType
     * score)
     */
    static ClauseScore getClauseScore(const std::shared_ptr<Clause> &clause);

    /**
     * Determines if a set of synonyms of a clause group intersects with a vector of synonyms of a Clause
     * @param currSynGroup the set of synonyms to compare with
     * @param synonyms the vector of synonyms to compare with
     * @return true if the set and the vector have common synonym(s), otherwise false
     */
    static bool intersect(const std::unordered_set<Synonym> &currSynGroup, const std::vector<Synonym> &synonyms);

public:
    /**
     * Calculates the score of each clause in clauses and returns them as pairs
     * @param clauses The clauses which scores to calculate
     * @return A vector of pairs (clause, score)
     */
    static std::vector<std::pair<std::shared_ptr<Clause>, ClauseScore>>
    getClauseScorePairs(std::vector<std::shared_ptr<Clause>> &clauses);

    /**
     * Groups connected clauses based on their collective synonyms and calculates their scores
     * @param query The query containing all the clauses
     * @return A vector of pairs (clause group, score)
     */
    static std::vector<std::pair<std::unordered_set<std::shared_ptr<Clause>>, GroupScore>>
    getGroupScorePairs(Query &query);

    /**
     * Sorts a vector of Clauses by their ClauseScore
     * @param clauses The vector of Clauses to sort
     * @return The sorted vector of Clauses
     */
    static std::vector<std::shared_ptr<Clause>> sortClauses(std::vector<std::shared_ptr<Clause>> &clauses);

    /**
     * Compares two pairs by the GroupScore of the clause group for a min-heap priority queue
     * @param p1 The first pair of (clause group, score) to compare
     * @param p2 The second pair of (clause group, score) to compare
     * @return true if the first pair has a higher score, otherwise false
     */
    static bool compareGroupByScore(const std::pair<std::unordered_set<std::shared_ptr<Clause>>, GroupScore> &p1,
                                    const std::pair<std::unordered_set<std::shared_ptr<Clause>>, GroupScore> &p2);

    /**
     * Compares two pairs by the ClauseScore of the clause for a min-heap priority queue
     * @param p1 The first pair of (clause, score) to compare
     * @param p2 The second pair of (clause, score) to compare
     * @return true if the first pair has a higher score, otherwise false
     */
    static bool compareClauseByScore(const std::pair<std::shared_ptr<Clause>, ClauseScore> &p1,
                                     const std::pair<std::shared_ptr<Clause>, ClauseScore> &p2);
};
