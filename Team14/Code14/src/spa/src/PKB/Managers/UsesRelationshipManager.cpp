#pragma once

#include "UsesRelationshipManager.h"

UsesRelationshipManager::UsesRelationshipManager()
    : usesRelationshipStore(std::make_shared<UsesRelationshipStore>(UsesRelationshipStore())) {}

void UsesRelationshipManager::storeUsesRelationship(std::shared_ptr<Statement> statement, std::shared_ptr<Variable> variable) {
    this->usesRelationshipStore->storeRelationship(std::make_shared<UsesRelationship>(UsesRelationship(statement, variable)));
}

std::vector<std::vector<Entity>> UsesRelationshipManager::getUsesStmtPair(StatementType type) const {
    auto matcher = [type](UsesRelationship& usesRelationship) {
        return usesRelationship.getLeftObject()->isStatementType(type);
    };
    return ManagerUtils::getEntityPairsFromStore<UsesRelationshipStore, UsesRelationship>(usesRelationshipStore,
                                                                                         matcher,
                                                                                         UsesRelationship::getEntityPairFromRelationship);
}

std::vector<Entity> UsesRelationshipManager::getUsesTypeIdent(StatementType type, Variable& var) const {
    auto matcher = [type, var](UsesRelationship& usesRelationship) {
        return *(usesRelationship.getRightObject()) == var && usesRelationship.getLeftObject()->isStatementType(type);
    };
    return ManagerUtils::getEntitiesFromStore<UsesRelationshipStore, UsesRelationship>(usesRelationshipStore,
                                                                                         matcher,
                                                                                         UsesRelationship::getLeftEntityFromRelationship);
}

std::vector<Entity> UsesRelationshipManager::getUsesStmt(StatementType type) const {
    auto set = std::unordered_set<Entity>();

    auto matcher = [type, &set](UsesRelationship& usesRelationship) {
        return usesRelationship.getLeftObject()->isStatementType(type) && set.find(*(usesRelationship.getLeftEntity())) == set.end();
    };

    auto getter = [&set](UsesRelationship& usesRelationship) {
        set.insert(*(usesRelationship.getLeftEntity()));
        return *(usesRelationship.getLeftEntity());
    };
    return ManagerUtils::getEntitiesFromStore<UsesRelationshipStore, UsesRelationship>(usesRelationshipStore,
                                                                                         matcher,
                                                                                         getter);
}

std::vector<Entity> UsesRelationshipManager::getUsesVar(Statement& stmt) const {
    auto matcher = [&stmt](UsesRelationship& usesRelationship) {
        return *(usesRelationship.getLeftObject()) == stmt;
    };
    return ManagerUtils::getEntitiesFromStore<UsesRelationshipStore, UsesRelationship>(usesRelationshipStore,
                                                                                         matcher,
                                                                                         UsesRelationship::getRightEntityFromRelationship);
}

bool UsesRelationshipManager::isStmtUsesVar(Statement& stmt, Variable& var) const {
    return usesRelationshipStore->getRelationship(std::make_shared<UsesRelationship>(std::make_shared<Statement>(stmt), std::make_shared<Variable>(var))) != nullptr;
}

bool UsesRelationshipManager::hasUses(Statement& stmt) const {
    return std::find_if(usesRelationshipStore->getBeginIterator(), usesRelationshipStore->getEndIterator(), [&stmt](std::shared_ptr<UsesRelationship> relationship) {
        return *relationship->getLeftEntity() == stmt;
    }) != usesRelationshipStore->getEndIterator();
}