#pragma once

#include "Entity.h"
#include "EntityType.h"

class Constant: public Entity {
public:
	/*!
     * Costructor for Constant object
	 */
	Constant(int value);
};