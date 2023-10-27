#include "AffectsRelationshipManager.h"

AffectsRelationshipManager::AffectsRelationshipManager() : StmtToStmtRelationshipManager() {
    this->isAffectsCalculated = false;
}

bool AffectsRelationshipManager::hasAffectsBeenCalculated() const { return this->isAffectsCalculated; }

void AffectsRelationshipManager::calculateAffects(
        const std::unordered_set<std::shared_ptr<Statement>> &assignStmts,
        const std::function<std::shared_ptr<Variable>(std::shared_ptr<Statement>)> &getVariable,
        const std::function<bool(Statement &, Variable &)> &hasUses,
        const std::function<bool(Statement &, Variable &)> &hasModifies,
        const std::function<std::shared_ptr<EntityStore<Statement>>(std::shared_ptr<Statement>)> &getNext) {

    if (this->isAffectsCalculated) { return; }

    for (const auto &currentAssignStmt: assignStmts) {
        std::stack<std::shared_ptr<Statement>> stack;
        std::unordered_set<std::shared_ptr<Statement>> visited;
        std::shared_ptr<Variable> modifiedVar = getVariable(currentAssignStmt);
        stack.push(currentAssignStmt);

        while (!stack.empty()) {
            std::shared_ptr<Statement> stmt = stack.top();
            stack.pop();

            // If starting stmt visited again, means there is a loop, add relationship if stmt uses modifiedVar
            if (stmt == currentAssignStmt && visited.find(stmt) != visited.end() && hasUses(*stmt, *modifiedVar)) {
                this->relationshipStore->storeRelationship(currentAssignStmt, stmt);
                continue;
            }

            // Skip all other revisited stmts
            if (visited.find(stmt) != visited.end()) { continue; }
            visited.insert(stmt);

            // If node is an assign and uses modifiedVar, add relationship
            if (stmt != currentAssignStmt && stmt->isStatementType(StatementType::Assign) &&
                hasUses(*stmt, *modifiedVar)) {
                this->relationshipStore->storeRelationship(currentAssignStmt, stmt);
            }

            // If node is an assign, call, read and modifies, and modifies modifiedVar, skip
            if ((stmt != currentAssignStmt && stmt->isStatementType(StatementType::Assign) ||
                 stmt->isStatementType(StatementType::Call) || stmt->isStatementType(StatementType::Read)) &&
                hasModifies(*stmt, *modifiedVar)) {
                continue;
            }

            // Add all next stmts to stack
            std::shared_ptr<EntityStore<Statement>> nextSet = getNext(stmt);
            if (nextSet == nullptr) { continue; }
            for (auto it = nextSet->getBeginIterator(); it != nextSet->getEndIterator(); it++) { stack.push(*it); }
        }
    }
    this->isAffectsCalculated = true;
}

void AffectsRelationshipManager::clearStore() {
    this->relationshipStore->clear();
    this->isAffectsCalculated = false;
}

std::vector<Entity> AffectsRelationshipManager::getAffectsSameStmt(StatementType stmtType) const {
    auto leftMatcher = [stmtType](Statement &stmt) { return stmt.isStatementType(stmtType); };

    return ManagerUtils::getLeftKeysMatchRight<Statement>(*relationshipStore, leftMatcher);
}