#pragma once

#include "Strategy.h"

class AssignPatternStrategy : public Strategy {
public:
    void evaluateClause(Query& query, Result& result, std::shared_ptr<PkbReader> pkbReader) const override;
};
