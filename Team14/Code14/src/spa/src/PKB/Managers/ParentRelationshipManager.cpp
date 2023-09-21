#include "ParentRelationshipManager.h"

ParentRelationshipManager::ParentRelationshipManager()
    : parentRelationshipStore(std::make_shared<ParentRelationshipStore>(ParentRelationshipStore())) {}

void ParentRelationshipManager::storeParentRelationship(std::shared_ptr<Statement> parentStatement, std::shared_ptr<Statement> childStatement, bool isDirect) {
    parentRelationshipStore->storeRelationship(std::make_shared<ParentRelationship>(parentStatement, childStatement, isDirect));
}

bool ParentRelationshipManager::isParent(Statement& statement1, Statement& statement2, bool requireDirect) const {
    std::shared_ptr<ParentRelationship> parentRelationship = std::make_shared<ParentRelationship>(std::make_shared<Statement>(statement1), std::make_shared<Statement>(statement2), requireDirect);
    std::shared_ptr<ParentRelationship> relationship = parentRelationshipStore->getRelationship(parentRelationship);
    return relationship != nullptr && relationship->isDirect() >= requireDirect;
}