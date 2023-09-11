#include "FollowsRelationshipManager.h"

FollowsRelationshipManager::FollowsRelationshipManager() {
    this->followsRelationshipStore = std::make_shared<FollowsRelationshipStore>(FollowsRelationshipStore());;
}

void FollowsRelationshipManager::storeFollowsRelationship(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2) {
    followsRelationshipStore->storeRelationship(std::make_shared<FollowsRelationship>(statement1, statement2));
}

std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<Entity>>>>> FollowsRelationshipManager::getAllFollowsStatementPair() const {
    auto followsStatementPair = std::make_shared<std::vector<std::shared_ptr<std::vector<std::shared_ptr<Entity>>>>>();
    for (auto it = followsRelationshipStore->getBeginIterator(); it != followsRelationshipStore->getEndIterator(); it++) {
        auto followsStatementPairRow = std::make_shared<std::vector<std::shared_ptr<Entity>>>();
        followsStatementPairRow->push_back((*it)->getLeftEntity());
        followsStatementPairRow->push_back((*it)->getRightEntity());
        followsStatementPair->push_back(followsStatementPairRow);
    }
    return followsStatementPair;
}

std::shared_ptr<Entity> FollowsRelationshipManager::getFollowsByStatement(std::shared_ptr<Statement> statement) const {
    for (auto it = followsRelationshipStore->getBeginIterator(); it != followsRelationshipStore->getEndIterator(); it++) {
        if ((*it)->getRightEntity() == statement) {
            return (*it)->getLeftEntity();
        }
    }
    return nullptr;
}

std::shared_ptr<Entity> FollowsRelationshipManager::getFollowingStatement(std::shared_ptr<Statement> statement) const {
    for (auto it = followsRelationshipStore->getBeginIterator(); it != followsRelationshipStore->getEndIterator(); it++) {
        if ((*it)->getLeftEntity() == statement) {
            return (*it)->getRightEntity();
        }
    }
    return nullptr;
}

bool FollowsRelationshipManager::getIsFollows(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2) const {
    for (auto it = followsRelationshipStore->getBeginIterator(); it != followsRelationshipStore->getEndIterator(); it++) {
        if ((*it)->getLeftEntity() == statement1 && (*it)->getRightEntity() == statement2) {
            return true;
        }
    }
    return false;
}