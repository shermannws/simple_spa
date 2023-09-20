#pragma once

#include "ModifiesRelationshipManager.h"

ModifiesRelationshipManager::ModifiesRelationshipManager()
    : modifiesRelationshipStore(std::make_shared<ModifiesRelationshipStore>()) {}

void ModifiesRelationshipManager::storeModifiesRelationship(std::shared_ptr<Statement> statement, std::shared_ptr<Variable> variable) {
    this->modifiesRelationshipStore->storeRelationship(std::make_shared<ModifiesRelationship>(statement, variable));
}

bool ModifiesRelationshipManager::isStmtModifiesVar(Statement& stmt, Variable& var) const {
    return modifiesRelationshipStore->getRelationship(std::make_shared<ModifiesRelationship>(std::make_shared<Statement>(stmt), std::make_shared<Variable>(var))) != nullptr;
}
