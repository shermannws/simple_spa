#pragma once

#include "UsesRelationshipManager.h"

UsesRelationshipManager::UsesRelationshipManager()
    : usesRelationshipStore(std::make_shared<UsesRelationshipStore>(UsesRelationshipStore())) {}

void UsesRelationshipManager::storeUsesRelationship(std::shared_ptr<Statement> statement, std::shared_ptr<Variable> variable) {
    this->usesRelationshipStore->storeRelationship(std::make_shared<UsesRelationship>(UsesRelationship(statement, variable)));
}

std::vector<std::vector<Entity>> UsesRelationshipManager::getUsesStmtPair(StatementType type) const {
    auto pairs = std::vector<std::vector<Entity>>();
    for (auto it = usesRelationshipStore->getBeginIterator(); it != usesRelationshipStore->getEndIterator(); it++) {
        if ((*it)->getLeftObject()->isStatementType(type)) {
            pairs.push_back(std::vector<Entity>(std::vector<Entity>({*((*it)->getLeftEntity()),*((*it)->getRightEntity())})));
        }
    }
    return pairs;
}

std::vector<Entity> UsesRelationshipManager::getUsesTypeIdent(StatementType type, Variable& var) const {
    auto result = std::vector<Entity>();
    for (auto it = usesRelationshipStore->getBeginIterator(); it != usesRelationshipStore->getEndIterator(); it++) {
        if (*((*it)->getRightObject()) == var && (*it)->getLeftObject()->isStatementType(type)) {
            result.push_back(*((*it)->getLeftEntity()));
        }
    }
    return result;
}

std::vector<Entity> UsesRelationshipManager::getUsesStmt(StatementType type) const {
    auto result = std::vector<Entity>();
    auto set = std::unordered_set<Entity>();
    for (auto it = usesRelationshipStore->getBeginIterator(); it != usesRelationshipStore->getEndIterator(); it++) {
        if ((*it)->getLeftObject()->isStatementType(type) && set.find(*((*it)->getLeftEntity())) == set.end()) {
            result.push_back(*((*it)->getLeftEntity()));
            set.insert(*((*it)->getLeftEntity()));
        }
    }
    return result;
}

std::vector<Entity> UsesRelationshipManager::getUsesVar(Statement& stmt) const {
    auto result = std::vector<Entity>();
    for (auto it = usesRelationshipStore->getBeginIterator(); it != usesRelationshipStore->getEndIterator(); it++) {
        if (*((*it)->getLeftObject()) == stmt) {
            result.push_back(*((*it)->getRightEntity()));
        }
    }
    return result;
}

bool UsesRelationshipManager::isStmtUsesVar(Statement& stmt, Variable& var) const {
    return usesRelationshipStore->getRelationship(std::make_shared<UsesRelationship>(std::make_shared<Statement>(stmt), std::make_shared<Variable>(var))) != nullptr;
}

bool UsesRelationshipManager::hasUses(Statement& stmt) const {
    return std::find_if(usesRelationshipStore->getBeginIterator(), usesRelationshipStore->getEndIterator(), [&stmt](std::shared_ptr<UsesRelationship> relationship) {
        return *relationship->getLeftEntity() == stmt;
    }) != usesRelationshipStore->getEndIterator();
}