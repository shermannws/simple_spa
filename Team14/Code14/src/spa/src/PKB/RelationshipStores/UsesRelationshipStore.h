#pragma once

#include "RelationshipStore.h"
#include "PKB/Relationships/UsesRelationship.h"

class UsesRelationshipStore : public RelationshipStore<UsesRelationship> {
public:
	/*!
	 * Constructor for UsesRelationshipStore
	 */
	UsesRelationshipStore();
};