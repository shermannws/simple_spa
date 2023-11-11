#pragma once

#include "QPS/Clauses/SuchThatClause.h"
#include "SuchThatStrategy.h"

/**
 * The Strategy class of Affects in SuchThatClause
 */
class AffectsSuchThatStrategy : public SuchThatStrategy {
public:
    /**
     * @brief Explicit constructor of AffectsSuchThatStrategy
     * @param pkbReader The shared pointer to the PKB reader
     */
    explicit AffectsSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader);

    /**
     * @brief Evaluates SuchThatClause that follows the syntax Affects(s,s)
     * @param leftRef The first parameter of the SuchThatClause to evaluate
     * @param rightRef The second parameter of the SuchThatClause to evaluate
     * @return The shared pointer to result of the SuchThatClause evaluation
     */
    std::shared_ptr<Result> evaluateSynSyn(Ref &leftRef, Ref &rightRef) const override;

    /**
     * @brief Evaluates SuchThatClause that follows the syntax Affects(s, )
     * @param leftRef The first parameter of the SuchThatClause to evaluate
     * @param rightRef The second parameter of the SuchThatClause to evaluate
     * @return The shared pointer to result of the SuchThatClause evaluation
     */
    std::shared_ptr<Result> evaluateSynAny(Ref &leftRef, Ref &rightRef) const override;

    /**
     * @brief Evaluates SuchThatClause that follows the syntax Affects( , s)
     * @param leftRef The first parameter of the SuchThatClause to evaluate
     * @param rightRef The second parameter of the SuchThatClause to evaluate
     * @return The shared pointer to result of the SuchThatClause evaluation
     */
    std::shared_ptr<Result> evaluateAnySyn(Ref &leftRef, Ref &rightRef) const override;

    /**
     * @brief Evaluates SuchThatClause that results in boolean
     * @param leftRef The first parameter of the SuchThatClause to evaluate
     * @param rightRef The second parameter of the SuchThatClause to evaluate
     * @return The shared pointer to result of the SuchThatClause evaluation
     */
    std::shared_ptr<Result> evaluateBoolean(Ref &leftRef, Ref &rightRef) const override;
};
