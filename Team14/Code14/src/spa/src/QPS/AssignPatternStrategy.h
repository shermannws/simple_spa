#pragma once

#include "Strategy.h"
#include "PatternClause.h"

class AssignPatternStrategy : public Strategy {
public:
    Result evaluateClause(Clause& clause, std::shared_ptr<PkbReader> pkbReader) const override;
};