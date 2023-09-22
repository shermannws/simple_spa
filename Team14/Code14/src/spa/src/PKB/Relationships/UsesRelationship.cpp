#include "UsesRelationship.h"

RelationshipType UsesRelationship::relationshipType = RelationshipType::Uses;

UsesRelationship::UsesRelationship(const std::shared_ptr<Statement> leftEntity,
	const std::shared_ptr<Variable> rightEntity)
	: Relationship(this->relationshipType, leftEntity, rightEntity) {};