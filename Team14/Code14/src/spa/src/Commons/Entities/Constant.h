#pragma once

#include "Entity.h"
#include "EntityType.h"

class Constant: public Entity {
public:
	Constant(int value);
};