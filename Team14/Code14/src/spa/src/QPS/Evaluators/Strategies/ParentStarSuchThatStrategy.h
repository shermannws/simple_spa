#pragma once

#include "SuchThatStrategy.h"
#include "QPS/Clauses/SuchThatClause.h"

/**
 * The Strategy class of Parent in SuchThatClause
 */
class ParentStarSuchThatStrategy : public SuchThatStrategy {
public:
    /**
     * @brief Explicit constructor of ParentStarSuchThatStrategy
     * @param pkbReader The shared pointer to the PKB reader
     */
    explicit ParentStarSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader);

    /**
     * @brief Evaluates SuchThatClause that follows the syntax Parent*(s,s)
     * @param leftRef The first parameter of the SuchThatClause to evaluate
     * @param rightRef The second parameter of the SuchThatClause to evaluate
     * @return The result of the SuchThatClause evaluation as a Result object
     */
    std::shared_ptr<Result> evaluateSynSyn(Ref &leftRef, Ref &rightRef) const override;

    /**
     * @brief Evaluates SuchThatClause that follows the syntax Parent*(s, )
     * @param leftRef The first parameter of the SuchThatClause to evaluate
     * @param rightRef The second parameter of the SuchThatClause to evaluate
     * @return The result of the SuchThatClause evaluation as a Result object
     */
    std::shared_ptr<Result> evaluateSynAny(Ref &leftRef, Ref &rightRef) const override;

    /**
     * @brief Evaluates SuchThatClause that follows the syntax Parent*( , s)
     * @param leftRef The first parameter of the SuchThatClause to evaluate
     * @param rightRef The second parameter of the SuchThatClause to evaluate
     * @return The result of the SuchThatClause evaluation as a Result object
     */
    std::shared_ptr<Result> evaluateAnySyn(Ref &leftRef, Ref &rightRef) const override;

    /**
     * @brief Evaluates SuchThatClause that results in boolean
     * @param leftRef The first parameter of the SuchThatClause to evaluate
     * @param rightRef The second parameter of the SuchThatClause to evaluate
     * @return The result of the SuchThatClause evaluation as a Result object
     */
    std::shared_ptr<Result> evaluateBoolean(Ref &leftRef, Ref &rightRef) const override;
};
