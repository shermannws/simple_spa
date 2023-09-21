#include "FollowsRelationshipManager.h"

FollowsRelationshipManager::FollowsRelationshipManager()
    : followsRelationshipStore(std::make_shared<FollowsRelationshipStore>(FollowsRelationshipStore())) {}

void FollowsRelationshipManager::storeFollowsRelationship(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2, bool isDirect) {
    followsRelationshipStore->storeRelationship(std::make_shared<FollowsRelationship>(statement1, statement2, isDirect));
}

std::vector<std::vector<Entity>> FollowsRelationshipManager::getFollowsPair(StatementType formerType, StatementType latterType, bool requireDirect) const {
    auto matcher = [formerType, latterType, requireDirect](FollowsRelationship& followsRelationship) {
        return followsRelationship.isDirect() >= requireDirect && followsRelationship.getLeftObject()->isStatementType(formerType) && followsRelationship.getRightObject()->isStatementType(latterType);
    };
    return ManagerUtils::getEntityPairsFromStore<FollowsRelationshipStore, FollowsRelationship>(followsRelationshipStore,
                                                                                             matcher,
                                                                                             FollowsRelationship::getEntityPairFromRelationship);
}

std::vector<Entity> FollowsRelationshipManager::getFollowsTypeStmt(StatementType type, Statement& statement, bool requireDirect) const {
    auto matcher = [type, statement, requireDirect](FollowsRelationship& followsRelationship) {
        return followsRelationship.isDirect() >= requireDirect && *(followsRelationship.getRightObject()) == statement && followsRelationship.getLeftObject()->isStatementType(type);
    };

    return ManagerUtils::getEntitiesFromStore<FollowsRelationshipStore, FollowsRelationship>(followsRelationshipStore,
                                                                                             matcher,
                                                                                             FollowsRelationship::getLeftEntityFromRelationship);
}

std::vector<Entity> FollowsRelationshipManager::getFollowsTypeWildcard(StatementType type) const { // Same for Follows and Follows* since Follows* is a superset of Follows
    auto matcher = [type](FollowsRelationship& followsRelationship) {
        return followsRelationship.isDirect() && followsRelationship.getLeftObject()->isStatementType(type);
    };
    return ManagerUtils::getEntitiesFromStore<FollowsRelationshipStore, FollowsRelationship>(followsRelationshipStore,
                                                                                             matcher,
                                                                                             FollowsRelationship::getLeftEntityFromRelationship);
}

std::vector<Entity> FollowsRelationshipManager::getFollowsStmtType(Statement& statement, StatementType type, bool requireDirect) const {
    auto matcher = [statement, type, requireDirect](FollowsRelationship& followsRelationship) {
        return followsRelationship.isDirect() >= requireDirect && *(followsRelationship.getLeftObject()) == statement && followsRelationship.getRightObject()->isStatementType(type);
    };
    return ManagerUtils::getEntitiesFromStore<FollowsRelationshipStore, FollowsRelationship>(followsRelationshipStore,
                                                                                             matcher,
                                                                                             FollowsRelationship::getRightEntityFromRelationship);
}

std::vector<Entity> FollowsRelationshipManager::getFollowsWildcardType(StatementType type) const { // Same for Follows and Follows* since Follows* is a superset of Follows
    auto matcher = [type](FollowsRelationship& followsRelationship) {
        return followsRelationship.isDirect() && followsRelationship.getRightObject()->isStatementType(type);
    };
    return ManagerUtils::getEntitiesFromStore<FollowsRelationshipStore, FollowsRelationship>(followsRelationshipStore,
                                                                                             matcher,
                                                                                             FollowsRelationship::getRightEntityFromRelationship);
}

bool FollowsRelationshipManager::isFollows(Statement& statement1, Statement& statement2, bool requireDirect) const {
    std::shared_ptr<FollowsRelationship> followsRelationship = std::make_shared<FollowsRelationship>(std::make_shared<Statement>(statement1), std::make_shared<Statement>(statement2), requireDirect);
    std::shared_ptr<FollowsRelationship> relationship = followsRelationshipStore->getRelationship(followsRelationship);
    return relationship != nullptr && relationship->isDirect() >= requireDirect;
}

bool FollowsRelationshipManager::hasFollows() const {
    return !followsRelationshipStore->isEmpty();
}
