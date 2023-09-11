#pragma once

#include "RelationshipStorage.h"

RelationshipStorage::RelationshipStorage() {}

void RelationshipStorage::storeRelationship(std::shared_ptr<Relationship> relationship) {
	this->relationshipStore.insert(relationship);
}

std::shared_ptr<Relationship> RelationshipStorage::getRelationship(std::shared_ptr<Relationship> relationship) const {
	std::unordered_set<std::shared_ptr<Relationship>>::const_iterator got = this->relationshipStore.find(relationship);
	if (got == this->relationshipStore.end()) {
		return nullptr;
	}
	return *got;
}

std::unordered_set<std::shared_ptr<Relationship>>::iterator RelationshipStorage::getBeginIterator() {
    return this->relationshipStore.begin();
}

std::unordered_set<std::shared_ptr<Relationship>>::iterator RelationshipStorage::getEndIterator() {
    return this->relationshipStore.end();
}