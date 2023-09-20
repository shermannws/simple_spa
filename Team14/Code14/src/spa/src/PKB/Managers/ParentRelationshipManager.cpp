#include "ParentRelationshipManager.h"

ParentRelationshipManager::ParentRelationshipManager()
    : parentRelationshipStore(std::make_shared<ParentRelationshipStore>(ParentRelationshipStore())) {}

void ParentRelationshipManager::storeParentRelationship(std::shared_ptr<Statement> parentStatement, std::shared_ptr<Statement> childStatement, bool isDirect) {
    parentRelationshipStore->storeRelationship(std::make_shared<ParentRelationship>(parentStatement, childStatement, isDirect));
}