#pragma once

#include "RelationshipStore.h"
#include "PKB/Relationships/FollowsRelationship.h"

class FollowsRelationshipStore : public RelationshipStore<FollowsRelationship> {
public:
	/*!
	 * Constructor for FollowsRelationshipStore
	 */
	FollowsRelationshipStore();
};