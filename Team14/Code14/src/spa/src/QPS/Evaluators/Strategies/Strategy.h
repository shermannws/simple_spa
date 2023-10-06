#pragma once

#include "QPS/Evaluators/Result.h"
#include "QPS/Clauses/Clause.h"
#include "./PKB/PkbReader.h"
#include "Commons/Entities/StatementType.h"

/**
 * Strategy interface for each type of clause e.g. UsesStrategy, FollowsStrategy, AssignPatternStrategy, etc
 */
class Strategy {
public:
    /**
     * @brief Evaluates the clause using the appropriate pkbReader method
     * @param clause The shared pointer of the Clause to be evaluated
     * @param pkbReader The pkbReader of which the methods are to be called
     * @return The result of the clause evaluation
     */
    virtual Result evaluateClause(std::shared_ptr<Clause> clause) const = 0;
};
