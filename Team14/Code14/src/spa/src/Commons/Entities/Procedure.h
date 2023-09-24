#pragma once

#include <string>

#include "Entity.h"
#include "../AppConstants.h"

/**
 * @brief A Procedure is a procedure in the SIMPLE programming language
 * @details A Procedure is a procedure in the SIMPLE programming language
 */
class Procedure : public Entity {
public:
    /**
     * @brief Construct a new Procedure object
     * @param name The name of the procedure as type string
     * @return A new Procedure object
     */
    Procedure(ProcedureName name);
};