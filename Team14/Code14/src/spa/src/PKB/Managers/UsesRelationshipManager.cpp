#pragma once

#include "UsesRelationshipManager.h"

UsesRelationshipManager::UsesRelationshipManager()
    : usesRelationshipStore(std::make_shared<UsesRelationshipStore>(UsesRelationshipStore())) {}

void UsesRelationshipManager::storeUsesRelationship(std::shared_ptr<Statement> statement, std::shared_ptr<Variable> variable) {
    this->usesRelationshipStore->storeRelationship(std::make_shared<UsesRelationship>(UsesRelationship(statement, variable)));
}

std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<Entity>>>>> UsesRelationshipManager::getAllAssignVariable() const {
    auto pairs = std::make_shared<std::vector<std::shared_ptr<std::vector<std::shared_ptr<Entity>>>>>();
    for (auto it = usesRelationshipStore->getBeginIterator(); it != usesRelationshipStore->getEndIterator(); it++) {
        if (std::dynamic_pointer_cast<Statement>((*it)->getLeftEntity())->getStatementType() == StatementType::Assign) {
            pairs->push_back(std::make_shared<std::vector<std::shared_ptr<Entity>>>(std::vector<std::shared_ptr<Entity>>({(*it)->getLeftEntity(),(*it)->getRightEntity()})));
        }
    }
    return pairs;
}


std::shared_ptr<std::vector<std::shared_ptr<Entity>>> UsesRelationshipManager::getVariableAssignment(std::shared_ptr<Variable> variable) const {
    auto result = std::make_shared<std::vector<std::shared_ptr<Entity>>>();
    for (auto it = usesRelationshipStore->getBeginIterator(); it != usesRelationshipStore->getEndIterator(); it++) {
        if (*((*it)->getRightEntity()) == *variable && std::dynamic_pointer_cast<Statement>((*it)->getLeftEntity())->getStatementType() == StatementType::Assign) {
            result->push_back((*it)->getLeftEntity());
        }
    }
    return result;
}