#pragma once

#include "PkbReaderManager.h"

PkbReaderManager::PkbReaderManager(
    std::shared_ptr<AssignmentManager> assignmentManager,
    std::shared_ptr<ConstantStore> constantStore,
    std::shared_ptr<ProcedureStore> procedureStore,
    std::shared_ptr<StatementStore> statementStore,
    std::shared_ptr<VariableStore> variableStore,
    std::shared_ptr<FollowsRelationshipManager> followsRelationshipManager,
    std::shared_ptr<UsesRelationshipManager> usesRelationshipManager,
    std::shared_ptr<ModifiesRelationshipManager> modifiesRelationshipManager,
    std::shared_ptr<ParentRelationshipManager> parentRelationshipManager)
    : assignmentManager(assignmentManager),
    constantStore(constantStore),
    procedureStore(procedureStore),
    statementStore(statementStore),
    variableStore(variableStore),
    followsRelationshipManager(followsRelationshipManager),
    usesRelationshipManager(usesRelationshipManager),
    modifiesRelationshipManager(modifiesRelationshipManager),
    parentRelationshipManager(parentRelationshipManager) {}

template <typename T>
std::vector<Entity> PkbReaderManager::getAllEntities(const std::shared_ptr<EntityStore<T>>& store) const {
    return store->getAllEntities();
}

std::vector<Entity> PkbReaderManager::getAllVariables() const {
    return this->getAllEntities<Variable>(this->variableStore);
}

std::vector<Entity> PkbReaderManager::getAllConstants() const {
    return this->getAllEntities<Constant>(this->constantStore);
}

std::vector<Entity> PkbReaderManager::getAllProcedures() const {
    return this->getAllEntities<Procedure>(this->procedureStore);
}

std::vector<Entity> PkbReaderManager::getAllStatements() const {
    return this->getAllEntities<Statement>(this->statementStore);
}

std::vector<std::vector<Entity>> PkbReaderManager::getUsesStmtPair(StatementType type) const {
    return this->usesRelationshipManager->getUsesStmtPair(type);
}

std::vector<Entity> PkbReaderManager::getUsesTypeIdent(StatementType type, Variable& var) const {
    return this->usesRelationshipManager->getUsesTypeIdent(type, var);
}

std::vector<Entity> PkbReaderManager::getUsesStmt(StatementType type) const {
    return this->usesRelationshipManager->getUsesStmt(type);
}

std::vector<Entity> PkbReaderManager::getUsesVar(Statement& stmt) const {
    return this->usesRelationshipManager->getUsesVar(stmt);
}

bool PkbReaderManager::isStmtUsesVar(Statement& stmt, Variable& var) const {
    return this->usesRelationshipManager->isStmtUsesVar(stmt, var);
}

bool PkbReaderManager::hasUses(Statement& stmt) const {
    return this->usesRelationshipManager->hasUses(stmt);
}

std::vector<std::vector<Entity>> PkbReaderManager::getFollowsPair(StatementType formerType, StatementType latterType) const {
    return this->followsRelationshipManager->getFollowsPair(formerType, latterType, true);
}

std::vector<std::vector<Entity>> PkbReaderManager::getFollowsStarPair(StatementType formerType, StatementType latterType) const {
    return this->followsRelationshipManager->getFollowsPair(formerType, latterType, false);
}

std::vector<Entity> PkbReaderManager::getFollowsTypeStmt(StatementType type, Statement& statement) const {
    return this->followsRelationshipManager->getFollowsTypeStmt(type, statement, true);
}

std::vector<Entity> PkbReaderManager::getFollowsStarTypeStmt(StatementType type, Statement& statement) const {
    return this->followsRelationshipManager->getFollowsTypeStmt(type, statement, false);
}

std::vector<Entity> PkbReaderManager::getFollowsTypeWildcard(StatementType type) const {
    return this->followsRelationshipManager->getFollowsTypeWildcard(type);
}

std::vector<Entity> PkbReaderManager::getFollowsStarTypeWildcard(StatementType type) const {
    return this->followsRelationshipManager->getFollowsTypeWildcard(type);
}

std::vector<Entity> PkbReaderManager::getFollowsStmtType(Statement& statement, StatementType type) const {
    return this->followsRelationshipManager->getFollowsStmtType(statement, type, true);
}

std::vector<Entity> PkbReaderManager::getFollowsStarStmtType(Statement& statement, StatementType type) const {
    return this->followsRelationshipManager->getFollowsStmtType(statement, type, false);
}

std::vector<Entity> PkbReaderManager::getFollowsWildcardType(StatementType type) const {
    return this->followsRelationshipManager->getFollowsWildcardType(type);
}

std::vector<Entity> PkbReaderManager::getFollowsStarWildcardType(StatementType type) const {
    return this->followsRelationshipManager->getFollowsWildcardType(type);
}

bool PkbReaderManager::isFollows(Statement& statement1, Statement& statement2) const {
    return this->followsRelationshipManager->isFollows(statement1, statement2, true);
}

bool PkbReaderManager::isFollowsStar(Statement& statement1, Statement& statement2) const {
    return this->followsRelationshipManager->isFollows(statement1, statement2, false);
}

bool PkbReaderManager::hasFollows() const {
    return this->followsRelationshipManager->hasFollows();
}

bool PkbReaderManager::hasLatterStmt(Statement& statement) const {
    return this->followsRelationshipManager->hasLatterStmt(statement);
}

bool PkbReaderManager::hasFormerStmt(Statement& statement) const {
    return this->followsRelationshipManager->hasFormerStmt(statement);
}

bool PkbReaderManager::hasLatterStarStmt(Statement& statement) const {
    return this->followsRelationshipManager->hasLatterStmt(statement);
}

