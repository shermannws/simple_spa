#pragma once

#include "Entity.h"
#include "EntityType.h"
#include "Commons/AppConstants.h"

class Constant: public Entity {
public:
	/*!
     * Costructor for Constant object
	 */
	Constant(ConstantValue value);
};