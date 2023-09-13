#pragma once

#include "UsesRelationshipManager.h"

UsesRelationshipManager::UsesRelationshipManager() {
    this->usesRelationshipStore = std::make_shared<UsesRelationshipStore>(UsesRelationshipStore());;
}

void UsesRelationshipManager::storeUsesRelationship(std::shared_ptr<Statement> statement, std::shared_ptr<Variable> variable) {
    this->usesRelationshipStore->storeRelationship(std::make_shared<UsesRelationship>(UsesRelationship(statement, variable)));
}

std::vector<std::vector<Entity>> UsesRelationshipManager::getAllAssignVariable() const {
    auto pairs = std::vector<std::vector<Entity>>();
    for (auto it = usesRelationshipStore->getBeginIterator(); it != usesRelationshipStore->getEndIterator(); it++) {
        if (std::dynamic_pointer_cast<Statement>((*it)->getLeftEntity())->getStatementType() == StatementType::Assign) {
            pairs.push_back(std::vector<Entity>(std::vector<Entity>({*((*it)->getLeftEntity()),*((*it)->getRightEntity())})));
        }
    }
    return pairs;
}


std::vector<Entity> UsesRelationshipManager::getVariableAssignment(Variable& variable) const {
    auto result = std::vector<Entity>();
    for (auto it = usesRelationshipStore->getBeginIterator(); it != usesRelationshipStore->getEndIterator(); it++) {
        if (*((*it)->getRightEntity()) == variable && std::dynamic_pointer_cast<Statement>((*it)->getLeftEntity())->getStatementType() == StatementType::Assign) {
            result.push_back(*((*it)->getLeftEntity()));
        }
    }
    return result;
}