#pragma once

#include "EntityMapStore.h"
#include "Commons/Entities/Procedure.h"
#include "Commons/Entities/Variable.h"

/**
 * @brief A class that stores UsesProcRelationships (UsesProcedureRelationships)
 * @details A class that stores UsesProcRelationships
 */
class UsesProcRelationshipStore : public EntityMapStore<Procedure, Variable> {
public:
    /**
     * @brief Construct a new UsesProcRelationshipStore
     * @return A new UsesProcRelationshipStore object
     */
    UsesProcRelationshipStore();
};