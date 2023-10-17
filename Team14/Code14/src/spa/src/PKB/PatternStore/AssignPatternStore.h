#pragma once

#include <memory>

#include "PKB/Commons/Assignment.h"
#include "PKB/Commons/SetStore.h"

/**
 * @brief A class that stores all the assignment patterns
 * @details A class that stores all the assignment patterns
 */
class AssignPatternStore : public SetStore<Assignment, Assignment> {
public:
    /**
     * @brief Construct a new AssignPatternStore object
     * @return A new AssignPatternStore object
     */
    AssignPatternStore();
};