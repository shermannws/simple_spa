#pragma once

#include <memory>

#include "PKB/Managers/AssignmentManager.h"
#include "PKB/EntityStorage/ConstantStore.h"
#include "PKB/EntityStorage/ProcedureStore.h"
#include "PKB/EntityStorage/StatementStore.h"
#include "PKB/EntityStorage/VariableStore.h"
#include "PKB/RelationshipStorage/FollowsRelationshipStore.h"
#include "PKB/RelationshipStorage/UsesRelationshipStore.h"
#include "PKB/Managers/UsesRelationshipManager.h"

class PkbReaderManager {
private:
    std::shared_ptr<AssignmentManager> assignmentManager;

    std::shared_ptr<ConstantStore> constantStore;
    std::shared_ptr<ProcedureStore> procedureStore;
    std::shared_ptr<StatementStore> statementStore;
    std::shared_ptr<VariableStore> variableStore;

    std::shared_ptr<FollowsRelationshipStore> followsRelationshipStore;
    std::shared_ptr<UsesRelationshipManager> usesRelationshipManager;

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getAllEntities(const std::shared_ptr<EntityStorage>&) const;

public:
    PkbReaderManager(
            std::shared_ptr<AssignmentManager> assignmentManager,
            std::shared_ptr<ConstantStore> constantStore,
            std::shared_ptr<ProcedureStore> procedureStore,
            std::shared_ptr<StatementStore> statementStore,
            std::shared_ptr<VariableStore> variableStore,
            std::shared_ptr<FollowsRelationshipStore> followsRelationshipStore,
            std::shared_ptr<UsesRelationshipManager> usesRelationshipManager
    );

    std::shared_ptr<std::vector<std::shared_ptr<Statement>>> getAllAssign() const;

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getAllVariables() const;

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getAllConstants() const;

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getAllProcedures() const;

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getAllStatements() const;

    std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<Entity>>>>> getAllAssignVariablePair() const;

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getAllAssignByVariable(std::shared_ptr<Variable> variable) const;

};