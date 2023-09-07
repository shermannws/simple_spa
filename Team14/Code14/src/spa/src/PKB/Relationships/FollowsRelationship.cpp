#pragma once

#include "FollowsRelationship.h"

RelationshipType FollowsRelationship::relationshipType = RelationshipType::Follows;


FollowsRelationship::FollowsRelationship(const std::shared_ptr<Entity> leftEntity,
	const std::shared_ptr<Entity> rightEntity)
	: Relationship(this->relationshipType, leftEntity, rightEntity) {};