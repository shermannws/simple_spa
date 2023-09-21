#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include "PKB/Managers/ManagerUtils.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"

template <typename S, typename R>
class StmtToVarRelationshipManager {
private:
    std::shared_ptr<S> relationshipStore;
protected:
    StmtToVarRelationshipManager();

    void storeRelationship(std::shared_ptr<Statement> statement, std::shared_ptr<Variable> variable);

    std::vector<std::vector<Entity>> getRelationshipStmtPair(StatementType type) const;

    std::vector<Entity> getRelationshipTypeIdent(StatementType type, Variable& var) const;

    std::vector<Entity> getRelationshipStmt(StatementType type) const;

    std::vector<Entity> getRelationshipVar(Statement& stmt) const;

    bool isRelationship(Statement& stmt, Variable& var) const;

    bool hasRelationship(Statement& stmt) const;
};

#include "StmtToVarRelationshipManager.hpp"