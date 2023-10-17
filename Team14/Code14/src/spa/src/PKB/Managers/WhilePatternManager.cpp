#include "WhilePatternManager.h"

WhilePatternManager::WhilePatternManager() : ConditionPatternManager<WhilePatternStore>() {}

void WhilePatternManager::storeWhilePattern(std::shared_ptr<Statement> stmt, std::shared_ptr<std::vector<std::shared_ptr<Variable>>> vars) {
    assert(stmt->getStatementType() == StatementType::While);
    this->storePattern(std::move(stmt), std::move(vars));
}