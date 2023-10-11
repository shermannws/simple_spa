#pragma once

#include <vector>
#include <array>
#include <unordered_map>

#include "Commons/Entities/Entity.h"
#include "QPS/QPSTypes.h"

/**
 * @brief Enumeration representing the type of result.
 * The result type can be Invalid, Boolean, or Tuples.
 */
enum class ResultType {
    Invalid,
    Boolean,
    Tuples
};

/**
 * @brief Represents the result of a PQL clause evaluation.
 */
class Result {
private:

    /**
     * The type of result
     */
    ResultType type;

    /**
     * the result for a Result of a boolean type, by default
     * false for non-boolean REsult objects
     */
    bool boolResult;

    /**
     * Map of synonym to index of the entities in the result tuples
     */
    SynonymMap synIndices;

    /**
     * the result set for a Result of tuple type
     */
    ResultTuples tuples;

public:
    /**
     * @brief Default constructor for the Result class, returns uninitialized Result object.
     */
    Result();

    /**
     * @brief Gets the type of the result.
     * @return The type of the result (ResultType).
     */
    ResultType getType();

    /**
     * @brief Sets the type of the result based on the list of Synonyms
     * @param synonyms vector of synonyms
     */
    void setType(std::vector<Synonym> synonyms);

    /**
     * @brief Sets the boolean result for a result of type Boolean.
     * @param result The boolean result to set.
     */
    void setBoolResult(bool result);

    /**
     * @brief Gets the boolean result.
     * @return The boolean result.
     */
    bool getBoolResult();

    /**
     * @brief Gets the synonym indices for the result.
     * @return The synonym indices (SynonymMap).
     */
    SynonymMap& getSynIndices();

    void setTuples(const std::vector<Entity>& resultEntities);

    void setTuples(const std::vector<std::vector<Entity>>& resultTuples);

    /**
     * @brief Gets the tuples in the result of the clause evaluation
     * @return The result tuples (ResultTuples).
     */
    ResultTuples& getTuples();
};
