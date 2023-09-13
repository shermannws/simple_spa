#pragma once

#include "AssignmentManager.h"

#include <utility>

AssignmentManager::AssignmentManager() {
    this->assignmentStore = std::make_shared<AssignmentPatternStore>(AssignmentPatternStore());
}

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

std::vector<Entity> AssignmentManager::getAssignStatements(Variable& variable, std::string pattern) const {
    std::vector<Entity> statements = std::vector<Entity>();
    for (auto it = assignmentStore->getBeginIterator(); it != assignmentStore->getEndIterator(); it++) {
        Variable currVar = *((*it)->getVariable());
        //TODO: Refactor second clause. Might need to override != operator for Variable
        if (!variable.isWildCard() && !(currVar == variable)) {
            continue;
        }
        // TEMP CODE
        statements.push_back(currVar);

        // Parse string into brackets
        // Validate wild cards
        // Construct regex
        // Check if regex matches
        // If matches, add to statements
    }
    return statements;

}

bool AssignmentManager::contains(Statement& statement) const {
    return assignmentStore->contains(statement);
}