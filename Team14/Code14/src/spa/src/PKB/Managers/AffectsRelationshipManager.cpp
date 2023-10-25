#include "AffectsRelationshipManager.h"

AffectsRelationshipManager::AffectsRelationshipManager() : StmtToStmtRelationshipManager() {
    this->isAffectsCalculated = false;
}

bool AffectsRelationshipManager::hasAffectsBeenCalculated() const {
    return this->isAffectsCalculated;
}

void AffectsRelationshipManager::calculateAffects(
        const std::unordered_set<std::shared_ptr<Statement>> &assignStmts,
        const std::function<std::shared_ptr<Variable>(std::shared_ptr<Statement>)> &getVariable,
        const std::function<bool(Statement &, Variable &)> &hasUses,
        const std::function<bool(Statement &, Variable &)> &hasModifies,
        const std::function<EntityStore<Statement>(std::shared_ptr<Statement>)> &getNext) {

    if (this->isAffectsCalculated) { return; }

    for (const auto currentAssignStmt: assignStmts) {
        std::stack<std::shared_ptr<Statement>> stack;
        std::unordered_set<std::shared_ptr<Statement>> visited;
        std::shared_ptr<Variable> modifiedVar = getVariable(currentAssignStmt);
        stack.push(currentAssignStmt);

        while (!stack.empty()) {
            std::shared_ptr<Statement> stmt = stack.top();
            stack.pop();

            if (stmt == currentAssignStmt && visited.find(stmt) != visited.end() && hasUses(*stmt, *modifiedVar)) {
                this->relationshipStore->storeRelationship(currentAssignStmt, stmt);
                continue;
            }

            if (visited.find(stmt) != visited.end()) { continue; }
            visited.insert(stmt);

            // If node is an assign and uses, add pair
            if (stmt != currentAssignStmt && stmt->isStatementType(StatementType::Assign) &&
                hasUses(*stmt, *modifiedVar)) {
                this->relationshipStore->storeRelationship(currentAssignStmt, stmt);
            }

            // If node is an assign, call, read and modifies, then continue
            if ((stmt != currentAssignStmt && stmt->isStatementType(StatementType::Assign) ||
                 stmt->isStatementType(StatementType::Call) || stmt->isStatementType(StatementType::Read)) &&
                hasModifies(*stmt, *modifiedVar)) {
                continue;
            }

            // add all next
            EntityStore<Statement> nextSet = getNext(stmt);
            for (auto it = nextSet.getBeginIterator(); it != nextSet.getEndIterator(); it++) { stack.push(*it); }

            // 1. The initial assign stmt
            // Add next nodes Y
            // 2. The initial assign stmt visited again that uses var
            // Add relationship & continue Y
            // 3. The initial assign stmt visited again
            // continue Y
            // 4. Another assign statement that uses
            // add relationship and add next Y
            // 5. Another assign statement that modifies
            // continue Y
            // 6. Another assign stmt that uses and modifies
            // add relationship and continue Y
            // 7. Another assign stmt that don't use and don't modify
            // add next Y
        }
    }
    this->isAffectsCalculated = true;
}

void AffectsRelationshipManager::clearStore() {
    this->relationshipStore->clear();
}
