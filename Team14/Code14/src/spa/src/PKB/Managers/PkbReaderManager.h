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

    bool hasFollowsStar() const;

    bool hasLatterStmt(Statement& statement) const;

    bool hasFormerStmt(Statement& statement) const;

    bool hasLatterStarStmt(Statement& statement) const;

    bool hasFormerStarStmt(Statement& statement) const;

    std::vector<std::vector<Entity>> getModifiesStmtPair(StatementType type) const;

    std::vector<Entity> getModifiesTypeIdent(StatementType type, Variable& var) const;

    std::vector<Entity> getModifiesStmt(StatementType type) const;

    std::vector<Entity> getModifiesVar(Statement& stmt) const;

    bool isStmtModifiesVar(Statement& stmt, Variable& var) const;

    bool hasModifies(Statement& stmt) const;

    // pattern a (_,_)
    std::vector<Entity> getAllAssign() const;

    // pattern a (_, "x")
    std::vector<Entity> getAssignStmtsByRhs(std::string& rhs, bool hasRhsWildCard) const;

    // pattern a (v, _)
    std::vector<std::vector<Entity>> getAllAssignStmtVarPair() const;

    // pattern a (v, "x")
    std::vector<std::vector<Entity>> getAssignStmtsVarPairByRhs(std::string& rhs, bool hasWildCard) const;

    // pattern a ("x", _)
    std::vector<Entity> getAssignStmtsByLhs(Variable& lhs) const;

    // pattern a ("x", "x")
    std::vector<Entity> getAssignStmtsByLhsRhs(Variable& lhs, std::string& rhs, bool hasRhsWildCard) const;

    std::vector<std::vector<Entity>> getParentPair(StatementType formerType, StatementType latterType) const;

    std::vector<std::vector<Entity>> getParentStarPair(StatementType formerType, StatementType latterType) const;

    std::vector<Entity> getParentTypeStmt(StatementType type, Statement& statement) const;

    std::vector<Entity> getParentStarTypeStmt(StatementType type, Statement& statement) const;

    std::vector<Entity> getParentTypeWildcard(StatementType type) const;

    std::vector<Entity> getParentStarTypeWildcard(StatementType type) const;

    std::vector<Entity> getParentStmtType(Statement& statement, StatementType type) const;

    std::vector<Entity> getParentStarStmtType(Statement& statement, StatementType type) const;

    std::vector<Entity> getParentWildcardType(StatementType type) const;

    std::vector<Entity> getParentStarWildcardType(StatementType type) const;

    bool isParent(Statement& statement1, Statement& statement2) const;

    bool isParentStar(Statement& statement1, Statement& statement2) const;

    bool hasParent() const;

    bool hasParentStar() const;

    bool hasParentStmt(Statement& statement) const;

    bool hasParentStarStmt(Statement& statement) const;

    bool hasChildStmt(Statement& statement) const;

    bool hasChildStarStmt(Statement& statement) const;

};