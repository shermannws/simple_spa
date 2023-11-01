#include "NextRelationshipManager.h"

#include <utility>

NextRelationshipManager::NextRelationshipManager() : StmtToStmtRelationshipManager() {
    this->clauseGroup = ClauseGroup::Next;
    this->isNextStarCalculated = false;
};

EntitySet NextRelationshipManager::getNextStarSameStmt(StatementType stmtType) const {
    if (!this->isNextStarCalculated) { this->calculateNextStar(); }

    return getSameStmt(stmtType, false);
}

EntityPairSet NextRelationshipManager::getRelationshipPair(StatementType formerType,
                                                                                     StatementType latterType,
                                                                                     bool requireDirect) const {
    if (!requireDirect && !this->isNextStarCalculated) { this->calculateNextStar(); }
    return StmtToStmtRelationshipManager::getRelationshipPair(formerType, latterType, requireDirect);
}

EntitySet NextRelationshipManager::getRelationshipTypeStmt(StatementType type, Statement &statement,
                                                                            bool requireDirect) const {
    if (!requireDirect && !this->isNextStarCalculated) { this->calculateNextStar(); }
    return StmtToStmtRelationshipManager::getRelationshipTypeStmt(type, statement, requireDirect);
}

EntitySet NextRelationshipManager::getRelationshipTypeWildcard(StatementType type,
                                                                                bool requireDirect) const {
    if (!requireDirect && !this->isNextStarCalculated) { this->calculateNextStar(); }
    return StmtToStmtRelationshipManager::getRelationshipTypeWildcard(type, requireDirect);
}

EntitySet NextRelationshipManager::getRelationshipStmtType(Statement &statement, StatementType type,
                                                                            bool requireDirect) const {
    if (!requireDirect && !this->isNextStarCalculated) { this->calculateNextStar(); }
    return StmtToStmtRelationshipManager::getRelationshipStmtType(statement, type, requireDirect);
}

EntitySet NextRelationshipManager::getRelationshipWildcardType(StatementType type,
                                                                                bool requireDirect) const {
    if (!requireDirect && !this->isNextStarCalculated) { this->calculateNextStar(); }
    return StmtToStmtRelationshipManager::getRelationshipWildcardType(type, requireDirect);
}

bool NextRelationshipManager::isRelationship(Statement &statement1, Statement &statement2, bool requireDirect) const {
    if (!requireDirect && !this->isNextStarCalculated) { this->calculateNextStar(); }
    return StmtToStmtRelationshipManager::isRelationship(statement1, statement2, requireDirect);
}

void NextRelationshipManager::clearNextStarStore() {
    this->starRelationshipStore->clear();
    this->isNextStarCalculated = false;
}

void NextRelationshipManager::calculateNextStar() const {
    ManagerUtils::calculateTransitivity<NextRelationshipStore, Statement>(this->relationshipStore,
                                                                          this->starRelationshipStore);
    this->isNextStarCalculated = true;
}

std::shared_ptr<EntityStore<Statement>>
NextRelationshipManager::getAllNextOfStmt(std::shared_ptr<Statement> stmt) const {
    return this->relationshipStore->getRightEntitiesOf(std::move(stmt));
}