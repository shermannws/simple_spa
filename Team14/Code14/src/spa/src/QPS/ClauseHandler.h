#pragma once

#include "Result.h"
#include "Query.h"
#include "Strategy.h"
#include "AssignPatternStrategy.h"
#include "./PKB/PkbReader.h"


/*
 * The Context class in Strategy pattern, maintains a ref to a StrategyObject
 * Strategy Objects can be AssignPatternStrategy, UsesStrategy, FollowsStrategy,etc.
 */
class ClauseHandler {
private:
    std::unique_ptr<Strategy> strategy;
    std::shared_ptr<PkbReader> pkbReader;
public:
    explicit ClauseHandler(std::shared_ptr<PkbReader> pkbReader);
    void setStrategy(std::unique_ptr<Strategy> strategy);
    void processResult(Query& query, Result& result) const;
};