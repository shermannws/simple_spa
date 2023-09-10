#pragma once

#include "PkbReaderManager.h"

PkbReaderManager::PkbReaderManager(
        std::shared_ptr<AssignmentManager> assignmentManager,
        std::shared_ptr<ConstantStore> constantStore,
        std::shared_ptr<ProcedureStore> procedureStore,
        std::shared_ptr<StatementStore> statementStore,
        std::shared_ptr<VariableStore> variableStore,
        std::shared_ptr<FollowsRelationshipStore> followsRelationshipStore,
        std::shared_ptr<UsesRelationshipManager> usesRelationshipManager
) {
    this->assignmentManager = assignmentManager;
    this->constantStore = constantStore;
    this->procedureStore = procedureStore;
    this->statementStore = statementStore;
    this->variableStore = variableStore;
    this->followsRelationshipStore = followsRelationshipStore;
    this->usesRelationshipManager = usesRelationshipManager;
};

std::shared_ptr<std::vector<std::shared_ptr<Entity>>> PkbReaderManager::getAllEntities(const std::shared_ptr<EntityStorage>& store) const {
    return store->getAllEntities();
}

std::shared_ptr<std::vector<std::shared_ptr<Statement>>> PkbReaderManager::getAllAssign() const {
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

std::shared_ptr<std::vector<std::shared_ptr<std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>>>>> PkbReaderManager::getAllAssignVariablePair() const {
    return this->usesRelationshipManager->getAllAssignVariable();
}

std::shared_ptr<std::vector<std::shared_ptr<std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>>>>> PkbReaderManager::getAllAssignByVariable(std::shared_ptr<Variable> variable) const {
    return this->usesRelationshipManager->getVariableAssignment(variable);
}
