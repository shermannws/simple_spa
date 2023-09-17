#pragma once

#include "EntityStore.h"
#include "Commons/Entities/Statement.h"

class StatementStore : public EntityStore<Statement> {
public:
	/*!
	 * Constructor for StatementStore
	 */
	StatementStore();
};