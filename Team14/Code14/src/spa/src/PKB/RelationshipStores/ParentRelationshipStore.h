#pragma once

#include "RelationshipStore.h"
#include "PKB/Relationships/ParentRelationship.h"

class ParentRelationshipStore : public RelationshipStore<ParentRelationship> {
public:
	/*!
	 * Constructor for ParentRelationshipStore
	 */
	ParentRelationshipStore();
};