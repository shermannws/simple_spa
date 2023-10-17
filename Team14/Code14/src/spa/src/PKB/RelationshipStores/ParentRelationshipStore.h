#pragma once

#include "Commons/Entities/Statement.h"
#include "RelationshipStore.h"

/**
 * @brief A class that stores ParentRelationships
 * @details A class that stores ParentRelationships
 */
class ParentRelationshipStore : public RelationshipStore<Statement, Statement> {
public:
    /**
     * @brief Construct a new ParentRelationshipStore object
     * @return A new ParentRelationshipStore object
     */
    ParentRelationshipStore();
};