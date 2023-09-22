#include "ModifiesRelationship.h"

RelationshipType ModifiesRelationship::relationshipType = RelationshipType::Modifies;


ModifiesRelationship::ModifiesRelationship(const std::shared_ptr<Statement> leftEntity,
	const std::shared_ptr<Variable> rightEntity)
	: Relationship(this->relationshipType, leftEntity, rightEntity) {};