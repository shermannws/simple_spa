#pragma once

#include "UsesRelationship.h"

RelationshipType UsesRelationship::relationshipType = RelationshipType::Uses;

UsesRelationship::UsesRelationship(const std::shared_ptr<Statement> leftEntity,
	const std::shared_ptr<Variable> rightEntity)
	: Relationship(this->relationshipType, leftEntity, rightEntity) {};

std::size_t std::hash<UsesRelationship>::operator()(const UsesRelationship& relationship) const {
	return std::hash<std::string>()(
		*(relationship.getLeftEntity()->getEntityValue()) +
		"," +
		*(relationship.getRightEntity()->getEntityValue()));
}

std::size_t std::hash<std::shared_ptr<UsesRelationship>>::operator()(const std::shared_ptr<UsesRelationship> relationshipPtr) const {
	return std::hash<UsesRelationship>()(*relationshipPtr.get());
}


bool std::equal_to<std::shared_ptr<UsesRelationship>>::operator()(
	std::shared_ptr<UsesRelationship> const& lhs,
	std::shared_ptr<UsesRelationship> const& rhs) const {
	return *lhs == *rhs;
}