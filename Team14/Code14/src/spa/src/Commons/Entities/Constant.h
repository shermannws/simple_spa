#pragma once

#include "Entity.h"
#include "EntityType.h"
#include "Commons/AppConstants.h"

/**
 * @brief A Constant is a constant in the SIMPLE programming language
 * @details A Constant is a constant in the SIMPLE programming language
 */
class Constant: public Entity {
public:
    /**
     * @brief Construct a new Constant object
     * @param value The integer value of the constant
     * @return A new Constant object
     */
    Constant(ConstantValue value);
};