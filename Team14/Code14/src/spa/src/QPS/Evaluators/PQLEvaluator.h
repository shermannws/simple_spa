#pragma once

#include <list>
#include <string>

#include "./PKB/PkbReader.h"
#include "ClauseHandler.h"
#include "QPS/QPSTypes.h"
#include "QPS/Query.h"
#include "Result.h"
#include "ResultHandler.h"

using transformFunc = std::function<std::string(Entity)>;

/**
 * @brief PQL (Program Query Language) evaluator class.
 *
 * The PQLEvaluator class is responsible for evaluating PQL queries and producing results.
 * It uses a PKB reader, clause handler, and result handler for query evaluation.
 */
class PQLEvaluator {
private:
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
     * @return A vector of entities representing all instances of the query entity.
     */
    std::vector<Entity> getAll(const EntityPtr &queryEntity);

    /**
     * @brief Evaluates a clause and updates the result accordingly.
     * @param clause A shared pointer to the Clause to evaluate.
     * @return shared pointer to result object
     */
    std::shared_ptr<Result> evaluateClause(const std::shared_ptr<Clause> clause);

    /**
     * @brief Evaluates a select clause with the given entity as the result clause without any constraint clauses
     * @param entity the selected entity to be evaluated
     * @return shared pointer to result object
     */
    std::shared_ptr<Result> evaluateSelect(const std::shared_ptr<QueryEntity> entity);

    /**
     * @brief Evaluates a subset of the result clause of a query
     * @param query the query object whose result clause is being evaluated
     * @param resultSyns the vector of synonyms representing the subset of result clause to be evaluated
     * @return shared pointer to result object
     */
    std::shared_ptr<Result> evaluateResultClause(const Query &query, std::vector<Synonym> resultSyns);

    /**
     * @brief Evaluates all the constraint clauses of a query into a combined result, returns nullptr if
     * there are no constraint clauses
     * @param query the query object to evaluate
     * @return shared pointer to result object
     */
    std::shared_ptr<Result> evaluateConstraintClauses(const Query &query);

    /**
     * @brief returns the vector of synonyms in the result clause that is not present in the result object
     * @param resultClause vector of synonyms
     * @param result result object
     * @return vector of unevaluated synonyms
     */
    std::vector<Synonym> getUnevaluatedSyn(const std::vector<Synonym> resultClause, std::shared_ptr<Result> result);

    /**
     * applies the transformFunc to the entity at index equal to the int and stores the result in the returned vector
     * @param row vector of entities to transform
     * @param transformations pair of index of entity to transform and toString function to apply
     * @return the vector of transformation results
     */
    std::vector<std::string> project(std::vector<Entity> row, std::vector<std::pair<int, transformFunc>> transformations);

    /**
     * creates a vector of transformations to convert a row from a result table into the format specified by resultClause
     * a transformation is a pair of int, transformFunc where int represents index of entity
     * @param inputMap synonym indices of input tuples
     * @param resultClause vector of synonyms we want to build
     * @return
     */
    std::vector<std::pair<int, transformFunc>> getTransformations(SynonymMap inputMap, std::vector<Synonym> resultClause);

    /**
     * concatenates a vector of strings with a whitespace as the connector
     * @param strings vector of strings to join
     * @return resultant string
     */
    std::string concat (std::vector<std::string> strings);
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