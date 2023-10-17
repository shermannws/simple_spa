#pragma once

#include "Commons/Entities/Procedure.h"
#include "EntityStore.h"

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