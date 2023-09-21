#pragma once

#include "ModifiesRelationshipManager.h"

ModifiesRelationshipManager::ModifiesRelationshipManager()
    : modifiesRelationshipStore(std::make_shared<ModifiesRelationshipStore>()) {}

void ModifiesRelationshipManager::storeModifiesRelationship(std::shared_ptr<Statement> statement, std::shared_ptr<Variable> variable) {
    this->modifiesRelationshipStore->storeRelationship(std::make_shared<ModifiesRelationship>(statement, variable));
}

std::vector<std::vector<Entity>> ModifiesRelationshipManager::getModifiesStmtPair(StatementType type) const {
    auto matcher = [type](ModifiesRelationship& modifiesRelationship) {
        return modifiesRelationship.getLeftObject()->isStatementType(type);
    };
    return ManagerUtils::getEntityPairsFromStore<ModifiesRelationshipStore, ModifiesRelationship>(modifiesRelationshipStore,
                                                                                          matcher,
                                                                                          ModifiesRelationship::getEntityPairFromRelationship);
}

std::vector<Entity> ModifiesRelationshipManager::getModifiesTypeIdent(StatementType type, Variable& var) const {
    auto matcher = [type, var](ModifiesRelationship& modifiesRelationship) {
        return *(modifiesRelationship.getRightObject()) == var && modifiesRelationship.getLeftObject()->isStatementType(type);
    };
    return ManagerUtils::getEntitiesFromStore<ModifiesRelationshipStore, ModifiesRelationship>(modifiesRelationshipStore,
                                                                                          matcher,
                                                                                          ModifiesRelationship::getLeftEntityFromRelationship);
}

std::vector<Entity> ModifiesRelationshipManager::getModifiesStmt(StatementType type) const {
    auto set = std::unordered_set<Entity>();

    auto matcher = [type, &set](ModifiesRelationship& modifiesRelationship) {
        return modifiesRelationship.getLeftObject()->isStatementType(type) && set.find(*(modifiesRelationship.getLeftEntity())) == set.end();
    };

    auto getter = [&set](ModifiesRelationship& modifiesRelationship) {
        set.insert(*(modifiesRelationship.getLeftEntity()));
        return *(modifiesRelationship.getLeftEntity());
    };
    return ManagerUtils::getEntitiesFromStore<ModifiesRelationshipStore, ModifiesRelationship>(modifiesRelationshipStore,
                                                                                          matcher,
                                                                                          getter);
}

std::vector<Entity> ModifiesRelationshipManager::getModifiesVar(Statement& stmt) const {
    auto matcher = [&stmt](ModifiesRelationship& modifiesRelationship) {
        return *(modifiesRelationship.getLeftObject()) == stmt;
    };
    return ManagerUtils::getEntitiesFromStore<ModifiesRelationshipStore, ModifiesRelationship>(modifiesRelationshipStore,
                                                                                          matcher,
                                                                                          ModifiesRelationship::getRightEntityFromRelationship);
}

bool ModifiesRelationshipManager::isStmtModifiesVar(Statement& stmt, Variable& var) const {
    return modifiesRelationshipStore->getRelationship(std::make_shared<ModifiesRelationship>(std::make_shared<Statement>(stmt), std::make_shared<Variable>(var))) != nullptr;
}

bool ModifiesRelationshipManager::hasModifies(Statement& stmt) const {
    return std::find_if(modifiesRelationshipStore->getBeginIterator(), modifiesRelationshipStore->getEndIterator(), [&stmt](std::shared_ptr<ModifiesRelationship> relationship) {
        return *(relationship->getLeftObject()) == stmt;
    }) != modifiesRelationshipStore->getEndIterator();
}