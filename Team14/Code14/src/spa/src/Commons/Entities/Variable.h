#pragma once

#include <string>

#include "../AppConstants.h"
#include "Entity.h"

/**
 * @brief A Variable is a variable in the SIMPLE programming language
 * @details A Variable is a variable in the SIMPLE programming language
 */
class Variable : public Entity {
public:
    /**
     * @brief Construct a new Variable object
     * @param name The name of the variable as type VariableName (string)
     * @return A new Variable object
     */
    Variable(VariableName name);
};