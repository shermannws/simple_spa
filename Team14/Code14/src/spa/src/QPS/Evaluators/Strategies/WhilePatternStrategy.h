#pragma once

#include "QPS/Clauses/PatternClause.h"
#include "Strategy.h"

/**
 * The Strategy class of While Pattern clause
 */
class WhilePatternStrategy : public Strategy {
private:
    std::shared_ptr<PkbReader> pkbReader;

public:
    explicit WhilePatternStrategy(std::shared_ptr<PkbReader> pkbReader) : pkbReader(pkbReader){};
    /**
     * @brief Evaluates the clause using pkbReader methods relating to While Pattern
     * @param clause The shared pointer of the Clause to be evaluated
     * @param pkbReader The pkbReader of which the methods are to be called
     * @return The result of the clause evaluation
     */
    std::shared_ptr<Result> evaluateClause(std::shared_ptr<Clause> clause) const override;
};
