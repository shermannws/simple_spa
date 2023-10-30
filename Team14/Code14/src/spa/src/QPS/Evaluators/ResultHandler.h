#pragma once

#include <list>
#include <string>

#include "QPS/Query.h"
#include "QPS/QPSTypes.h"
#include "Result.h"

/* hash function for a vector of Entities used for hash join partitioning */
struct syn_vector_hash {
    std::size_t operator()(const std::vector<Entity> &entities) const {
        std::size_t seed = 0;
        for (const auto &ent: entities) { seed ^= std::hash<Entity>()(ent) + 0x9e3779b9 + (seed << 6) + (seed >> 2); }
        return seed;
    }
};

/* hashtable built in hash join algorithm */
using hashTable = std::unordered_map<std::vector<Entity>, std::unordered_set<std::vector<Entity>>, syn_vector_hash>;

/* template for the corresponding synonyms in the form of a pair representing <idx of input row, idx in input row> */
using RowTemplate = std::vector<std::pair<idx, idx>>;

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
     * Performs a natural join on two result tables using hash join algorithm
     * @param r1 first result table
     * @param r2 second result table
     * @param header the synonyms in the resultant table
     * @param commonSyns the common synonyms between the tables
     * @return the resultant table from the join
     */
    std::shared_ptr<Result> hashJoin(std::shared_ptr<Result> r1, std::shared_ptr<Result> r2,
                                     std::vector<Synonym> &header, std::vector<Synonym> &commonSyns);

    /**
     * Performs a natural join on two result tables using nested loop join algorithm
     * @param r1 first result table
     * @param r2 second result table
     * @param header  the synonyms in the resultant table
     * @return the resultant table from the join
     */
    std::shared_ptr<Result> nestedLoopJoin(std::shared_ptr<Result> r1, std::shared_ptr<Result> r2,
                                           std::vector<Synonym> &header);

    /**
     * returns the common synonyms between the Result objects and the combined synonyms of the join Result
     * @param r1 first result table to join
     * @param r2 second result table to join
     * @return pair of vector of synonyms representing <common synonyms, header of joined table>
     */
    std::pair<std::vector<Synonym>, std::vector<Synonym>> getSynonyms(std::shared_ptr<Result> r1,
                                                                      std::shared_ptr<Result> r2);

    /**
     * creates a row template to join the 2 result objects into the row according to the specified header
     * @param r1 first result table to join
     * @param r2 first result table to join
     * @param header header of the resultant table
     * @return template for the corresponding synonyms in the form of a pair representing
     * <idx of source row, idx in source row>
     */
    RowTemplate getRowTemplate(std::shared_ptr<Result> r1, std::shared_ptr<Result> r2,
                               const std::vector<Synonym> &header);

    /**
     * creates a new row according to the rowTemplate using row1 and row2 as the input/source rows
     * @param temp row template for resultant row
     * @param row1 first input row
     * @param row2 second input row
     * @return a vector of Entities representing the resultant row
     */
    std::vector<Entity> buildRow(const RowTemplate &temp, const std::vector<Entity> &row1,
                                 const std::vector<Entity> &row2);

    /**
     * Gets a map of indices of the common synonyms between two tables
     * @param r1 first result table
     * @param r2 second result table
     * @param commonSyns the vector of common synonyms
     * @return map of index of common synonyms in table 1 to index in table 2
     */
    std::unordered_map<idx, idx> getMatchMap(std::shared_ptr<Result> r1, std::shared_ptr<Result> r2,
                                             std::vector<Synonym> &commonSyns);

    /**
     * Returns true if the two rows have the same value for the common synonyms (if any)
     * @param row1 row from table 1
     * @param row2 row from table 2
     * @return boolean
     */
    bool isMatch(const std::vector<Entity> &row1, const std::vector<Entity> &row2,
                 const std::unordered_map<int, int> &matchMap);

    /**
     * returns the corresponding indices of the synonyms in the specified result table in a vector
     * @param synonyms vector of synonyms
     * @param result result object containing the synonyms
     * @return vector of the corresponding index of the synonym in the result object
     */
    std::vector<idx> getKeyIndices(std::vector<Synonym> &synonyms, std::shared_ptr<Result> result);

    /**
     * partitions the result table into a hashtable with the vector of synonyms specified as the hash key
     * @param synonyms vector of synonyms used as hash key
     * @param result result table to partition
     * @return hashtable of vector of synonyms to set of rows
     */
    hashTable partition(std::vector<Synonym> &synonyms, std::shared_ptr<Result> result);

    /**
     * Casts a Result object into a False Boolean Result if it is an Empty Tuple Result,
     * otherwise returns the original result
     * @param result shared pointer to the Result object being casted
     * @return shared pointer to the casted Result object
     */
    std::shared_ptr<Result> cast(std::shared_ptr<Result> result);

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
};
