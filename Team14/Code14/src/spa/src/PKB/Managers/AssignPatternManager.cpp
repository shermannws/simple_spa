#include "AssignPatternManager.h"

AssignPatternManager::AssignPatternManager()
    : assignmentStore(std::make_shared<AssignPatternStore>(AssignPatternStore())) {}

void AssignPatternManager::storeAssignPattern(std::shared_ptr<Assignment> assignment) {
    assert(assignment->getStatement()->getStatementType() == StatementType::Assign);
    this->assignmentStore->store(std::move(assignment));
}

std::regex AssignPatternManager::parsePattern(Expression& pattern) const {
    std::string regexPattern;
    for (char& c : pattern) {
        if (AppConstants::MATH_SPECIAL_CHAR_SET.find(c) != AppConstants::MATH_SPECIAL_CHAR_SET.end()) {
            regexPattern += "\\";
        }
        regexPattern += c;
    }
    return std::regex(regexPattern);
}

bool AssignPatternManager::matchExpression(Expression& expression, std::regex& pattern, bool hasWildCard) const {
    if (hasWildCard) {
        // Case where pattern is "_x_"
        return std::regex_search(expression, std::regex(pattern));
    }
    // Case where pattern is "x"
    return std::regex_match(expression, std::regex(pattern));
}

// Pattern queries i.e. pattern a (...,...)
// pattern a (_,_)
std::vector<Entity> AssignPatternManager::getAllAssignStmts() const {
    std::vector<Entity> statements = std::vector<Entity>();
    std::for_each(assignmentStore->getBeginIterator(), assignmentStore->getEndIterator(), [&statements](std::shared_ptr<Assignment> assignment) {
        statements.push_back(*(assignment->getStatement()));
    });
    return statements;
}

// pattern a (_, "x")
std::vector<Entity> AssignPatternManager::getAssignStmtsByRhs(Expression& rhs, bool hasRhsWildCard) const {
    std::regex regexPattern = AssignPatternManager::parsePattern(rhs);

    auto matcher = [&regexPattern, &hasRhsWildCard, this](Assignment& assignment) {
        return AssignPatternManager::matchExpression(*(assignment.getExpression()), regexPattern, hasRhsWildCard);
    };

    return ManagerUtils::getEntitiesFromStore<AssignPatternStore, Assignment>(assignmentStore, matcher, Assignment::getStmtFromAssign);
}

// pattern a (v, _)
std::vector<std::vector<Entity>> AssignPatternManager::getAllAssignStmtVarPair() const {
    auto matcher = [](Assignment& assignment) {
        return true;
    };
    return ManagerUtils::getEntityPairsFromStore<AssignPatternStore, Assignment>(assignmentStore, matcher, Assignment::getStmtVarPairFromAssign);
}

// pattern a (v, "x")
std::vector<std::vector<Entity>> AssignPatternManager::getAssignStmtsVarPairByRhs(Expression& rhs, bool hasRhsWildCard) const {
    std::regex regexPattern = AssignPatternManager::parsePattern(rhs);
    auto matcher = [&regexPattern, &hasRhsWildCard, this](Assignment& assignment) {
        return AssignPatternManager::matchExpression(*(assignment.getExpression()), regexPattern, hasRhsWildCard);
    };
    return ManagerUtils::getEntityPairsFromStore<AssignPatternStore, Assignment>(assignmentStore, matcher, Assignment::getStmtVarPairFromAssign);
}

// pattern a ("x", _)
std::vector<Entity> AssignPatternManager::getAssignStmtsByLhs(Variable& lhs) const {
    auto matcher = [&lhs](Assignment& assignment) {
        return *(assignment.getVariable()) == lhs;
    };
    return ManagerUtils::getEntitiesFromStore<AssignPatternStore, Assignment>(assignmentStore, matcher, Assignment::getStmtFromAssign);
}

// pattern a ("x", "x")
std::vector<Entity> AssignPatternManager::getAssignStmtsByLhsRhs(Variable& lhs, Expression& rhs, bool hasRhsWildCard) const {
    std::regex regexPattern = AssignPatternManager::parsePattern(rhs);
    auto matcher = [&regexPattern, &lhs, &hasRhsWildCard, this](Assignment& assignment) {
        return *(assignment.getVariable()) == lhs && AssignPatternManager::matchExpression(*(assignment.getExpression()), regexPattern, hasRhsWildCard);
    };
    return ManagerUtils::getEntitiesFromStore<AssignPatternStore, Assignment>(assignmentStore, matcher, Assignment::getStmtFromAssign);
}
