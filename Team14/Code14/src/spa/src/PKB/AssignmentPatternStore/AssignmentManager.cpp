#include <memory>

#include "AssignmentManager.h"

AssignmentManager::AssignmentManager(std::shared_ptr<AssignmentPatternStore> assignmentStore) {
    this->assignmentStore = assignmentStore;
}

bool AssignmentManager::addAssignment(std::shared_ptr<Assignment> assignment) {
    return this->assignmentStore->addAssignment(assignment);
}

std::shared_ptr<vector<shared_ptr<Statement>>> AssignmentManager::getAssignStatements(std::shared_ptr<Variable> variable, string pattern) const {
    std::shared_ptr<vector<shared_ptr<Statement>>> statements = std::make_shared<vector<shared_ptr<Statement>>>();
    auto it = this->assignmentStore->getBeginIterator();
    auto end = this->assignmentStore->getEndIterator();
    while (it != end) {
        if (!variable->isWildCard() && (*it)->getVariable() != variable) {
            it++;
            continue;
        }
        // TEMP CODE
        statements->push_back((*it)->getStatement());
        it++;

        // Parse string into brackets
        // Validate wild cards
        // Construct regex
        // Check if regex matches
        // If matches, add to statements
    }
    return statements;

}