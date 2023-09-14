#pragma once

#include "FollowsRelationship.h"

RelationshipType FollowsRelationship::relationshipType = RelationshipType::Follows;


FollowsRelationship::FollowsRelationship(const std::shared_ptr<Statement> leftEntity,
	const std::shared_ptr<Statement> rightEntity)
	: Relationship(this->relationshipType, leftEntity, rightEntity) {};

std::size_t std::hash<FollowsRelationship>::operator()(const FollowsRelationship& relationship) const {
	return std::hash<std::string>()(
		*(relationship.getLeftEntity()->getEntityValue()) +
		"," +
		*(relationship.getRightEntity()->getEntityValue()));
}

std::size_t std::hash<std::shared_ptr<FollowsRelationship>>::operator()(const std::shared_ptr<FollowsRelationship> relationshipPtr) const {
	return std::hash<FollowsRelationship>()(*relationshipPtr.get());
}


bool std::equal_to<std::shared_ptr<FollowsRelationship>>::operator()(
	std::shared_ptr<FollowsRelationship> const& lhs,
	std::shared_ptr<FollowsRelationship> const& rhs) const {
	return *lhs == *rhs;
}