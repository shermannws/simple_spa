#pragma once

#include "PatternStrategy.h"
#include "QPS/Clauses/PatternClause.h"

/**
 * The Strategy class of While Pattern clause
 */
class WhilePatternStrategy : public PatternStrategy {
public:
    /**
     * @brief Explicit constructor of WhilePatternStrategy
     * @param pkbReader The shared pointer to the PKB reader
     */
    explicit WhilePatternStrategy(std::shared_ptr<PkbReader> pkbReader);

    /**
     * @brief Evaluates PatternClause that follows the syntax pattern w(_,_)
     * @param secondArg The second argument of PatternClause to evaluate
     * @return The result of the PatternClause evaluation as a Result object
     */
    std::shared_ptr<Result> evaluateWildcard(ExpressionSpec &secondArg) const override;

    /**
     * @brief Evaluates PatternClause that follows the syntax pattern w(v,_)
     * @param secondArg The second argument of PatternClause to evaluate
     * @return The result of the PatternClause evaluation as a Result object
     */
    std::shared_ptr<Result> evaluateSyn(ExpressionSpec &secondArg) const override;

    /**
     * @brief Evaluates PatternClause that follows the syntax pattern w("var",_)
     * @param firstArg The first argument of PatternClause to evaluate
     * @param secondArg The second argument of PatternClause to evaluate
     * @return The result of the PatternClause evaluation as a Result object
     */
    std::shared_ptr<Result> evaluateVarIdent(Ref &firstArg, ExpressionSpec &secondArg) const override;
};