#include "AssignPatternManager.h"

AssignPatternManager::AssignPatternManager()
    : assignmentStore(std::make_shared<AssignPatternStore>(AssignPatternStore())) {}

void AssignPatternManager::storeAssignPattern(std::shared_ptr<Assignment> assignment) {
    assert(assignment->getStatement()->getStatementType() == StatementType::Assign);
    this->assignmentStore->store(std::move(assignment));
}

std::regex AssignPatternManager::parsePattern(Expression &pattern) const {
    std::string regexPattern;
    for (char &c: pattern) {
        if (AppConstants::MATH_SPECIAL_CHAR_SET.find(c) != AppConstants::MATH_SPECIAL_CHAR_SET.end()) {
            regexPattern += "\\";
        }
        regexPattern += c;
    }
    return std::regex(regexPattern);
}

bool AssignPatternManager::matchExpression(Expression &expression, std::regex &pattern, bool hasWildCard) const {
    if (hasWildCard) {
        // Case where pattern is "_x_"
        return std::regex_search(expression, std::regex(pattern));
    }
    // Case where pattern is "x"
    return std::regex_match(expression, std::regex(pattern));
}

// Pattern queries i.e. pattern a (...,...)
// pattern a (_,_)
EntitySet AssignPatternManager::getAllAssignStmts() const {
    EntitySet statements = EntitySet();
    std::for_each(
            assignmentStore->getBeginIterator(), assignmentStore->getEndIterator(),
            [&statements](std::shared_ptr<Assignment> assignment) { statements.insert(assignment->getStatement()); });
    return statements;
}

// pattern a (_, "x")
EntitySet AssignPatternManager::getAssignStmtsByRhs(Expression &rhs, bool hasRhsWildCard) const {
    std::regex regexPattern = AssignPatternManager::parsePattern(rhs);

    auto matcher = [&regexPattern, &hasRhsWildCard, this](std::shared_ptr<Assignment> assignment) {
        return AssignPatternManager::matchExpression(*(assignment->getExpression()), regexPattern, hasRhsWildCard);
    };

    return ManagerUtils::getEntitiesFromStore<AssignPatternStore, Assignment>(assignmentStore, matcher,
                                                                              Assignment::getStmtFromAssign);
}

// pattern a (v, _)
EntityPairSet AssignPatternManager::getAllAssignStmtVarPair() const {
    auto matcher = [](std::shared_ptr<Assignment> assignment) { return true; };
    return ManagerUtils::getEntityPairsFromStore<AssignPatternStore, Assignment>(assignmentStore, matcher,
                                                                                 Assignment::getStmtVarPairFromAssign);
}

// pattern a (v, "x")
EntityPairSet AssignPatternManager::getAssignStmtsVarPairByRhs(Expression &rhs, bool hasRhsWildCard) const {
    std::regex regexPattern = AssignPatternManager::parsePattern(rhs);
    auto matcher = [&regexPattern, &hasRhsWildCard, this](std::shared_ptr<Assignment> assignment) {
        return AssignPatternManager::matchExpression(*(assignment->getExpression()), regexPattern, hasRhsWildCard);
    };
    return ManagerUtils::getEntityPairsFromStore<AssignPatternStore, Assignment>(assignmentStore, matcher,
                                                                                 Assignment::getStmtVarPairFromAssign);
}

// pattern a ("x", _)
EntitySet AssignPatternManager::getAssignStmtsByLhs(Variable &lhs) const {
    auto matcher = [&lhs](std::shared_ptr<Assignment> assignment) { return *(assignment->getVariable()) == lhs; };
    return ManagerUtils::getEntitiesFromStore<AssignPatternStore, Assignment>(assignmentStore, matcher,
                                                                              Assignment::getStmtFromAssign);
}

// pattern a ("x", "x")
EntitySet AssignPatternManager::getAssignStmtsByLhsRhs(Variable &lhs, Expression &rhs, bool hasRhsWildCard) const {
    std::regex regexPattern = AssignPatternManager::parsePattern(rhs);
    auto matcher = [&regexPattern, &lhs, &hasRhsWildCard, this](std::shared_ptr<Assignment> assignment) {
        return *(assignment->getVariable()) == lhs &&
               AssignPatternManager::matchExpression(*(assignment->getExpression()), regexPattern, hasRhsWildCard);
    };
    return ManagerUtils::getEntitiesFromStore<AssignPatternStore, Assignment>(assignmentStore, matcher,
                                                                              Assignment::getStmtFromAssign);
}

std::unordered_set<std::shared_ptr<Statement>> AssignPatternManager::getAllAssignStmtsAsStmts() const {
    std::unordered_set<std::shared_ptr<Statement>> statements = std::unordered_set<std::shared_ptr<Statement>>();
    for (auto it = assignmentStore->getBeginIterator(); it != assignmentStore->getEndIterator(); it++) {
        statements.insert((*it)->getStatement());
    }
    return statements;
}