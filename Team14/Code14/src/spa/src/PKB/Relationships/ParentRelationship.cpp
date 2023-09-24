#include "ParentRelationship.h"

RelationshipType ParentRelationship::relationshipType = RelationshipType::Parent;


ParentRelationship::ParentRelationship(const std::shared_ptr<Statement> parentEntity,
	const std::shared_ptr<Statement> childEntity, bool isDirect)
	: Relationship(this->relationshipType, parentEntity, childEntity) {
    this->direct = isDirect;
};

bool ParentRelationship::isDirect() const {
    return this->direct;
}