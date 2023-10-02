#pragma once

#include "SuchThatStrategy.h"
#include "QPS/Clauses/SuchThatClause.h"

/**
 * The Strategy class of Follows* in SuchThatClause
 */
class FollowsStarSuchThatStrategy : public SuchThatStrategy {
public:
    explicit FollowsStarSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader);
    Result evaluateSynSyn(Ref &leftRef, Ref &rightRef) const override;

    Result evaluateSynInt(Ref &leftRef, Ref &rightRef) const override;

    Result evaluateSynWild(Ref &leftRef, Ref &rightRef) const override;

    Result evaluateIntSyn(Ref &leftRef, Ref &rightRef) const override;

    Result evaluateWildSyn(Ref &leftRef, Ref &rightRef) const override;

    Result evaluateIntWild(Ref &leftRef, Ref &rightRef) const override;

    Result evaluateWildInt(Ref &leftRef, Ref &rightRef) const override;

    Result evaluateIntInt(Ref &leftRef, Ref &rightRef) const override;

    Result evaluateWildWild(Ref &leftRef, Ref &rightRef) const override;
};
