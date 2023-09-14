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

template <>
struct std::hash<FollowsRelationship> {
	std::size_t operator()(const FollowsRelationship& relationship) const;
};

template <>
struct std::hash<std::shared_ptr<FollowsRelationship>> {
	std::size_t operator()(const std::shared_ptr<FollowsRelationship> relationshipPtr) const;
};

template <>
struct std::equal_to<std::shared_ptr<FollowsRelationship>> {
	bool operator()(
		std::shared_ptr<FollowsRelationship> const& lhs,
		std::shared_ptr<FollowsRelationship> const& rhs) const;
};