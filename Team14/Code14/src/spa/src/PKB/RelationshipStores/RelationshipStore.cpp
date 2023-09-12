#pragma once

#include "RelationshipStore.h"

RelationshipStore::RelationshipStore() {}

void RelationshipStore::storeRelationship(std::shared_ptr<Relationship> relationship) {
	this->relationshipStore.insert(relationship);
}

std::shared_ptr<Relationship> RelationshipStore::getRelationship(std::shared_ptr<Relationship> relationship) const {
	std::unordered_set<std::shared_ptr<Relationship>>::const_iterator got = this->relationshipStore.find(relationship);
	if (got == this->relationshipStore.end()) {
		return nullptr;
	}
	return *got;
}

std::unordered_set<std::shared_ptr<Relationship>>::iterator RelationshipStore::getBeginIterator() {
    return this->relationshipStore.begin();
}

std::unordered_set<std::shared_ptr<Relationship>>::iterator RelationshipStore::getEndIterator() {
    return this->relationshipStore.end();
}