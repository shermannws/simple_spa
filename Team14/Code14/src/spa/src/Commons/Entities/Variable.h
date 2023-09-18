#pragma once

#include <string>

#include "Entity.h"

class Variable : public Entity {
public:
	/*!
	 * Costructor for Variable object
	 */
	Variable(std::string name);

	/*!
	 * Returns true if Variable object is a wildcard variable, return false otherwise
	 */
    virtual bool isWildCard();
};