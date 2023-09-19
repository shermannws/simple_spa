#include "FollowsRelationshipManager.h"

FollowsRelationshipManager::FollowsRelationshipManager()
    : followsRelationshipStore(std::make_shared<FollowsRelationshipStore>(FollowsRelationshipStore())) {}

void FollowsRelationshipManager::storeFollowsRelationship(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2, bool isDirect) {
    followsRelationshipStore->storeRelationship(std::make_shared<FollowsRelationship>(statement1, statement2, isDirect));
}

std::vector<std::vector<Entity>> FollowsRelationshipManager::getFollowsPair(StatementType formerType, StatementType latterType, bool requireDirect) const {
    auto followsPair = std::vector<std::vector<Entity>>();
    for (auto it = followsRelationshipStore->getBeginIterator(); it != followsRelationshipStore->getEndIterator(); it++) {
        if ((*it)->getLeftObject()->isStatementType(formerType) && (*it)->getRightObject()->isStatementType(latterType) && (*it)->isDirect() >= requireDirect) {
            followsPair.push_back(std::vector<Entity>{*((*it)->getLeftEntity()), *((*it)->getRightEntity())});
        }
    }
    return followsPair;
}

//std::vector<Entity> FollowsRelationshipManager::getFollowsTypeStmt(StatementType type, Statement& statement, bool requireDirect) const {
//    auto result = std::vector<Entity>();
//    for (auto it = followsRelationshipStore->getBeginIterator(); it != followsRelationshipStore->getEndIterator(); it++) {
//        if (*((*it)->getRightObject()) == statement && (*it)->getLeftObject()->isStatementType(type) && (*it)->isDirect() >= requireDirect) {
//            result.push_back(*((*it)->getLeftEntity()));
//        }
//    }
//    return result;
//}

std::vector<Entity> FollowsRelationshipManager::getFollowsTypeWildcard(StatementType type) const { // Same for Follows and Follows* since Follows* is a superset of Follows
    auto result = std::vector<Entity>();
    for (auto it = followsRelationshipStore->getBeginIterator(); it != followsRelationshipStore->getEndIterator(); it++) {
        if ((*it)->getLeftObject()->isStatementType(type) && (*it)->isDirect()) {
            result.push_back(*((*it)->getLeftEntity()));
        }
    }
    return result;
}

std::vector<Entity> FollowsRelationshipManager::getFollowsStmtType(Statement& statement, StatementType type, bool requireDirect) const {
    auto result = std::vector<Entity>();
    for (auto it = followsRelationshipStore->getBeginIterator(); it != followsRelationshipStore->getEndIterator(); it++) {
        if (*((*it)->getLeftObject()) == statement && (*it)->getRightObject()->isStatementType(type) && (*it)->isDirect() >= requireDirect) {
            result.push_back(*((*it)->getRightEntity()));
        }
    }
    return result;
}

std::vector<Entity> FollowsRelationshipManager::getFollowsWildcardType(StatementType type) const { // Same for Follows and Follows* since Follows* is a superset of Follows
    auto result = std::vector<Entity>();
    for (auto it = followsRelationshipStore->getBeginIterator();
         it != followsRelationshipStore->getEndIterator(); it++) {
        if ((*it)->getRightObject()->isStatementType(type) && (*it)->isDirect()) {
            result.push_back(*((*it)->getRightEntity()));
        }
    }
    return result;
}

bool FollowsRelationshipManager::isFollows(Statement& statement1, Statement& statement2, bool requireDirect) const {
    std::shared_ptr<FollowsRelationship> followsRelationship = std::make_shared<FollowsRelationship>(std::make_shared<Statement>(statement1), std::make_shared<Statement>(statement2), requireDirect);
    std::shared_ptr<FollowsRelationship> relationship = followsRelationshipStore->getRelationship(followsRelationship);
    return relationship != nullptr && relationship->isDirect() >= requireDirect;
}

bool FollowsRelationshipManager::hasFollows() const {
    return !followsRelationshipStore->isEmpty();
}


std::vector<Entity> FollowsRelationshipManager::getFollowsTypeStmt(StatementType type, Statement& statement, bool requireDirect) const {
    auto matcher = [type, statement, requireDirect](FollowsRelationship& followsRelationship) {
        return *(followsRelationship.getRightObject()) == statement && followsRelationship.getLeftObject()->isStatementType(type) && followsRelationship.isDirect() >= requireDirect;
    };

    auto getter = [](FollowsRelationship& followsRelationship) {
        return *followsRelationship.getLeftEntity();
    };
    return ManagerUtils::getFromStore<FollowsRelationshipStore, FollowsRelationship>(followsRelationshipStore, matcher, getter);
}
