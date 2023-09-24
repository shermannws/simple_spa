#pragma once

#include "Strategy.h"
#include "QPS/Clauses/SuchThatClause.h"

/**
 * The Strategy class of Uses in SuchThatClause
 */
class UsesSuchThatStrategy : public Strategy {
public:
    /**
     * @brief Evaluates the clause using pkbReader methods relating to Uses
     * @param clause The shared pointer of the Clause to be evaluated
     * @param pkbReader The pkbReader of which the methods are to be called
     * @return The result of the clause evaluation
     */
    Result evaluateClause(std::shared_ptr<Clause> clause, std::shared_ptr<PkbReader> pkbReader) const override;
};
