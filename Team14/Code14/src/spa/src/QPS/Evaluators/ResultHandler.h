#pragma once

#include <list>
#include <string>

#include "Result.h"
#include "QPS/Query.h"

/**
 * @class ResultHandler class generates a result table from the combining two tables
 * and handles result table join operations.
 */
class ResultHandler {
private:
    /**
     * Performs a natural join on two result tables
     * @param r1 first result table
     * @param r2 second result table
     * @return the resultant table from the join
     */
    std::shared_ptr<Result> join(std::shared_ptr<Result> r1, std::shared_ptr<Result> r2);

    /**
     * Gets a map of indices of the common synonyms between two tables
     * @param r1 first result table
     * @param r2 second result table
     * @return map of index of common synonyms in table 1 to index in table 2
     */
    std::unordered_map<int, int> getCommonColumns(std::shared_ptr<Result> r1, std::shared_ptr<Result> r2);

    /**
     * Builds a map of synonym to index for the resultant combined table
     * @param r1 first result table
     * @param r2 second result table
     * @return map of synonym to index
     */
    SynonymMap buildSynIndices(std::shared_ptr<Result> r1, std::shared_ptr<Result> r2);

    /**
     * Creates a vector of the synonyms in the order of their index in map
     * @param SynonymMap map of synonyms to index
     * @return vector of the synonyms
     */
    std::vector<Synonym> getHeader(SynonymMap);

    /**
     * Returns true if the two rows have the same value for the common synonyms (if any)
     * @param row1 row from table 1
     * @param row2 row from table 2
     * @return boolean
     */
    bool isMatch(const std::vector<Entity>& row1, const std::vector<Entity>& row2, const std::unordered_map<int, int>& commons);

public:
    /**
     * Constructor for ResultHandler class
     * @return A ResultHandler object
     */
    explicit ResultHandler();

    /**
     * Evaluates the final result form combining 2 results
     * @param r1 first result table
     * @param r2 second result table
     * @return the resultant table
     */
    std::shared_ptr<Result> getCombined(std::shared_ptr<Result> r1, std::shared_ptr<Result> r2);

    /**
     * Casts a Result object into a False Boolean Result if it is an Empty Tuple Result,
     * otherwise returns the original result
     * @param result shared pointer to the Result object being casted
     * @return shared pointer to the casted Result object
     */
    std::shared_ptr<Result> cast(std::shared_ptr<Result> result);
};


