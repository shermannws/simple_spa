#include "FollowsRelationshipManager.h"

FollowsRelationshipManager::FollowsRelationshipManager() {
    this->followsRelationshipStore = std::make_shared<FollowsRelationshipStore>(FollowsRelationshipStore());;
}

void FollowsRelationshipManager::storeFollowsRelationship(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2) {
    followsRelationshipStore->storeRelationship(std::make_shared<FollowsRelationship>(statement1, statement2));
}

std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<Statement>>>>> FollowsRelationshipManager::getAllFollowsStatementPair() const {
    auto followsStatementPair = std::make_shared<std::vector<std::shared_ptr<std::vector<std::shared_ptr<Statement>>>>>();
    for (auto it = followsRelationshipStore->getBeginIterator(); it != followsRelationshipStore->getEndIterator(); it++) {
        auto followsStatementPairRow = std::make_shared<std::vector<std::shared_ptr<Statement>>>();
        followsStatementPairRow->push_back(std::dynamic_pointer_cast<Statement>((*it)->getLeftEntity()));
        followsStatementPairRow->push_back(std::dynamic_pointer_cast<Statement>((*it)->getRightEntity()));
        followsStatementPair->push_back(followsStatementPairRow);
    }
    return followsStatementPair;
}

std::shared_ptr<Statement> FollowsRelationshipManager::getFollowsByStatement(std::shared_ptr<Statement> statement) const {
    for (auto it = followsRelationshipStore->getBeginIterator(); it != followsRelationshipStore->getEndIterator(); it++) {
        if ((*it)->getRightEntity() == statement) {
            return std::dynamic_pointer_cast<Statement>((*it)->getLeftEntity());
        }
    }
    return nullptr;
}

std::shared_ptr<Statement> FollowsRelationshipManager::getFollowingStatement(std::shared_ptr<Statement> statement) const {
    for (auto it = followsRelationshipStore->getBeginIterator(); it != followsRelationshipStore->getEndIterator(); it++) {
        if ((*it)->getLeftEntity() == statement) {
            return std::dynamic_pointer_cast<Statement>((*it)->getRightEntity());
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