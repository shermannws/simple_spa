#include "FollowsRelationshipManager.h"

FollowsRelationshipManager::FollowsRelationshipManager() : StmtToStmtRelationshipManager<FollowsRelationshipStore, FollowsRelationship>() {};

void FollowsRelationshipManager::storeFollowsRelationship(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2, bool isDirect) {
    this->storeRelationship(statement1, statement2, isDirect);
};

std::vector<std::vector<Entity>> FollowsRelationshipManager::getFollowsPair(StatementType formerType, StatementType latterType, bool requireDirect) const {
    return this->getRelationshipPair(formerType, latterType, requireDirect);
};

std::vector<Entity> FollowsRelationshipManager::getFollowsTypeStmt(StatementType type, Statement& statement, bool requireDirect) const {
    return this->getRelationshipTypeStmt(type, statement, requireDirect);
};

std::vector<Entity> FollowsRelationshipManager::getFollowsTypeWildcard(StatementType type) const { // Same for Follows and Follows* since Follows* is a superset of Follows
    return this->getRelationshipTypeWildcard(type);
};

std::vector<Entity> FollowsRelationshipManager::getFollowsStmtType(Statement& statement, StatementType type, bool requireDirect) const {
    return this->getRelationshipStmtType(statement, type, requireDirect);
};

std::vector<Entity> FollowsRelationshipManager::getFollowsWildcardType(StatementType type) const { // Same for Follows and Follows* since Follows* is a superset of Follows
    return this->getRelationshipWildcardType(type);
};

bool FollowsRelationshipManager::isFollows(Statement& statement1, Statement& statement2, bool requireDirect) const {
    return this->isRelationship(statement1, statement2, requireDirect);
};

bool FollowsRelationshipManager::hasFollows() const {
    return this->hasRelationship();
};
