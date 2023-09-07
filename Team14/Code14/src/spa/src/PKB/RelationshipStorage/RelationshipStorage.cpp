#include "RelationshipStorage.h"

RelationshipStorage::RelationshipStorage() {}

void RelationshipStorage::storeRelationship(std::shared_ptr<Relationship> relationship) {
	this->relationshipStore.insert(relationship);
}

Relationship* RelationshipStorage::getRelationship(std::shared_ptr<Relationship> relationship) const {
	std::unordered_set<std::shared_ptr<Relationship>>::const_iterator got = this->relationshipStore.find(relationship);
	if (got == this->relationshipStore.end()) {
		return nullptr;
	}
	return (*got).get();
}