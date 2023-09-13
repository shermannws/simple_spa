#pragma once

#include "AssignmentPatternStore.h"

AssignmentPatternStore::AssignmentPatternStore() = default;

bool AssignmentPatternStore::addAssignment(std::shared_ptr<Assignment> assignment) {
    return this->assignmentStore.insert(assignment).second;
}

std::unordered_set<std::shared_ptr<Assignment>>::iterator AssignmentPatternStore::getBeginIterator() {
    return this->assignmentStore.begin();
}

std::unordered_set<std::shared_ptr<Assignment>>::iterator AssignmentPatternStore::getEndIterator() {
    return this->assignmentStore.end();
}

bool AssignmentPatternStore::contains(Statement& statement) const {
    return this->assignmentStore.find(std::make_shared<Assignment>(std::make_shared<Statement>(statement), nullptr, nullptr)) != this->assignmentStore.end();
}