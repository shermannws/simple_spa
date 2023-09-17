#include "ParentRelationshipManager.h"

ParentRelationshipManager::ParentRelationshipManager()
    : parentRelationshipStore(std::make_shared<ParentRelationshipStore>(ParentRelationshipStore())) {}

void ParentRelationshipManager::storeParentRelationship(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2) {
    parentRelationshipStore->storeRelationship(std::make_shared<ParentRelationship>(statement1, statement2));
}