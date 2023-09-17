#pragma once

#include "ParentRelationship.h"

RelationshipType ParentRelationship::relationshipType = RelationshipType::Parent;


ParentRelationship::ParentRelationship(const std::shared_ptr<Statement> leftEntity,
	const std::shared_ptr<Statement> rightEntity)
	: Relationship(this->relationshipType, leftEntity, rightEntity) {};