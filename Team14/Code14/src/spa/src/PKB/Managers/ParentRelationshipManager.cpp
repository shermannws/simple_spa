#include "ParentRelationshipManager.h"

ParentRelationshipManager::ParentRelationshipManager() : StmtToStmtRelationshipManager<ParentRelationshipStore, ParentRelationship>() {};

void ParentRelationshipManager::storeParentRelationship(std::shared_ptr<Statement> parentStatement, std::shared_ptr<Statement> childStatement, bool isDirect) {
    this->storeRelationship(parentStatement, childStatement, isDirect);
};

std::vector<std::vector<Entity>> ParentRelationshipManager::getParentPair(StatementType formerType, StatementType latterType, bool requireDirect) const {
    return this->getRelationshipPair(formerType, latterType, requireDirect);
};

std::vector<Entity> ParentRelationshipManager::getParentTypeStmt(StatementType type, Statement& statement, bool requireDirect) const {
    return this->getRelationshipTypeStmt(type, statement, requireDirect);
};

std::vector<Entity> ParentRelationshipManager::getParentTypeWildcard(StatementType type) const { // Same for Parent and Parent* since Parent* is a superset of Parent
    return this->getRelationshipTypeWildcard(type);
};

std::vector<Entity> ParentRelationshipManager::getParentStmtType(Statement& statement, StatementType type, bool requireDirect) const {
    return this->getRelationshipStmtType(statement, type, requireDirect);
};

std::vector<Entity> ParentRelationshipManager::getParentWildcardType(StatementType type) const { // Same for Parent and Parent* since Parent* is a superset of Parent
    return this->getRelationshipWildcardType(type);
};

bool ParentRelationshipManager::isParent(Statement& statement1, Statement& statement2, bool requireDirect) const {
    return this->isRelationship(statement1, statement2, requireDirect);
};

bool ParentRelationshipManager::hasParent() const {
    return this->hasRelationship();
};