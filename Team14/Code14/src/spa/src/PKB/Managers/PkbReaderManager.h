#pragma once

#include <memory>

#include "PKB/Managers/AssignmentManager.h"
#include "PKB/EntityStores/ConstantStore.h"
#include "PKB/EntityStores/ProcedureStore.h"
#include "PKB/EntityStores/StatementStore.h"
#include "PKB/EntityStores/VariableStore.h"
#include "PKB/Managers/FollowsRelationshipManager.h"
#include "PKB/Managers/UsesRelationshipManager.h"

class PkbReaderManager {
private:
    std::shared_ptr<AssignmentManager> assignmentManager;

    std::shared_ptr<ConstantStore> constantStore;
    std::shared_ptr<ProcedureStore> procedureStore;
    std::shared_ptr<StatementStore> statementStore;
    std::shared_ptr<VariableStore> variableStore;

    std::shared_ptr<FollowsRelationshipManager> followsRelationshipManager;
    std::shared_ptr<UsesRelationshipManager> usesRelationshipManager;

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getAllEntities(const std::shared_ptr<EntityStore>&) const;

public:
    PkbReaderManager(
            std::shared_ptr<AssignmentManager> assignmentManager,
            std::shared_ptr<ConstantStore> constantStore,
            std::shared_ptr<ProcedureStore> procedureStore,
            std::shared_ptr<StatementStore> statementStore,
            std::shared_ptr<VariableStore> variableStore,
            std::shared_ptr<FollowsRelationshipManager> followsRelationshipManager,
            std::shared_ptr<UsesRelationshipManager> usesRelationshipManager
    );

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getAllAssign() const;

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getAllVariables() const;

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getAllConstants() const;

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getAllProcedures() const;

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getAllStatements() const;

    std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<Entity>>>>> getAllUsesAssignVariablePair() const;

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getAllUsesAssignByVariable(std::shared_ptr<Variable> variable) const;

    std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<Entity>>>>> getAllFollowsStatementPair() const;

    std::shared_ptr<Entity> getFollowsByStatement(std::shared_ptr<Statement> statement) const; // Returns statement followed by (ahead) given statement

    std::shared_ptr<Entity> getFollowingStatement(std::shared_ptr<Statement> statement) const; // Returns statement following (behind) given statement

    bool getIsFollows(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2) const; // Returns true if statement1 follows statement2

};