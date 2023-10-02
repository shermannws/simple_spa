#include "CallsRelationship.h"

RelationshipType CallsRelationship::relationshipType = RelationshipType::Calls;


CallsRelationship::CallsRelationship(const std::shared_ptr<Procedure> leftEntity,
	const std::shared_ptr<Procedure> rightEntity, bool isDirect)
	: Relationship(this->relationshipType, leftEntity, rightEntity) {
	this->direct = isDirect;
};

bool CallsRelationship::isDirect() const {
	return this->direct;
}