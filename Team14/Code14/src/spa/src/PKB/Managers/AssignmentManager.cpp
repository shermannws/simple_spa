#pragma once

#include "AssignmentManager.h"

AssignmentManager::AssignmentManager()
    : assignmentStore(std::make_shared<AssignmentPatternStore>(AssignmentPatternStore())) {}

bool AssignmentManager::addAssignment(std::shared_ptr<Assignment> assignment) {
    return this->assignmentStore->addAssignment(std::move(assignment));
}

std::regex AssignmentManager::parsePattern(std::string& pattern) const {
    std::string regexPattern;
    for (char& c : pattern) {
        if (AppConstants::MATH_SPECIAL_CHAR_SET.find(c) != AppConstants::MATH_SPECIAL_CHAR_SET.end()) {
            regexPattern += "\\";
        }
        regexPattern += c;
    }
    return std::regex(regexPattern);
}

bool AssignmentManager::matchExpression(std::string& expression, std::regex& pattern, bool hasWildCard) const {
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
    for (auto it = assignmentStore->getBeginIterator(); it != assignmentStore->getEndIterator(); it++) {
        statements.push_back(*((*it)->getStatement()));
    }
    return statements;
}

// pattern a (_, "x")
std::vector<Entity> AssignmentManager::getAssignStmtsByRhs(std::string& rhs, bool hasRhsWildCard) const {
    std::vector<Entity> statements = std::vector<Entity>();
    std::regex regexPattern = AssignmentManager::parsePattern(rhs);
    for (auto it = assignmentStore->getBeginIterator(); it != assignmentStore->getEndIterator(); it++) {
        bool regexMatch = AssignmentManager::matchExpression(*((*it)->getExpression()), regexPattern, hasRhsWildCard);
        if (regexMatch) {
            statements.push_back(*((*it)->getStatement()));
        }
    }
    return statements;
}

// pattern a (v, _)
std::vector<std::vector<Entity>> AssignmentManager::getAllAssignStmtVarPair() const {
    std::vector<std::vector<Entity>> pair = std::vector<std::vector<Entity>>();
    for (auto it = assignmentStore->getBeginIterator(); it != assignmentStore->getEndIterator(); it++) {
        std::vector<Entity> currPair = std::vector<Entity>();
        currPair.push_back(*((*it)->getStatement()));
        currPair.push_back(*((*it)->getVariable()));
        pair.push_back(currPair);
    }
    return pair;
}

// pattern a (v, "x")
std::vector<std::vector<Entity>> AssignmentManager::getAssignStmtsVarPairByRhs(std::string& rhs, bool hasRhsWildCard) const {
    std::vector<std::vector<Entity>> pair = std::vector<std::vector<Entity>>();
    std::regex regexPattern = AssignmentManager::parsePattern(rhs);
    for (auto it = assignmentStore->getBeginIterator(); it != assignmentStore->getEndIterator(); it++) {
        bool regexMatch = AssignmentManager::matchExpression(*((*it)->getExpression()), regexPattern, hasRhsWildCard);
        if (regexMatch) {
            std::vector<Entity> currPair = std::vector<Entity>();
            currPair.push_back(*((*it)->getStatement()));
            currPair.push_back(*((*it)->getVariable()));
            pair.push_back(currPair);
        }
    }
    return pair;
}

// pattern a ("x", _)
std::vector<Entity> AssignmentManager::getAssignStmtsByLhs(Variable& lhs) const {
    std::vector<Entity> statements = std::vector<Entity>();
    for (auto it = assignmentStore->getBeginIterator(); it != assignmentStore->getEndIterator(); it++) {
        if (*((*it)->getVariable()) == lhs) {
            statements.push_back(*((*it)->getStatement()));
        }
    }
    return statements;
}

// pattern a ("x", "x")
std::vector<Entity> AssignmentManager::getAssignStmtsByLhsRhs(Variable& lhs, std::string& rhs, bool hasRhsWildCard) const {
    std::vector<Entity> statements = std::vector<Entity>();
    std::regex regexPattern = AssignmentManager::parsePattern(rhs);
    for (auto it = assignmentStore->getBeginIterator(); it != assignmentStore->getEndIterator(); it++) {
        bool regexMatch = AssignmentManager::matchExpression(*((*it)->getExpression()), regexPattern, hasRhsWildCard);
        if (*((*it)->getVariable()) == lhs && regexMatch) {
            statements.push_back(*((*it)->getStatement()));
        }
    }
    return statements;
}
