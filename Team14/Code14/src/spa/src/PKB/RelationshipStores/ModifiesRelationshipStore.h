#pragma once

#include "RelationshipStore.h"
#include "PKB/Relationships/ModifiesRelationship.h"

/**
 * @brief A class that stores ModifiesRelationships
 * @details A class that stores ModifiesRelationships
 */
class ModifiesRelationshipStore : public RelationshipStore<ModifiesRelationship> {
public:
	/**
     * @brief Construct a new ModifiesRelationshipStore object
     * @return A new ModifiesRelationshipStore object
     */
	ModifiesRelationshipStore();
};