#include "NextRelationshipManager.h"

NextRelationshipManager::NextRelationshipManager() : StmtToStmtRelationshipManager() {};

std::vector<Entity> NextRelationshipManager::getNextStarSameStmt(StatementType stmtType) const {
    auto leftMatcher = [stmtType](Statement& stmt) {
        return stmt.isStatementType(stmtType);
        };

    return ManagerUtils::getLeftKeysMatchRight<Statement>(*starRelationshipStore, leftMatcher);
}