#pragma once

#include "PatternStrategy.h"
#include "QPS/Clauses/PatternClause.h"

/**
 * The Strategy class of If Pattern clause
 */
class IfPatternStrategy : public PatternStrategy {
public:
    /**
     * @brief Explicit constructor of IfPatternStrategy
     * @param pkbReader The shared pointer to the PKB reader
     */
    explicit IfPatternStrategy(std::shared_ptr<PkbReader> pkbReader);

    /**
     * @brief Evaluates PatternClause that follows the syntax pattern i(_,_,_)
     * @param secondArg The second argument of PatternClause to evaluate
     * @return The shared pointer to result of the PatternClause evaluation
     */
    std::shared_ptr<Result> evaluateWildcard(ExpressionSpec &secondArg) const override;

    /**
     * @brief Evaluates PatternClause that follows the syntax pattern i(v,_,_)
     * @param secondArg The second argument of PatternClause to evaluate
     * @return The shared pointer to result of the PatternClause evaluation
     */
    std::shared_ptr<Result> evaluateSyn(ExpressionSpec &secondArg) const override;

    /**
     * @brief Evaluates PatternClause that follows the syntax pattern i("IDENT",_,_)
     * @param firstArg The first argument of PatternClause to evaluate
     * @param secondArg The second argument of PatternClause to evaluate
     * @return The shared pointer to result of the PatternClause evaluation
     */
    std::shared_ptr<Result> evaluateVarIdent(Ref &firstArg, ExpressionSpec &secondArg) const override;
};
