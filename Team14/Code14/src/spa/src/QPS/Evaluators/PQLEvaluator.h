#pragma once

#include <list>
#include <queue>
#include <string>

#include "./PKB/PkbReader.h"
#include "ClauseHandler.h"
#include "QPS/QPSTypes.h"
#include "QPS/Query.h"
#include "QPSOptimizer.h"
#include "Result.h"
#include "ResultHandler.h"

using transformFunc = std::function<std::string(std::shared_ptr<Entity>)>;

/**
 * @brief PQL (Program Query Language) evaluator class.
 *
 * The PQLEvaluator class is responsible for evaluating PQL queries and producing results.
 * It uses a PKB reader, clause handler, and result handler for query evaluation.
 */
class PQLEvaluator {
private:
    /**
     * map of synonyms to shared pointer to QueryEntity of the current query being evaluated
     */
    DeclarationMap declarationMap;

    /**
     * Shared pointer to the PKB reader which retrieves the required information for query evaluation
     */
    std::shared_ptr<PkbReader> pkbReader;

    /**
     * Shared pointer to the clause handler which evaluates each clause in the PQL query
     */
    std::shared_ptr<ClauseHandler> clauseHandler;

    /**
     * Shared pointer to the result handler which is responsible for combining results
     */
    std::shared_ptr<ResultHandler> resultHandler;

    /**
     * @brief Retrieves all instances of a query entity from the PKB, the method
     * is responsible for choosing which PKB API to call
     * @param queryEntity A pointer to the query entity to retrieve instances for.
     * @return A set of entities representing all instances of the query entity.
     */
    std::unordered_set<EntityPointer> getAll(const EntityPtr &queryEntity);

    /**
     * @brief retrieves all combinations of the entities in the order specified by entitySyns from the PKB
     * @param entitySyns vector of Synonyms representing the combination of Entities to retrieve
     * @return shared pointer to Result containing all combinations of entities
     */
    std::shared_ptr<Result> evaluateAll(const std::vector<Synonym> &entitySyns);

    /**
     * @brief Evaluates a clause and updates the result accordingly.
     * @param clause A shared pointer to the Clause to evaluate.
     * @return shared pointer to result object
     */
    std::shared_ptr<Result> evaluateClause(std::shared_ptr<Clause> clause);

    /**
     * @brief Evaluates the result of current and negating the specified clause result
     * @param curr current Result
     * @param clauseRes Result of the clause to be negated
     * @return shared pointer to result object
     */
    std::shared_ptr<Result> evaluateNegation(std::shared_ptr<Result> curr, std::shared_ptr<Result> clauseRes);

    /**
     * @brief Evaluates a subset of the result clause of a query
     * @param resultSyns the vector of synonyms representing the subset of result clause to be evaluated
     * @return shared pointer to result object
     */
    std::shared_ptr<Result> evaluateResultClause(std::vector<Synonym> resultSyns);

    /**
     * @brief returns the vector of synonyms in the result clause that is not present in the result object
     * @param resultClause vector of synonyms
     * @param result result object
     * @return vector of unevaluated synonyms
     */
    std::vector<Synonym> getUnevaluatedSyn(std::vector<Synonym> resultClause, std::shared_ptr<Result> result);

    /**
     * applies the transformFunc to the entity at index equal to the int and stores the result in the returned vector
     * @param row vector of entities to transform
     * @param transformations pair of index of entity to transform and toString function to apply
     * @return the vector of transformation results
     */
    std::vector<std::string> project(ResultTuple row, std::vector<std::pair<int, transformFunc>> &transformations);

    /**
     * creates a vector of transformations to convert a row from a result table into the format specified by
     * resultClause a transformation is a pair of int, transformFunc where int represents index of entity
     * @param inputMap synonym indices of input tuples
     * @param resultClause vector of synonyms we want to build
     * @return
     */
    std::vector<std::pair<int, transformFunc>> getTransformations(SynonymMap inputMap,
                                                                  std::vector<Synonym> resultClause);

    /**
     * concatenates a vector of strings with a whitespace as the connector
     * @param strings vector of strings to join
     * @return resultant string
     */
    std::string concat(std::vector<std::string> strings);

    /**
     * Evaluates all clauses in the group as boolean clauses
     * @param clauses The group of clauses to evaluate
     * @return true if all of the clauses are true or non-empty, otherwise false
     */
    bool evaluateBooleanGroup(const std::vector<std::shared_ptr<Clause>> &clauses);

    /**
     * Evaluates a group of clauses which returns tuples
     * @param clauses The group of clauses to evaluate
     * @return the Tuple Result object if it is non-empty, otherwise false Result object
     */
    std::shared_ptr<Result> evaluateTupleGroup(std::vector<std::shared_ptr<Clause>> &clauses);

    /**
     * sets the PQLEvaluator's declaration map
     * @param query current query being evaluated
     */
    void setDeclarationMap(Query &query);

    /**
     * @brief groups the synonyms in the clause result based on whether it is found in current result
     * @param curr current result
     * @param clauseRes clause result
     * @return pair of vector of synonyms representing evaluated synonyms and unevaluated synonyms respectively
     */
    std::pair<std::vector<Synonym>, std::vector<Synonym>> groupSynByEvaluated(std::shared_ptr<Result> curr,
                                                                              std::shared_ptr<Result> clauseRes);

public:
    /**
     * @brief Explicit constructor for the PQLEvaluator class.
     * @param pkbReader A shared pointer to the PKB reader.
     */
    explicit PQLEvaluator(std::shared_ptr<PkbReader> pkbReader);

    /**
     * @brief Evaluates a PQL query and returns the result.
     * @param query The PQL query to evaluate.
     * @return The result of the PQL query evaluation as a Result object
     */
    Result evaluate(Query &query);

    /**
     * @brief Formats the result of a PQL query based on the given query and result table.
     * @param query The PQL query.
     * @param result The result of the PQL query evaluation.
     * @return The formatted result list
     */
    ResultList formatResult(Query &query, Result &result);
};