#pragma once

#include "Strategy.h"

/**
 * @class The PatternStrategy base class to evaluate PatternClause
 */
class PatternStrategy : public Strategy {
protected:
    /**
     * Shared pointer to the PKB reader which retrieves the required information for query evaluation
     */
    std::shared_ptr<PkbReader> pkbReader;

public:
    /**
     * @brief Explicit constructor of PatternStrategy
     * @param pkbReader The shared pointer to the PKB reader
     */
    explicit PatternStrategy(std::shared_ptr<PkbReader> pkbReader);

    /**
     * @brief Evaluates PatternClause that has wildcard as first parameter
     * @param secondArg The second argument of PatternClause to evaluate
     * @return The shared pointer to result of the PatternClause evaluation
     */
    virtual std::shared_ptr<Result> evaluateWildcard(ExpressionSpec &secondArg) const = 0;

    /**
     * @brief Evaluates PatternClause that has a synonym as the first parameter
     * @param secondArg The second argument of PatternClause to evaluate
     * @return The shared pointer to result of the PatternClause evaluation
     */
    virtual std::shared_ptr<Result> evaluateSyn(ExpressionSpec &secondArg) const = 0;

    /**
     * @brief Evaluates PatternClause that has an IDENT representing a variable as first parameter
     * @param firstArg The first argument of PatternClause to evaluate
     * @param secondArg The second argument of PatternClause to evaluate
     * @return The shared pointer to result of the PatternClause evaluation
     */
    virtual std::shared_ptr<Result> evaluateVarIdent(Ref &firstArg, ExpressionSpec &secondArg) const = 0;

    /**
     * @brief Evaluates PatternClause and returns the Result
     * @param clause The PatternClause to evaluate
     * @return The shared pointer to result of the PatternClause evaluation
     */
    std::shared_ptr<Result> evaluateClause(std::shared_ptr<Clause> clause) const override;
};
