#pragma once

#include "Relationship.h"
#include "RelationshipType.h"
#include "Commons/Entities/Statement.h"

class ParentRelationship : public Relationship<Statement, Statement> {
public:
	/*!
	 * Static field specifying the relatioshipType of the Relationship
	 */
	static RelationshipType relationshipType;

	/*!
	 * Constructor for FollowsRelationship
	 */
	ParentRelationship(const std::shared_ptr<Statement> parentEntity,
		const std::shared_ptr<Statement> childEntity);
};