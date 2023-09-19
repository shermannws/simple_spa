#pragma once

#include "Result.h"
#include "Clause.h"
#include "./PKB/PkbReader.h"

/*
 * Strategy interface for each type of clause e.g. UsesStrategy, FollowsStrategy, AssignPatternStrategy, etc
 */
class Strategy {
public:
    Strategy() = default;
    virtual ~Strategy() = default;
    virtual Result evaluateClause(std::shared_ptr<Clause> clause, std::shared_ptr<PkbReader> pkbReader) const = 0;
};
