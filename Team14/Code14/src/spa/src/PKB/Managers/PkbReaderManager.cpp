#pragma once

#include "PkbReaderManager.h"

PkbReaderManager::PkbReaderManager(
    std::shared_ptr<AssignmentManager> assignmentManager,
    std::shared_ptr<ConstantStore> constantStore,
    std::shared_ptr<ProcedureStore> procedureStore,
    std::shared_ptr<StatementStore> statementStore,
    std::shared_ptr<VariableStore> variableStore,
    std::shared_ptr<FollowsRelationshipManager> followsRelationshipManager,
    std::shared_ptr<UsesRelationshipManager> usesRelationshipManager)
    : assignmentManager(assignmentManager),
    constantStore(constantStore),
    procedureStore(procedureStore),
    statementStore(statementStore),
    variableStore(variableStore),
    followsRelationshipManager(followsRelationshipManager),
    usesRelationshipManager(usesRelationshipManager) {}

std::shared_ptr<std::vector<std::shared_ptr<Entity>>> PkbReaderManager::getAllEntities(const std::shared_ptr<EntityStore>& store) const {
    return store->getAllEntities();
}

std::shared_ptr<std::vector<std::shared_ptr<Entity>>> PkbReaderManager::getAllAssign() const {
    return this->assignmentManager->getAllAssignStatements();
}

std::shared_ptr<std::vector<std::shared_ptr<Entity>>> PkbReaderManager::getAllVariables() const {
    return this->getAllEntities(this->variableStore);
}

std::shared_ptr<std::vector<std::shared_ptr<Entity>>> PkbReaderManager::getAllConstants() const {
    return this->getAllEntities(this->constantStore);
}

std::shared_ptr<std::vector<std::shared_ptr<Entity>>> PkbReaderManager::getAllProcedures() const {
    return this->getAllEntities(this->procedureStore);
}

std::shared_ptr<std::vector<std::shared_ptr<Entity>>> PkbReaderManager::getAllStatements() const {
    return this->getAllEntities(this->statementStore);
}

std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<Entity>>>>> PkbReaderManager::getAllUsesAssignVariablePair() const {
    return this->usesRelationshipManager->getAllAssignVariable();
}

std::shared_ptr<std::vector<std::shared_ptr<Entity>>> PkbReaderManager::getAllUsesAssignByVariable(std::shared_ptr<Variable> variable) const {
    return this->usesRelationshipManager->getVariableAssignment(variable);
}

std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<Entity>>>>> PkbReaderManager::getAllFollowsStatementPair() const {
    return this->followsRelationshipManager->getAllFollowsStatementPair();
}

std::shared_ptr<Entity> PkbReaderManager::getFollowsByStatement(std::shared_ptr<Statement> statement) const {
    return this->followsRelationshipManager->getFollowsByStatement(statement);
}

std::shared_ptr<Entity> PkbReaderManager::getFollowingStatement(std::shared_ptr<Statement> statement) const {
    return this->followsRelationshipManager->getFollowingStatement(statement);
}

bool PkbReaderManager::getIsFollows(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2) const {
    return this->followsRelationshipManager->getIsFollows(statement1, statement2);
}
