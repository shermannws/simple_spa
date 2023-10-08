#pragma once

#include <memory>
#include <unordered_set>

#include "PKB/Commons/Assignment.h"
#include "PKB/Commons/SetStore.h"

/**
 * @brief A class that stores all the assignment patterns
 * @details A class that stores all the assignment patterns
 */
class AssignmentPatternStore : public SetStore<Assignment, Assignment> {
public:
    /**
     * @brief Construct a new AssignmentPatternStore object
     * @return A new AssignmentPatternStore object
     */
    AssignmentPatternStore();

    /**
     * @brief Adds an Assignment object to the store
     * @param assignment The Assignment object to be added
     */
    void addAssignment(std::shared_ptr<Assignment> assignment);
};