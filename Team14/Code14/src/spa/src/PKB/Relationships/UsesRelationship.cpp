#pragma once

#include "UsesRelationship.h"

RelationshipType UsesRelationship::relationshipType = RelationshipType::Uses;

UsesRelationship::UsesRelationship(const std::shared_ptr<Entity> leftEntity,
	const std::shared_ptr<Entity> rightEntity)
	: Relationship(this->relationshipType, leftEntity, rightEntity) {};