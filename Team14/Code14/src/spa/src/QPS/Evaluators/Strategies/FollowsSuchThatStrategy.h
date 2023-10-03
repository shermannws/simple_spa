#pragma once

#include "SuchThatStrategy.h"
#include "QPS/Clauses/SuchThatClause.h"

/**
 * The Strategy class of Follows in SuchThatClause
 */
class FollowsSuchThatStrategy : public SuchThatStrategy {
public:
    explicit FollowsSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader);
    Result evaluateSynSyn(Ref &leftRef, Ref &rightRef) const override;
    Result evaluateSynAny(Ref &leftRef, Ref &rightRef) const override;
    Result evaluateAnySyn(Ref &leftRef, Ref &rightRef) const override;
    Result evaluateBoolean(Ref &leftRef, Ref &rightRef) const override;
};
