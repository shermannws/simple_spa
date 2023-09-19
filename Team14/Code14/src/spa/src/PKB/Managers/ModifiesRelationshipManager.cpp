#pragma once

#include "ModifiesRelationshipManager.h"

ModifiesRelationshipManager::ModifiesRelationshipManager()
    : modifiesRelationshipStore(std::make_shared<ModifiesRelationshipStore>()) {}

void ModifiesRelationshipManager::storeModifiesRelationship(std::shared_ptr<Statement> statement, std::shared_ptr<Variable> variable) {
    this->modifiesRelationshipStore->storeRelationship(std::make_shared<ModifiesRelationship>(statement, variable));
}