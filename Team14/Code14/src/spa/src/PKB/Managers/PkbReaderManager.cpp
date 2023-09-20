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

std::vector<Entity> PkbReaderManager::getAllAssign() const {
    return this->assignmentManager->getAllAssignStatements();
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
