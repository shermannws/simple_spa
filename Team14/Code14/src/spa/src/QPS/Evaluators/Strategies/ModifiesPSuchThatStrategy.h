#pragma once

#include "SuchThatStrategy.h"
#include "QPS/Clauses/SuchThatClause.h"

class ModifiesPSuchThatStrategy : public SuchThatStrategy {
public:
    explicit ModifiesPSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader);
    Result evaluateSynSyn(Ref &leftRef, Ref &rightRef) const override;

    Result evaluateSynIdent(Ref &leftRef, Ref &rightRef) const override;

    Result evaluateSynWild(Ref &leftRef, Ref &rightRef) const override;

    Result evaluateIdentSyn(Ref &leftRef, Ref &rightRef) const override;

    Result evaluateIdentIdent(Ref &leftRef, Ref &rightRef) const override;

    Result evaluateIdentWild(Ref &leftRef, Ref &rightRef) const override;
};
