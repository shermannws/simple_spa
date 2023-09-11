#pragma once

#include "Strategy.h"

class AssignPatternStrategy : public Strategy {
public:
    Result evaluateClause(Query& query, std::shared_ptr<PkbReader> pkbReader) const override;
};
