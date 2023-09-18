#pragma once

#include "Relationship.h"
#include "RelationshipType.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"

class ModifiesRelationship : public Relationship<Statement, Variable> {
public:
	/*!
	 * Static field specifying the relatioshipType of the Relationship
	 */
	static RelationshipType relationshipType;

	/*!
	 * Constructor for ModifiesRelationship
	 */
	ModifiesRelationship(const std::shared_ptr<Statement> leftEntity,
		const std::shared_ptr<Variable> rightEntity);
};