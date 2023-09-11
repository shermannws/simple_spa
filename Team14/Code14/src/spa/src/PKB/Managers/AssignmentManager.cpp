#pragma once

#include "AssignmentManager.h"

AssignmentManager::AssignmentManager(std::shared_ptr<AssignmentPatternStore> assignmentStore) {
    this->assignmentStore = assignmentStore;
}

bool AssignmentManager::addAssignment(std::shared_ptr<Assignment> assignment) {
    return this->assignmentStore->addAssignment(assignment);
}

std::shared_ptr<std::vector<std::shared_ptr<Statement>>> AssignmentManager::getAllAssignStatements() const {
    std::shared_ptr<std::vector<std::shared_ptr<Statement>>> statements = std::make_shared<std::vector<std::shared_ptr<Statement>>>();
    for (auto it = assignmentStore->getBeginIterator(); it != assignmentStore->getEndIterator(); it++) {
        statements->push_back((*it)->getStatement());
    }
    return statements;
}

std::shared_ptr<std::vector<std::shared_ptr<Statement>>> AssignmentManager::getAssignStatements(std::shared_ptr<Variable> variable, std::string pattern) const {
    std::shared_ptr<std::vector<std::shared_ptr<Statement>>> statements = std::make_shared<std::vector<std::shared_ptr<Statement>>>();
    for (auto it = assignmentStore->getBeginIterator(); it != assignmentStore->getEndIterator(); it++) {
        if (!variable->isWildCard() && (*it)->getVariable() != variable) {
            continue;
        }
        // TEMP CODE
        statements->push_back((*it)->getStatement());

        // Parse string into brackets
        // Validate wild cards
        // Construct regex
        // Check if regex matches
        // If matches, add to statements
    }
    return statements;

}

bool AssignmentManager::contains(std::shared_ptr<Statement> statement) const {
    return assignmentStore->contains(statement);
}