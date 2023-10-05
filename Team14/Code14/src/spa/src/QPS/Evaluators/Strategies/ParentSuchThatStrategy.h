#pragma once

#include "SuchThatStrategy.h"
#include "QPS/Clauses/SuchThatClause.h"

/**
 * The Strategy class of Parent in SuchThatClause
 */
class ParentSuchThatStrategy : public SuchThatStrategy {
public:
    Result evaluateSynSyn(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const override;

    Result evaluateSynInt(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const override;

    Result evaluateSynWild(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const override;

    Result evaluateIntSyn(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const override;

    Result evaluateWildSyn(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const override;

    Result evaluateIntWild(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const override;

    Result evaluateWildInt(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const override;

    Result evaluateIntInt(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const override;

    Result evaluateWildWild(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const override;
};
