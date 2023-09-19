#pragma once

#include "Relationship.h"
#include "RelationshipType.h"
#include "Commons/Entities/Statement.h"

class ParentRelationship : public Relationship<Statement, Statement> {
    bool direct;
public:
	/*!
	 * Static field specifying the relationshipType of the Relationship
	 */
	static RelationshipType relationshipType;

	/*!
	 * Constructor for FollowsRelationship
	 */
	ParentRelationship(const std::shared_ptr<Statement> parentEntity,
		const std::shared_ptr<Statement> childEntity, bool isDirect);

    bool isDirect() const;
};