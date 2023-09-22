#pragma once

#include "Strategy.h"
#include "SuchThatClause.h"

class UsesSuchThatStrategy : public Strategy {
public:
    Result evaluateClause(std::shared_ptr<Clause> clause, std::shared_ptr<PkbReader> pkbReader) const override;
};
