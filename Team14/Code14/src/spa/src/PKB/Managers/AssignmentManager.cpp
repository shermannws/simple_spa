#pragma once

#include "AssignmentManager.h"

AssignmentManager::AssignmentManager()
    : assignmentStore(std::make_shared<AssignmentPatternStore>(AssignmentPatternStore())) {}

bool AssignmentManager::addAssignment(std::shared_ptr<Assignment> assignment) {
    return this->assignmentStore->addAssignment(std::move(assignment));
}

std::vector<Entity> AssignmentManager::getAllAssignStatements() const {
    std::vector<Entity> statements = std::vector<Entity>();
    for (auto it = assignmentStore->getBeginIterator(); it != assignmentStore->getEndIterator(); it++) {
        statements.push_back(*((*it)->getStatement()));
    }
    return statements;
}

std::vector<Entity> AssignmentManager::getAssignStatements(Variable& variable, std::string& pattern, bool hasExpressionWildCard) const {
    std::vector<Entity> statements = std::vector<Entity>();
    std::regex regexPattern = AssignmentManager::parsePattern(pattern);
    for (auto it = assignmentStore->getBeginIterator(); it != assignmentStore->getEndIterator(); it++) {
        Variable currVar = *((*it)->getVariable());
        bool regexMatch = AssignmentManager::matchExpression(*((*it)->getExpression()), regexPattern, hasExpressionWildCard);
        if (!variable.isWildCard() && (currVar == variable) && regexMatch) {
            // Case where left entity is not wild card
            statements.push_back(*((*it)->getStatement()));
            continue;
        }
        if (variable.isWildCard() && regexMatch) {
            // Case where left entity is not wild card
            statements.push_back(*((*it)->getStatement()));
            continue;
        }
    }
    return statements;
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
    if (expression.empty() && hasWildCard) {
        // Case where pattern is "_"
        return true;
    }
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