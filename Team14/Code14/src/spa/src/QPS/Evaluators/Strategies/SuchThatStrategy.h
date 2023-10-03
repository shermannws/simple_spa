#pragma once

#include "Strategy.h"

class SuchThatStrategy : public Strategy {
public:
    virtual Result evaluateSynSyn(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const = 0;
    virtual Result evaluateIntWild(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const = 0;
    virtual Result evaluateSynWild(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const = 0;
    virtual Result evaluateIntSyn(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const = 0;
    virtual Result evaluateSynIdent(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const;
    virtual Result evaluateIntIdent(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const;
    virtual Result evaluateSynInt(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const;
    virtual Result evaluateWildSyn(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const;
    virtual Result evaluateWildInt(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const;
    virtual Result evaluateIntInt(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const;
    virtual Result evaluateWildWild(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const;

    Result evaluateClause(std::shared_ptr<Clause> clause, std::shared_ptr<PkbReader> pkbReader) const override;
};
