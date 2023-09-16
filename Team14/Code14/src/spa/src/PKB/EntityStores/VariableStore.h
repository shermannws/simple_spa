#pragma once

#include "EntityStore.h"
#include "Commons/Entities/Variable.h"

class VariableStore : public EntityStore<Variable> {
public:
	/*!
	 * Constructor for VariableStore
	 */
	VariableStore();
};