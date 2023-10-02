#pragma once

#include "SuchThatStrategy.h"
#include "QPS/Clauses/SuchThatClause.h"

class UsesPSuchThatStrategy : public SuchThatStrategy {
public:
    Result evaluateSynSyn(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const override;

    Result evaluateSynIdent(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const override;

    Result evaluateSynWild(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const override;

    Result evaluateIdentSyn(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const override;

    Result evaluateIdentIdent(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const override;

    Result evaluateIdentWild(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const override;
};

