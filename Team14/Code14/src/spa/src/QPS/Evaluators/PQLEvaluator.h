#pragma once

#include <list>
#include <string>

#include "Result.h"
#include "QPS/Query.h"
#include "ClauseHandler.h"
#include "ResultHandler.h"
#include "./PKB/PkbReader.h"
#include "QPS/QPSTypes.h"

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
    std::vector<Entity> getAll(const EntityPtr& queryEntity);

    /**
     * @brief Evaluates a clause and updates the result accordingly.
     * @param clause A shared pointer to the Clause to evaluate.
     * @return shared pointer to result object
     */
    std::shared_ptr<Result> evaluateClause(const std::shared_ptr<Clause> clause);

    /**
     * @brief Evaluates the select clause of a query.
     * @param entity shared pointer to the selected query entity
     * @return shared pointer to result object
     */
    std::shared_ptr<Result> evaluateSelect(const EntityPtr entity);

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
    Result evaluate(Query& query);

    /**
    * @brief Formats the result of a PQL query based on the given query and result table.
    * @param query The PQL query.
    * @param result The result of the PQL query evaluation.
    * @return The formatted result list
    */
    ResultList formatResult(Query& query, Result& result);
};