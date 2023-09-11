#pragma once

#include "Strategy.h"

class AssignPatternStrategy : public Strategy {
public:
    Result evaluateClause(Clause& clause, std::shared_ptr<PkbReader> pkbReader) const override;
};
