#pragma once

#include "Strategy.h"
#include "QPS/Clauses/PatternClause.h"

/**
 * The Strategy class of Assign Pattern clause
 */
class AssignPatternStrategy : public Strategy {
    // TODO: create an abstract class of PatternStrategy similar to SuchThat
private:
    std::shared_ptr<PkbReader> pkbReader;
public:
    explicit AssignPatternStrategy(std::shared_ptr<PkbReader> pkbReader) : pkbReader(pkbReader) {};
    /**
     * @brief Evaluates the clause using pkbReader methods relating to AssignPattern
     * @param clause The shared pointer of the Clause to be evaluated
     * @param pkbReader The pkbReader of which the methods are to be called
     * @return The result of the clause evaluation
     */
    Result evaluateClause(std::shared_ptr<Clause> clause) const override;
};

