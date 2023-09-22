#pragma once

#include "RelationshipStore.h"
#include "PKB/Relationships/UsesRelationship.h"

/**
 * @brief A class that stores UsesRelationships
 * @details A class that stores UsesRelationships
 */
class UsesRelationshipStore : public RelationshipStore<UsesRelationship> {
public:
	/**
     * @brief Construct a new UsesRelationshipStore object
     * @return A new UsesRelationshipStore object
     */
	UsesRelationshipStore();
};