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

    std::vector<std::vector<Entity>> getUsesStmtPair(StatementType type) const;

    std::vector<Entity> getUsesTypeIdent(StatementType type, Variable& var) const;

    std::vector<Entity> getUsesStmt(StatementType type) const;

    std::vector<Entity> getUsesVar(Statement& stmt) const;

    bool isStmtUsesVar(Statement& stmt, Variable& var) const;

    bool hasUses(Statement& stmt) const;

    std::vector<std::vector<Entity>> getFollowsPair(StatementType formerType, StatementType latterType) const;

    std::vector<std::vector<Entity>> getFollowsStarPair(StatementType formerType, StatementType latterType) const;

    std::vector<Entity> getFollowsTypeStmt(StatementType type, Statement& statement) const;

    std::vector<Entity> getFollowsStarTypeStmt(StatementType type, Statement& statement) const;

    std::vector<Entity> getFollowsTypeWildcard(StatementType type) const;

    std::vector<Entity> getFollowsStarTypeWildcard(StatementType type) const;

    std::vector<Entity> getFollowsStmtType(Statement& statement, StatementType type) const;

    std::vector<Entity> getFollowsStarStmtType(Statement& statement, StatementType type) const;

    std::vector<Entity> getFollowsWildcardType(StatementType type) const;

    std::vector<Entity> getFollowsStarWildcardType(StatementType type) const;

    bool isFollows(Statement& statement1, Statement& statement2) const;

    bool isFollowsStar(Statement& statement1, Statement& statement2) const;

    bool hasFollows() const;
};