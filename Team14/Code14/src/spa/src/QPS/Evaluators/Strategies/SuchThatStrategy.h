#pragma once

#include "Strategy.h"

class SuchThatStrategy : public Strategy {
protected:
    std::shared_ptr<PkbReader> pkbReader;
public:
    explicit SuchThatStrategy(std::shared_ptr<PkbReader> pkbReader);
    virtual Result evaluateSynSyn(Ref &leftRef, Ref &rightRef) const = 0;
    virtual Result evaluateSynWild(Ref &leftRef, Ref &rightRef) const = 0;
    virtual Result evaluateIntWild(Ref &leftRef, Ref &rightRef) const;
    virtual Result evaluateIntSyn(Ref &leftRef, Ref &rightRef) const;
    virtual Result evaluateSynIdent(Ref &leftRef, Ref &rightRef) const;
    virtual Result evaluateIntIdent(Ref &leftRef, Ref &rightRef) const;
    virtual Result evaluateSynInt(Ref &leftRef, Ref &rightRef) const;
    virtual Result evaluateWildSyn(Ref &leftRef, Ref &rightRef) const;
    virtual Result evaluateWildInt(Ref &leftRef, Ref &rightRef) const;
    virtual Result evaluateIntInt(Ref &leftRef, Ref &rightRef) const;
    virtual Result evaluateWildWild(Ref &leftRef, Ref &rightRef) const;
    virtual Result evaluateIdentSyn(Ref &leftRef, Ref &rightRef) const;
    virtual Result evaluateIdentIdent(Ref &leftRef, Ref &rightRef) const;
    virtual Result evaluateIdentWild(Ref &leftRef, Ref &rightRef) const;


    Result evaluateClause(std::shared_ptr<Clause> clause) const override;
};
