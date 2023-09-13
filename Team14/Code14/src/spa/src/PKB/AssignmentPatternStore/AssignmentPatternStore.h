#pragma once

#include <memory>
#include <unordered_set>

#include "Assignment.h"

class AssignmentPatternStore {
private:
    std::unordered_set<
        std::shared_ptr<Assignment>,
        std::hash<std::shared_ptr<Assignment>>,
        std::equal_to<std::shared_ptr<Assignment>>
        > assignmentStore;
public:
    AssignmentPatternStore();

    bool addAssignment(std::shared_ptr<Assignment> assignment);

    std::unordered_set<std::shared_ptr<Assignment>>::iterator getBeginIterator();

    std::unordered_set<std::shared_ptr<Assignment>>::iterator getEndIterator();

    bool contains(Statement& statement) const;
};