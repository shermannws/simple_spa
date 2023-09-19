#pragma once

#include "Result.h"
#include "Clause.h"
#include "./PKB/PkbReader.h"

/*
 * Strategy interface for each type of clause e.g. UsesStrategy, FollowsStrategy, AssignPatternStrategy, etc
 */
class Strategy {
protected:
    // TODO: move this to util or make it static
    std::unordered_map<QueryEntityType, StatementType> stmtMap {
            {QueryEntityType::Assign, StatementType::Assign},
            {QueryEntityType::Print, StatementType::Print},
            {QueryEntityType::Read, StatementType::Read},
            {QueryEntityType::If, StatementType::If},
            {QueryEntityType::While, StatementType::While},
            {QueryEntityType::Call, StatementType::Call},
            {QueryEntityType::Stmt, StatementType::Stmt}
    };
public:
    Strategy() = default;
    virtual ~Strategy() = default;
    virtual Result evaluateClause(Clause& clause, std::shared_ptr<PkbReader> pkbReader) const = 0;
};
