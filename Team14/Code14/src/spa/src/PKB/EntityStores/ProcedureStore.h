#pragma once

#include "EntityStore.h"
#include "Commons/Entities/Procedure.h"

/**
 * @brief A class that stores all the procedures in the SIMPLE source program
 */
class ProcedureStore : public EntityStore<Procedure> {
public:
    /**
     * @brief Construct a new ProcedureStore object
     * @return A new ProcedureStore object
     */
    ProcedureStore();
};