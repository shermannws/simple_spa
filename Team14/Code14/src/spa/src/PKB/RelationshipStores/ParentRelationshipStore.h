#pragma once

#include "RelationshipStore.h"
#include "PKB/Relationships/ParentRelationship.h"

/**
 * @brief A class that stores ParentRelationships
 * @details A class that stores ParentRelationships
 */
class ParentRelationshipStore : public RelationshipStore<ParentRelationship> {
public:
    /**
     * @brief Construct a new ParentRelationshipStore object
     * @return A new ParentRelationshipStore object
     */
    ParentRelationshipStore();
};