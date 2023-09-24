#pragma once

#include "EntityStore.h"
#include "Commons/Entities/Variable.h"

class VariableStore : public EntityStore<Variable> {
public:
    /**
     * @brief Construct a new VariableStore object
     * @param None
     * @return A new VariableStore object
     */
    VariableStore();
};