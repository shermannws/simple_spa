#include "NextRelationshipManager.h"

NextRelationshipManager::NextRelationshipManager() : StmtToStmtRelationshipManager() {
    this->isNextStarCalculated = false;
};

std::vector<Entity> NextRelationshipManager::getNextStarSameStmt(StatementType stmtType) const {
    if (!this->isNextStarCalculated) {
        this->calculateNextStar();
    }

    auto leftMatcher = [stmtType](Statement& stmt) {
        return stmt.isStatementType(stmtType);
        };

    return ManagerUtils::getLeftKeysMatchRight<Statement>(*starRelationshipStore, leftMatcher);
}

std::vector<std::vector<Entity>> NextRelationshipManager::getRelationshipPair(StatementType formerType, StatementType latterType, bool requireDirect) const {
    if (!requireDirect && !this->isNextStarCalculated) {
		this->calculateNextStar();
	}   
    return StmtToStmtRelationshipManager::getRelationshipPair(formerType, latterType, requireDirect);
}

std::vector<Entity> NextRelationshipManager::getRelationshipTypeStmt(StatementType type, Statement& statement, bool requireDirect) const {
    if (!requireDirect && !this->isNextStarCalculated) {
        this->calculateNextStar();
    }
    return StmtToStmtRelationshipManager::getRelationshipTypeStmt(type, statement, requireDirect);
}

std::vector<Entity> NextRelationshipManager::getRelationshipTypeWildcard(StatementType type, bool requireDirect) const {
    if (!requireDirect && !this->isNextStarCalculated) {
        this->calculateNextStar();
    }
    return StmtToStmtRelationshipManager::getRelationshipTypeWildcard(type, requireDirect);
}

std::vector<Entity> NextRelationshipManager::getRelationshipStmtType(Statement& statement, StatementType type, bool requireDirect) const {
    if (!requireDirect && !this->isNextStarCalculated) {
        this->calculateNextStar();
    }
    return StmtToStmtRelationshipManager::getRelationshipStmtType(statement, type, requireDirect);
}

std::vector<Entity> NextRelationshipManager::getRelationshipWildcardType(StatementType type, bool requireDirect) const {
    if (!requireDirect && !this->isNextStarCalculated) {
        this->calculateNextStar();
    }
    return StmtToStmtRelationshipManager::getRelationshipWildcardType(type, requireDirect);
}

bool NextRelationshipManager::isRelationship(Statement& statement1, Statement& statement2, bool requireDirect) const {
    if (!requireDirect && !this->isNextStarCalculated) {
        this->calculateNextStar();
    }
    return StmtToStmtRelationshipManager::isRelationship(statement1, statement2, requireDirect);
}

void NextRelationshipManager::clearNextStarStore() { //TODO: Someone need to invoke this function after each query
	this->starRelationshipStore->clear();
    this->isNextStarCalculated = false;
}

void NextRelationshipManager::calculateNextStar() const {
    for (auto it = relationshipStore->getLeftToRightBeginIterator(); it != relationshipStore->getLeftToRightEndIterator(); ++it) {
        auto former = it->first;
        auto latterSet = it->second;
        for (auto it2 = latterSet->getBeginIterator(); it2 != latterSet->getEndIterator(); ++it2) {
            auto latter = *it2;
            starRelationshipStore->storeRelationship(former, latter);
            calculateNextStarHelper(former, latter);
        }
    }

    this->isNextStarCalculated = true;
}

void NextRelationshipManager::calculateNextStarHelper(std::shared_ptr<Statement> former, std::shared_ptr<Statement> latter) const {
    auto latterChildren = relationshipStore->getRightEntitiesOf(latter);
    if (latterChildren == nullptr) {
        return;
    }
    for (auto it = latterChildren->getBeginIterator(); it != latterChildren->getEndIterator(); ++it) {
        auto newLatter = *it;
        auto rightOfFormer = starRelationshipStore->getRightEntitiesOf(former);
        if (rightOfFormer != nullptr && rightOfFormer->get(newLatter) != nullptr) {
            continue;
        }
        starRelationshipStore->storeRelationship(former, newLatter);
        calculateNextStarHelper(former, newLatter);
    }
}