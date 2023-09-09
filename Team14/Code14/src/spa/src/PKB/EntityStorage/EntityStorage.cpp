#include "EntityStorage.h"

EntityStorage::EntityStorage() {}

void EntityStorage::storeEntity(std::shared_ptr<Entity> entity) {
	this->entityStore.insert(entity);
}

Entity* EntityStorage::getEntity(std::shared_ptr<Entity> entity) const {
	std::unordered_set<std::shared_ptr<Entity>>::const_iterator got = this->entityStore.find(entity);
	if (got == this->entityStore.end()) {
		return nullptr;
	}
	return (*got).get();
}