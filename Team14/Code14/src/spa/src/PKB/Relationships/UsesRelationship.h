#pragma once

#include "Relationship.h"
#include "RelationshipType.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"

class UsesRelationship : public Relationship<Statement, Variable> {
public:
	/*!
	 * Static field specifying the relatioshipType of the Relationship
	 */
	static RelationshipType relationshipType;

	/*!
	 * Constructor for UsesRelationship
	 */
	UsesRelationship(const std::shared_ptr<Statement> leftEntity,
		const std::shared_ptr<Variable> rightEntity);
};

template <>
struct std::hash<UsesRelationship> {
	std::size_t operator()(const UsesRelationship& relationship) const;
};

template <>
struct std::hash<std::shared_ptr<UsesRelationship>> {
	std::size_t operator()(const std::shared_ptr<UsesRelationship> relationshipPtr) const;
};

template <>
struct std::equal_to<std::shared_ptr<UsesRelationship>> {
	bool operator()(
		std::shared_ptr<UsesRelationship> const& lhs,
		std::shared_ptr<UsesRelationship> const& rhs) const;
};