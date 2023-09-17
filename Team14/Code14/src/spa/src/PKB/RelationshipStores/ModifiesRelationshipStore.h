#pragma once

#include "RelationshipStore.h"
#include "PKB/Relationships/ModifiesRelationship.h"

class ModifiesRelationshipStore : public RelationshipStore<ModifiesRelationship> {
public:
	/*!
	 * Constructor for ModifiesRelationshipStore
	 */
	ModifiesRelationshipStore();
};