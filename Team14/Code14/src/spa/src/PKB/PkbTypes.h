#pragma once

#include <string>

#include "Commons/Entities/Entity.h"

/**
 * @brief A type alias for an expression
 * @details A type alias for an expression
 */
typedef std::string Expression;

/**
 * @brief A type alias for a Entity shared pointer
 */
typedef std::shared_ptr<Entity> EntityPointer;

/**
 * @brief A type alias for a return type of set of Entities
 */
typedef std::unordered_set<EntityPointer> EntitySet;

/**
 * @brief A type alias for a return type of set of pairs of Entities
 */
typedef std::unordered_set<std::vector<EntityPointer>> EntityPairSet;