#pragma once

#include "EntityStore.h"
#include "Commons/Entities/Procedure.h"

class ProcedureStore : public EntityStore<Procedure> {
public:
	/*!
	 * Constructor for ProcedureStore
	 */
	ProcedureStore();
};