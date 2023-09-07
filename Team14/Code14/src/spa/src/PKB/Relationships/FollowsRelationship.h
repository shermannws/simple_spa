#pragma once

#include "Relationship.h"
#include "RelationshipType.h"

class FollowsRelationship : public Relationship {
public:
	static RelationshipType relationshipType;

	FollowsRelationship(const std::shared_ptr<Entity> leftEntity,
		const std::shared_ptr<Entity> rightEntity);
};