#pragma once

#include "Commons/Entities/Procedure.h"
#include "Commons/Entities/Variable.h"
#include "PKB/RelationshipStores/RelationshipStore.h"

/**
 * @brief A class that stores ModifiesProcRelationships
 * (ModifiesProcedureRelationships)
 * @details A class that stores ModifiesProcRelationships
 */
class ModifiesProcRelationshipStore
    : public RelationshipStore<Procedure, Variable> {
public:
    /**
     * @brief Construct a new ModifiesProcRelationshipStore
     * @return A new ModifiesProcRelationshipStore object
     */
    ModifiesProcRelationshipStore();
};