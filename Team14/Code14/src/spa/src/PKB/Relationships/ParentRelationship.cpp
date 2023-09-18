#pragma once

#include "ParentRelationship.h"

RelationshipType ParentRelationship::relationshipType = RelationshipType::Parent;


ParentRelationship::ParentRelationship(const std::shared_ptr<Statement> parentEntity,
	const std::shared_ptr<Statement> childEntity)
	: Relationship(this->relationshipType, parentEntity, childEntity) {};