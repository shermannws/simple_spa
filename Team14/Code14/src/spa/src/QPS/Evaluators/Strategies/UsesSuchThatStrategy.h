#pragma once

#include "SuchThatStrategy.h"
#include "QPS/Clauses/SuchThatClause.h"

/**
 * The Strategy class of Uses in SuchThatClause
 */
class UsesSuchThatStrategy : public SuchThatStrategy {
public:
    Result evaluateSynSyn(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const override;

    Result evaluateSynIdent(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const override;

    Result evaluateSynWild(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const override;

    Result evaluateIntSyn(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const override;

    Result evaluateIntIdent(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const override;

    Result evaluateIntWild(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const override;
};
