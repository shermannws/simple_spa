#pragma once

#include "Strategy.h"

class WithStrategy : public Strategy {
protected:
    /**
     * Shared pointer to the PKB reader which retrieves the required information for query evaluation
     */
    std::shared_ptr<PkbReader> pkbReader;

public:
    explicit WithStrategy(std::shared_ptr<PkbReader> pkbReader);

    std::shared_ptr<Result> evaluateClause(std::shared_ptr<Clause> clause) const override;

    std::shared_ptr<Result> evaluateSynSyn(Ref &leftRef, Ref &rightRef) const;

    std::shared_ptr<Result> evaluateSynAny(Ref &leftRef, Ref &rightRef) const;

    std::shared_ptr<Result> evaluateAnySyn(Ref &leftRef, Ref &rightRef) const;

    std::shared_ptr<Result> evaluateBoolean(Ref &leftRef, Ref &rightRef) const;

    std::vector<std::vector<Entity>> join(std::vector<Entity> v1, AttrName a1, std::vector<Entity> v2,
                                          AttrName a2) const;

    std::vector<Entity> join(std::vector<Entity> v, AttrName a, StringRep rep) const;
};