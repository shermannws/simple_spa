#pragma once

#include "SuchThatStrategy.h"

class CallsSuchThatStrategy : public SuchThatStrategy {
public:
    /**
     * @brief constructor for CallsSuchThatStrategy
     * @param pkbReader The shared pointer to the PKB reader
     */
    explicit CallsSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader);

    /**
     * @brief Evaluates SuchThatClause that follows the syntax Calls(s,s)
     * @param leftRef The first parameter of the SuchThatClause to evaluate
     * @param rightRef The second parameter of the SuchThatClause to evaluate
     * @return The result of the SuchThatClause evaluation as a Result object
     */
    std::shared_ptr<Result> evaluateSynSyn(Ref &leftRef, Ref &rightRef) const override;

    /**
     * @brief Evaluates SuchThatClause that follows the syntax Calls(s, )
     * @param leftRef The first parameter of the SuchThatClause to evaluate
     * @param rightRef The second parameter of the SuchThatClause to evaluate
     * @return The result of the SuchThatClause evaluation as a Result object
     */
    std::shared_ptr<Result> evaluateSynAny(Ref &leftRef, Ref &rightRef) const override;

    /**
     * @brief Evaluates SuchThatClause that follows the syntax Calls( , s)
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
