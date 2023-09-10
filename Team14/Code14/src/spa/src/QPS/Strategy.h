#pragma once

#include "Result.h"
#include "Query.h"
#include "./PKB/PkbReader.h"

/*
 * Strategy interface for each type of clause e.g. UsesStrategy, FollowsStrategy, AssignPatternStrategy, etc
 */
class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void evaluateClause(Query& query, Result& result, std::shared_ptr<PkbReader> pkbReader) const = 0;
};
