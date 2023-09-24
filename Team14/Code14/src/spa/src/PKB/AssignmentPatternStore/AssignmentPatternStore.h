#pragma once

#include <memory>
#include <unordered_set>

#include "Assignment.h"

/**
 * @brief A class that stores all the assignment patterns
 * @details A class that stores all the assignment patterns
 */
class AssignmentPatternStore {
private:
    /**
     * @brief An unordered_set that stores all the assignment patterns
     */
    std::unordered_set<
        std::shared_ptr<Assignment>,
        std::hash<std::shared_ptr<Assignment>>,
        std::equal_to<std::shared_ptr<Assignment>>
        > assignmentStore;
public:
    /**
     * @brief Construct a new AssignmentPatternStore object
     * @return A new AssignmentPatternStore object
     */
    AssignmentPatternStore();

    /**
     * @brief Adds an Assignment object to the store
     * @param assignment The Assignment object to be added
     * @return True if the Assignment object is added successfully, false otherwise
     */
    bool addAssignment(std::shared_ptr<Assignment> assignment);

    /**
     * @brief Returns an iterator to the beginning of the store
     * @return An iterator to the beginning of the store
     */
    std::unordered_set<std::shared_ptr<Assignment>>::iterator getBeginIterator();

    /**
     * @brief Returns an iterator to the end of the store
     * @return An iterator to the end of the store
     */
    std::unordered_set<std::shared_ptr<Assignment>>::iterator getEndIterator();

    /**
     * @brief Returns true if the store contains the Assignment object, false otherwise
     * @param assignment The Assignment object to check against
     * @return True if the store contains the Assignment object, false otherwise
     */
    bool contains(Statement& statement) const;
};