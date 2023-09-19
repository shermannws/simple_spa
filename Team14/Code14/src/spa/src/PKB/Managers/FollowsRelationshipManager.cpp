#include "FollowsRelationshipManager.h"

FollowsRelationshipManager::FollowsRelationshipManager()
    : followsRelationshipStore(std::make_shared<FollowsRelationshipStore>(FollowsRelationshipStore())) {}

void FollowsRelationshipManager::storeFollowsRelationship(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2) {
    followsRelationshipStore->storeRelationship(std::make_shared<FollowsRelationship>(statement1, statement2));
}

std::vector<std::vector<Entity>> FollowsRelationshipManager::getAllFollowsStatementPair() const {
    auto followsStatementPair = std::vector<std::vector<Entity>>();
    for (auto it = followsRelationshipStore->getBeginIterator(); it != followsRelationshipStore->getEndIterator(); it++) {
        followsStatementPair.push_back(std::vector<Entity>{*((*it)->getLeftEntity()), *((*it)->getRightEntity())});
    }
    return followsStatementPair;
}

std::vector<Entity> FollowsRelationshipManager::getFollowsByStatement(Statement& statement) const {
    //TODO: to fix to take into accout follows vs follows* rs
    for (auto it = followsRelationshipStore->getBeginIterator(); it != followsRelationshipStore->getEndIterator(); it++) {
        if (*((*it)->getRightEntity()) == statement) {
            return std::vector<Entity>{*((*it)->getLeftEntity())};
        }
    }
    return {};
}

std::vector<Entity> FollowsRelationshipManager::getFollowingStatement(Statement& statement) const {
    //TODO: to fix to take into accout follows vs follows* rs
    for (auto it = followsRelationshipStore->getBeginIterator(); it != followsRelationshipStore->getEndIterator(); it++) {
        if (*((*it)->getLeftEntity()) == statement) {
            return std::vector<Entity>{*((*it)->getRightEntity())};
        }
    }
    return {};
}

bool FollowsRelationshipManager::getIsFollows(Statement& statement1, Statement& statement2) const {
    //TODO: should not be an iterator but use the .getRelationship method ad check if nullptr
    for (auto it = followsRelationshipStore->getBeginIterator(); it != followsRelationshipStore->getEndIterator(); it++) {
        if (*((*it)->getLeftEntity()) == statement1 && *((*it)->getRightEntity()) == statement2) {
            return true;
        }
    }
    return false;
}