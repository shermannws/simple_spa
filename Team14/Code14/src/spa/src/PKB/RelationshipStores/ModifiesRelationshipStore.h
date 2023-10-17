#pragma once

#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "RelationshipStore.h"

/**
 * @brief A class that stores ModifiesRelationships
 * @details A class that stores ModifiesRelationships
 */
class ModifiesRelationshipStore : public RelationshipStore<Statement, Variable> {
public:
    /**
     * @brief Construct a new ModifiesRelationshipStore object
     * @return A new ModifiesRelationshipStore object
     */
    ModifiesRelationshipStore();
};