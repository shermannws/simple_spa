#pragma once

#include "./PKB/PkbReader.h"
#include "QPS/Query.h"
#include "Result.h"
#include "Strategies/AssignPatternStrategy.h"
#include "Strategies/Strategy.h"


/**
 * @class ClauseHandler is the interface for PQLEvaluator to evaluate clauses
 * with different strategies
 */
class ClauseHandler {
private:
    /**
     * The strategy used by the ClauseHandler
     */
    std::shared_ptr<Strategy> strategy;

    /**
     * The pkbReader called to retrieve required data for executing clause
     */
    std::shared_ptr<PkbReader> pkbReader;

public:
    /**
     * Constructor for ClauseHandler
     * @param pkbReader The pkbReader instance called to retrieve required data
     */
    explicit ClauseHandler(std::shared_ptr<PkbReader> pkbReader);

    /**
     * Sets the strategy used by the ClauseHandler
     * @param strategy the strategy picked at runtime
     */
    void setStrategy(std::shared_ptr<Strategy> strategy);

    /**
     * Executes the clause using the strategy and writes the result into the
     * result object
     * @param clause the clause to be evaluated
     * @param result the Result table to be populated with the results of the
     * clause execution
     */
    std::shared_ptr<Result> executeClause(std::shared_ptr<Clause> clause) const;
};
