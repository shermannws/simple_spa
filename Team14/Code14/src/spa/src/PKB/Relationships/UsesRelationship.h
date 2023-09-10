#pragma once

#include "Relationship.h"
#include "RelationshipType.h"

class UsesRelationship : public Relationship {
public:
	static RelationshipType relationshipType;

	UsesRelationship(const std::shared_ptr<Entity> leftEntity,
		const std::shared_ptr<Entity> rightEntity);
};