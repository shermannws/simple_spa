#pragma once

#include "EntityMapStore.h"
#include "Commons/Entities/Procedure.h"
#include "Commons/Entities/Variable.h"

/**
 * @brief A class that stores ModifiesProcRelationships (ModifiesProcedureRelationships)
 * @details A class that stores ModifiesProcRelationships
 */
class ModifiesProcRelationshipStore : public EntityMapStore<Procedure, Variable> {
public:
    /**
     * @brief Construct a new ModifiesProcRelationshipStore
     * @return A new ModifiesProcRelationshipStore object
     */
    ModifiesProcRelationshipStore();
};