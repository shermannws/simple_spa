#pragma once

#include "Strategy.h"

/**
 * @class The WithStratey class to evaluate WithClause
 */
class WithStrategy : public Strategy {
protected:
    /**
     * Shared pointer to the PKB reader which retrieves the required information for query evaluation
     */
    std::shared_ptr<PkbReader> pkbReader;

public:
    /**
     * @brief Explicit constructor of WithStrategy
     * @param pkbReader The shared pointer to the PKB reader
     */
    explicit WithStrategy(std::shared_ptr<PkbReader> pkbReader);

    /**
     * @brief Evaluates WithClause and returns a Result
     * @param clause The WithClause to evaluate
     * @return The result of the WithClause evaluation as a Result object
     */
    std::shared_ptr<Result> evaluateClause(std::shared_ptr<Clause> clause) const override;

    /**
     * Evaluates WithClause that has synonyms in both parameters
     * @param leftRef The first parameter of the WithClause to evaluate
     * @param rightRef The second parameter of the WithClause to evaluate
     * @return The result of the WithClause evaluation as a Result object
     */
    std::shared_ptr<Result> evaluateSynSyn(Ref &leftRef, Ref &rightRef) const;

    /**
     * Evaluates WithClause that has a synonym in one of the parameters
     * @param leftRef The first parameter of the WithClause to evaluate
     * @param rightRef The second parameter of the WithClause to evaluate
     * @return The result of the WithClause evaluation as a Result object
     */
    std::shared_ptr<Result> evaluateSynAny(Ref &leftRef, Ref &rightRef) const;

    /**
     * Evaluates WithClause that results in boolean
     * @param leftRef The first parameter of the WithClause to evaluate
     * @param rightRef The second parameter of the WithClause to evaluate
     * @return The result of the WithClause evaluation as a Result object
     */
    std::shared_ptr<Result> evaluateBoolean(Ref &leftRef, Ref &rightRef) const;

    /**
     * Joins two vectors of Entities based on the AttrName
     * @param v1 The first vector of Entities to join
     * @param a1 The AttrName of the first attrRef to join
     * @param v2 The second vector of Entities to join
     * @param a2 The AttrName of the second attrRef to join
     * @return The vector of vectors of Entity as a result of the join
     */
    std::vector<std::vector<Entity>> join(std::vector<Entity> v1, AttrName a1, std::vector<Entity> v2,
                                          AttrName a2) const;

    /**
     * Filters a vector of Entities based on a StringRep
     * @param v The vector of Entities to filter
     * @param a The AttrName of the attrRef to filter
     * @param rep The string representation of the value to filter with
     * @return The vector of Entities as a result of the join
     */
    std::vector<Entity> filter(std::vector<Entity> v, AttrName a, StringRep rep) const;
};