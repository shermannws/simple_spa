#pragma once

#include "Relationship.h"
#include "RelationshipType.h"

class UsesRelationship : public Relationship {
public:
	/*!
	 * Static field specifying the relatioshipType of the Relationship
	 */
	static RelationshipType relationshipType;

	/*!
	 * Constructor for UsesRelationship
	 */
	UsesRelationship(const std::shared_ptr<Entity> leftEntity,
		const std::shared_ptr<Entity> rightEntity);
};