#pragma once

#include <memory>

#include "PKB/Managers/AssignmentManager.h"
#include "PKB/EntityStores/ConstantStore.h"
#include "PKB/EntityStores/ProcedureStore.h"
#include "PKB/EntityStores/StatementStore.h"
#include "PKB/EntityStores/VariableStore.h"
#include "PKB/Managers/FollowsRelationshipManager.h"
#include "PKB/Managers/UsesRelationshipManager.h"
#include "PKB/Managers/ModifiesRelationshipManager.h"
#include "PKB/Managers/ParentRelationshipManager.h"

class PkbReaderManager {
private:
    std::shared_ptr<AssignmentManager> assignmentManager;

    std::shared_ptr<ConstantStore> constantStore;
    std::shared_ptr<ProcedureStore> procedureStore;
    std::shared_ptr<StatementStore> statementStore;
    std::shared_ptr<VariableStore> variableStore;

    std::shared_ptr<FollowsRelationshipManager> followsRelationshipManager;
    std::shared_ptr<UsesRelationshipManager> usesRelationshipManager;
    std::shared_ptr<ModifiesRelationshipManager> modifiesRelationshipManager;
    std::shared_ptr<ParentRelationshipManager> parentRelationshipManager;

    template <typename T>
    std::vector<Entity> getAllEntities(const std::shared_ptr<EntityStore<T>>&) const;

public:
    PkbReaderManager(
            std::shared_ptr<AssignmentManager> assignmentManager,
            std::shared_ptr<ConstantStore> constantStore,
            std::shared_ptr<ProcedureStore> procedureStore,
            std::shared_ptr<StatementStore> statementStore,
            std::shared_ptr<VariableStore> variableStore,
            std::shared_ptr<FollowsRelationshipManager> followsRelationshipManager,
            std::shared_ptr<UsesRelationshipManager> usesRelationshipManager,
            std::shared_ptr<ModifiesRelationshipManager> modifiesRelationshipManager,
            std::shared_ptr<ParentRelationshipManager> parentRelationshipManager
    );

    std::vector<Entity> getAllAssign() const;

    std::vector<Entity> getAllVariables() const;

    std::vector<Entity> getAllConstants() const;

    std::vector<Entity> getAllProcedures() const;

    std::vector<Entity> getAllStatements() const;

    std::vector<std::vector<Entity>> getAllUsesAssignVariablePair() const;

    std::vector<Entity> getAllUsesAssignByVariable(Variable& variable) const;

    std::vector<std::vector<Entity>> getAllFollowsStatementPair() const;

    std::vector<Entity> getFollowsByStatement(Statement& statement) const; // Returns statement followed by (ahead) given statement

    std::vector<Entity> getFollowingStatement(Statement& statement) const; // Returns statement following (behind) given statement

    bool getIsFollows(Statement& statement1, Statement& statement2) const; // Returns true if statement1 follows statement2

    std::vector<Entity> getAssignPatternStatements(Variable& variable, std::string& pattern, bool hasExpressionWildCard) const;

};