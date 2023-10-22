#pragma once

#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "RelationshipStore.h"

/**
 * @brief A class that stores UsesRelationships
 * @details A class that stores UsesRelationships
 */
class UsesRelationshipStore : public RelationshipStore<Statement, Variable> {
public:
    /**
     * @brief Construct a new UsesRelationshipStore object
     * @return A new UsesRelationshipStore object
     */
    UsesRelationshipStore();
};