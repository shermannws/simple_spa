#pragma once

#include "SuchThatStrategy.h"
#include "QPS/Clauses/SuchThatClause.h"

/**
 * The Strategy class of Parent in SuchThatClause
 */
class ParentSuchThatStrategy : public SuchThatStrategy {
public:
    explicit ParentSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader);
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
