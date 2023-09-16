#pragma once

#include "EntityStore.h"
#include "Commons/Entities/Constant.h"

class ConstantStore : public EntityStore<Constant> {
public:
	/*!
	 * Constructor for ConstantStore class
	 */
	ConstantStore();
};