#pragma once

#include "Strategy.h"

class SuchThatStrategy : public Strategy {
protected:
    std::shared_ptr<PkbReader> pkbReader;
public:
    explicit SuchThatStrategy(std::shared_ptr<PkbReader> pkbReader);
    virtual Result evaluateSynSyn(Ref &leftRef, Ref &rightRef) const = 0;
    virtual Result evaluateSynAny(Ref &leftRef, Ref &rightRef) const = 0;
    virtual Result evaluateAnySyn(Ref &leftRef, Ref &rightRef) const = 0;
    virtual Result evaluateBoolean(Ref &leftRef, Ref &rightRef) const = 0;
    Result evaluateClause(std::shared_ptr<Clause> clause) const override;
};
