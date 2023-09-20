#pragma once

#include "FollowsRelationship.h"

RelationshipType FollowsRelationship::relationshipType = RelationshipType::Follows;


FollowsRelationship::FollowsRelationship(const std::shared_ptr<Statement> leftEntity,
	const std::shared_ptr<Statement> rightEntity, bool isDirect)
	: Relationship(this->relationshipType, leftEntity, rightEntity) {
    this->direct = isDirect;
};

bool FollowsRelationship::isDirect() const {
    return this->direct;
}