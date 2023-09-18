#pragma once

#include "FollowsRelationship.h"

RelationshipType FollowsRelationship::relationshipType = RelationshipType::Follows;


FollowsRelationship::FollowsRelationship(const std::shared_ptr<Statement> leftEntity,
	const std::shared_ptr<Statement> rightEntity)
	: Relationship(this->relationshipType, leftEntity, rightEntity) {};