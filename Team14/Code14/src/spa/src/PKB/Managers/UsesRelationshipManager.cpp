#include "UsesRelationshipManager.h"

UsesRelationshipManager::UsesRelationshipManager() : StmtToVarRelationshipManager<UsesRelationshipStore, UsesRelationship>() {};

void UsesRelationshipManager::storeUsesRelationship(std::shared_ptr<Statement> statement, std::shared_ptr<Variable> variable) {
    return this->storeRelationship(statement, variable);
}

std::vector<std::vector<Entity>> UsesRelationshipManager::getUsesStmtPair(StatementType type) const {
    return this->getRelationshipStmtPair(type);
}

std::vector<Entity> UsesRelationshipManager::getUsesTypeIdent(StatementType type, Variable& var) const {
    return this->getRelationshipTypeIdent(type, var);
}

std::vector<Entity> UsesRelationshipManager::getUsesStmt(StatementType type) const {
    return this->getRelationshipStmt(type);
}

std::vector<Entity> UsesRelationshipManager::getUsesVar(Statement& stmt) const {
    return this->getRelationshipVar(stmt);
}

bool UsesRelationshipManager::isStmtUsesVar(Statement& stmt, Variable& var) const {
    return this->isRelationship(stmt, var);
}

bool UsesRelationshipManager::hasUses(Statement& stmt) const {
    return this->hasRelationship(stmt);
}