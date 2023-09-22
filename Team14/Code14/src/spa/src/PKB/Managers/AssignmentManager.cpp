#pragma once

#include "AssignmentManager.h"

AssignmentManager::AssignmentManager()
    : assignmentStore(std::make_shared<AssignmentPatternStore>(AssignmentPatternStore())) {}

bool AssignmentManager::addAssignment(std::shared_ptr<Assignment> assignment) {
    return this->assignmentStore->addAssignment(std::move(assignment));
}

std::regex AssignmentManager::parsePattern(Expression& pattern) const {
    std::string regexPattern;
    for (char& c : pattern) {
        if (AppConstants::MATH_SPECIAL_CHAR_SET.find(c) != AppConstants::MATH_SPECIAL_CHAR_SET.end()) {
            regexPattern += "\\";
        }
        regexPattern += c;
    }
    return std::regex(regexPattern);
}

bool AssignmentManager::matchExpression(Expression& expression, std::regex& pattern, bool hasWildCard) const {
    if (hasWildCard) {
        // Case where pattern is "_x_"
        return std::regex_search(expression, std::regex(pattern));
    }
    // Case where pattern is "x"
    return std::regex_match(expression, std::regex(pattern));
}

bool AssignmentManager::contains(Statement& statement) const {
    return assignmentStore->contains(statement);
}

// Pattern queries i.e. pattern a (...,...)
// pattern a (_,_)
std::vector<Entity> AssignmentManager::getAllAssignStmts() const {
    std::vector<Entity> statements = std::vector<Entity>();
    std::for_each(assignmentStore->getBeginIterator(), assignmentStore->getEndIterator(), [&statements](std::shared_ptr<Assignment> assignment) {
        statements.push_back(*(assignment->getStatement()));
    });
    return statements;
}

// pattern a (_, "x")
std::vector<Entity> AssignmentManager::getAssignStmtsByRhs(Expression& rhs, bool hasRhsWildCard) const {
    std::regex regexPattern = AssignmentManager::parsePattern(rhs);

    auto matcher = [&regexPattern, &hasRhsWildCard, this](Assignment& assignment) {
        return AssignmentManager::matchExpression(*(assignment.getExpression()), regexPattern, hasRhsWildCard);
    };

    return ManagerUtils::getEntitiesFromStore<AssignmentPatternStore, Assignment>(assignmentStore, matcher, Assignment::getStmtFromAssign);
}

// pattern a (v, _)
std::vector<std::vector<Entity>> AssignmentManager::getAllAssignStmtVarPair() const {
    auto matcher = [](Assignment& assignment) {
        return true;
    };
    return ManagerUtils::getEntityPairsFromStore<AssignmentPatternStore, Assignment>(assignmentStore, matcher, Assignment::getStmtVarPairFromAssign);
}

// pattern a (v, "x")
std::vector<std::vector<Entity>> AssignmentManager::getAssignStmtsVarPairByRhs(Expression& rhs, bool hasRhsWildCard) const {
    std::regex regexPattern = AssignmentManager::parsePattern(rhs);
    auto matcher = [&regexPattern, &hasRhsWildCard, this](Assignment& assignment) {
        return AssignmentManager::matchExpression(*(assignment.getExpression()), regexPattern, hasRhsWildCard);
    };
    return ManagerUtils::getEntityPairsFromStore<AssignmentPatternStore, Assignment>(assignmentStore, matcher, Assignment::getStmtVarPairFromAssign);
}

// pattern a ("x", _)
std::vector<Entity> AssignmentManager::getAssignStmtsByLhs(Variable& lhs) const {
    auto matcher = [&lhs](Assignment& assignment) {
        return *(assignment.getVariable()) == lhs;
    };
    return ManagerUtils::getEntitiesFromStore<AssignmentPatternStore, Assignment>(assignmentStore, matcher, Assignment::getStmtFromAssign);
}

// pattern a ("x", "x")
std::vector<Entity> AssignmentManager::getAssignStmtsByLhsRhs(Variable& lhs, Expression& rhs, bool hasRhsWildCard) const {
    std::regex regexPattern = AssignmentManager::parsePattern(rhs);
    auto matcher = [&regexPattern, &lhs, &hasRhsWildCard, this](Assignment& assignment) {
        return *(assignment.getVariable()) == lhs && AssignmentManager::matchExpression(*(assignment.getExpression()), regexPattern, hasRhsWildCard);
    };
    return ManagerUtils::getEntitiesFromStore<AssignmentPatternStore, Assignment>(assignmentStore, matcher, Assignment::getStmtFromAssign);
}