bool PkbReaderManager::hasFormerStarStmt(Statement& statement) const {
    return this->followsRelationshipManager->hasFormerStmt(statement);
}

std::vector<std::vector<Entity>> PkbReaderManager::getModifiesStmtPair(StatementType type) const {
    return this->modifiesRelationshipManager->getModifiesStmtPair(type);
}

std::vector<Entity> PkbReaderManager::getModifiesTypeIdent(StatementType type, Variable& var) const {
    return this->modifiesRelationshipManager->getModifiesTypeIdent(type, var);
}

std::vector<Entity> PkbReaderManager::getModifiesStmt(StatementType type) const {
    return this->modifiesRelationshipManager->getModifiesStmt(type);
}

std::vector<Entity> PkbReaderManager::getModifiesVar(Statement& stmt) const {
    return this->modifiesRelationshipManager->getModifiesVar(stmt);
}

bool PkbReaderManager::isStmtModifiesVar(Statement& stmt, Variable& var) const {
    return this->modifiesRelationshipManager->isStmtModifiesVar(stmt, var);
}

bool PkbReaderManager::hasModifies(Statement& stmt) const {
    return this->modifiesRelationshipManager->hasModifies(stmt);
}

// Pattern queries i.e. pattern a (...,...)
// pattern a (_,_)
std::vector<Entity> PkbReaderManager::getAllAssign() const {
    return this->assignmentManager->getAllAssignStmts();
}

// pattern a (_, "x")
std::vector<Entity> PkbReaderManager::getAssignStmtsByRhs(Expression& rhs, bool hasRhsWildCard) const {
    return this->assignmentManager->getAssignStmtsByRhs(rhs, hasRhsWildCard);
}

// pattern a (v, _)
std::vector<std::vector<Entity>> PkbReaderManager::getAllAssignStmtVarPair() const {
    return this->assignmentManager->getAllAssignStmtVarPair();
}

// pattern a (v, "x")
std::vector<std::vector<Entity>> PkbReaderManager::getAssignStmtsVarPairByRhs(Expression& rhs, bool hasWildCard) const {
    return this->assignmentManager->getAssignStmtsVarPairByRhs(rhs, hasWildCard);
}

// pattern a ("x", _)
std::vector<Entity> PkbReaderManager::getAssignStmtsByLhs(Variable& lhs) const {
    return this->assignmentManager->getAssignStmtsByLhs(lhs);
}

// pattern a ("x", "x")
std::vector<Entity> PkbReaderManager::getAssignStmtsByLhsRhs(Variable& lhs, Expression& rhs, bool hasRhsWildCard) const {
    return this->assignmentManager->getAssignStmtsByLhsRhs(lhs, rhs, hasRhsWildCard);
}

std::vector<std::vector<Entity>> PkbReaderManager::getParentPair(StatementType formerType, StatementType latterType) const {
    return this->parentRelationshipManager->getParentPair(formerType, latterType, true);
}

std::vector<std::vector<Entity>> PkbReaderManager::getParentStarPair(StatementType formerType, StatementType latterType) const {
    return this->parentRelationshipManager->getParentPair(formerType, latterType, false);
}

std::vector<Entity> PkbReaderManager::getParentTypeStmt(StatementType type, Statement& statement) const {
    return this->parentRelationshipManager->getParentTypeStmt(type, statement, true);
}

std::vector<Entity> PkbReaderManager::getParentStarTypeStmt(StatementType type, Statement& statement) const {
    return this->parentRelationshipManager->getParentTypeStmt(type, statement, false);
}

std::vector<Entity> PkbReaderManager::getParentTypeWildcard(StatementType type) const {
    return this->parentRelationshipManager->getParentTypeWildcard(type);
}

std::vector<Entity> PkbReaderManager::getParentStarTypeWildcard(StatementType type) const {
    return this->parentRelationshipManager->getParentTypeWildcard(type);
}

std::vector<Entity> PkbReaderManager::getParentStmtType(Statement& statement, StatementType type) const {
    return this->parentRelationshipManager->getParentStmtType(statement, type, true);
}

std::vector<Entity> PkbReaderManager::getParentStarStmtType(Statement& statement, StatementType type) const {
    return this->parentRelationshipManager->getParentStmtType(statement, type, false);
}

std::vector<Entity> PkbReaderManager::getParentWildcardType(StatementType type) const {
    return this->parentRelationshipManager->getParentWildcardType(type);
}

std::vector<Entity> PkbReaderManager::getParentStarWildcardType(StatementType type) const {
    return this->parentRelationshipManager->getParentWildcardType(type);
}

bool PkbReaderManager::isParent(Statement& statement1, Statement& statement2) const {
    return this->parentRelationshipManager->isParent(statement1, statement2, true);
}

bool PkbReaderManager::isParentStar(Statement& statement1, Statement& statement2) const {
    return this->parentRelationshipManager->isParent(statement1, statement2, false);
}

bool PkbReaderManager::hasParent() const {
    return this->parentRelationshipManager->hasParent();
}

bool PkbReaderManager::hasChildStmt(Statement& statement) const {
    return this->parentRelationshipManager->hasChildStmt(statement);
}

bool PkbReaderManager::hasChildStarStmt(Statement& statement) const {
    return this->parentRelationshipManager->hasChildStmt(statement);
}

bool PkbReaderManager::hasParentStmt(Statement& statement) const {
    return this->parentRelationshipManager->hasParentStmt(statement);
}

bool PkbReaderManager::hasParentStarStmt(Statement& statement) const {
    return this->parentRelationshipManager->hasParentStmt(statement);
}

