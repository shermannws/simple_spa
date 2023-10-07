#include "AssignmentPatternStore.h"

AssignmentPatternStore::AssignmentPatternStore() : SetStore<Assignment, Assignment>() {}

void AssignmentPatternStore::addAssignment(std::shared_ptr<Assignment> assignment) {
    return this->store(assignment);
}
