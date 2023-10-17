#include "IfPatternManager.h"

IfPatternManager::IfPatternManager() : ConditionPatternManager<IfPatternStore>() {}

void IfPatternManager::storeIfPattern(std::shared_ptr<Statement> stmt, std::shared_ptr<std::vector<std::shared_ptr<Variable>>> vars) {
    assert(stmt->getStatementType() == StatementType::If);
    this->storePattern(std::move(stmt), std::move(vars));
}