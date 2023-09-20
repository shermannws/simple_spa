#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "PKB/RelationshipStores/UsesRelationshipStore.h"
#include "PKB/Managers/AssignmentManager.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "PKB/Relationships/UsesRelationship.h"

class UsesRelationshipManager {
private:
    std::shared_ptr<UsesRelationshipStore> usesRelationshipStore;
public:
    UsesRelationshipManager();

    void storeUsesRelationship(std::shared_ptr<Statement> statement, std::shared_ptr<Variable> variable);

    std::vector<std::vector<Entity>> getUsesStmtPair(StatementType type) const;

    std::vector<Entity> getUsesTypeIdent(StatementType type, Variable& var) const;

    std::vector<Entity> getUsesStmt(StatementType type) const;

    std::vector<Entity> getUsesVar(Statement& stmt) const;

    bool isStmtUsesVar(Statement& stmt, Variable& var) const;

    bool hasUses(Statement& stmt) const;
};
