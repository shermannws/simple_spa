#pragma once

#include "PatternStrategy.h"
#include "QPS/Clauses/PatternClause.h"

/**
 * The Strategy class of Assign Pattern clause
 */
class AssignPatternStrategy : public PatternStrategy {
public:
    /**
     * @brief Explicit constructor of AssignPatternStrategy
     * @param pkbReader The shared pointer to the PKB reader
     */
    explicit AssignPatternStrategy(std::shared_ptr<PkbReader> pkbReader);

    /**
     * @brief Evaluates PatternClause that follows the syntax pattern a(_,_)
     * @param secondArg The second argument of PatternClause to evaluate
     * @return The shared pointer to result of the PatternClause evaluation
     */
    std::shared_ptr<Result> evaluateWildcard(ExpressionSpec &secondArg) const override;

    /**
     * @brief Evaluates PatternClause that follows the syntax pattern a(v,_)
     * @param secondArg The second argument of PatternClause to evaluate
     * @return The shared pointer to result of the PatternClause evaluation
     */
    std::shared_ptr<Result> evaluateSyn(ExpressionSpec &secondArg) const override;

    /**
     * @brief Evaluates PatternClause that follows the syntax pattern a("IDENT",expression-spec)
     * @param firstArg The first argument of PatternClause to evaluate
     * @param secondArg The second argument of PatternClause to evaluate
     * @return The shared pointer to result of the PatternClause evaluation
     */
    std::shared_ptr<Result> evaluateVarIdent(Ref &firstArg, ExpressionSpec &secondArg) const override;
};
