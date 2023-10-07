#include "ModifiesRelationshipManager.h"

ModifiesRelationshipManager::ModifiesRelationshipManager() : StmtToVarRelationshipManager() {};

void ModifiesRelationshipManager::storeModifiesRelationship(std::shared_ptr<Statement> statement, std::shared_ptr<Variable> variable) {
    return this->storeRelationship(statement, variable);
}

std::vector<std::vector<Entity>> ModifiesRelationshipManager::getModifiesStmtPair(StatementType type) const {
    return this->getRelationshipStmtPair(type);
}

std::vector<Entity> ModifiesRelationshipManager::getModifiesTypeIdent(StatementType type, Variable& var) const {
    return this->getRelationshipTypeIdent(type, var);
}

std::vector<Entity> ModifiesRelationshipManager::getModifiesStmt(StatementType type) const {
    return this->getRelationshipStmt(type);
}

std::vector<Entity> ModifiesRelationshipManager::getModifiesVar(Statement& stmt) const {
    return this->getRelationshipVar(stmt);
}

bool ModifiesRelationshipManager::isStmtModifiesVar(Statement& stmt, Variable& var) const {
    return this->isRelationship(stmt, var);
}

bool ModifiesRelationshipManager::hasModifies(Statement& stmt) const {
    return this->hasRelationship(stmt);
}