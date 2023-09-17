#pragma once

#include "Relationship.h"
#include "RelationshipType.h"
#include "Commons/Entities/Statement.h"

class FollowsRelationship : public Relationship<Statement, Statement> {
public:
	/*!
	 * Static field specifying the relatioshipType of the Relationship
	 */
	static RelationshipType relationshipType;

	/*!
	 * Constructor for FollowsRelationship
	 */
	FollowsRelationship(const std::shared_ptr<Statement> leftEntity,
		const std::shared_ptr<Statement> rightEntity);
};