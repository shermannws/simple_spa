#pragma once

#include <array>
#include <unordered_map>
#include <vector>

#include "Commons/Entities/Entity.h"
#include "QPS/QPSTypes.h"

/**
 * @brief Enumeration representing the type of result.
 * The result type can be Invalid, Boolean, or Tuples.
 */
enum class ResultType { Invalid, Boolean, Tuples };

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
     * @brief Constructor for a boolean Result instance, returns a Result object with Type Boolean and boolResult of
     * value
     * @param value boolean value of the result
     */
    Result(bool value);

    /**
     * @brief Constructor for a Result instance, returns a Result object with Type Tuple and synonyms as Result columns
     * if synonyms is non empty, else returns a Boolean Result object
     * @param synonyms vector of synonyms representing the table header
     */
    Result(std::vector<Synonym> synonyms);

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
    SynonymMap &getSynIndices();

    std::vector<Synonym> getHeader();

    void setTuples(const std::unordered_set<std::shared_ptr<Entity>> &resultEntities);

    void setTuples(const std::unordered_set<ResultTuple> &resultTuples);

    /**
     * @brief Gets the tuples in the result of the clause evaluation
     * @return The result tuples (ResultTuples).
     */
    ResultTuples &getTuples();

    /**
     * @brief returns true if a Result object represents a True boolean Result
     * @return true if the result object is a True Boolean Result
     */
    bool isTrue();

    /**
     * @brief returns true if a Result object represents a False boolean Result
     * @return true if the result object is a False Boolean Result
     */
    bool isFalse();

    /**
     * @brief returns true if a Result object represents a Empty Tuple Result
     * @return true if the result object is a Empty Tuple Result
     */
    bool isEmpty();

    /**
     * @brief returns true if a Result object's type is Invalid
     * @return true if the result object is Invalid
     */
    bool isInvalid();
};
