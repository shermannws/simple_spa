#pragma once

#include "EntityStore.h"

EntityStore::EntityStore() = default;

void EntityStore::storeEntity(std::shared_ptr<Entity> entity) {
	this->entityStore.insert(entity);
}

std::vector<Entity> EntityStore::getAllEntities() const {
    std::vector<Entity> entities = std::vector<Entity>();
    for (std::shared_ptr<Entity> entity : this->entityStore) {
        entities.push_back(*entity);
    }
    return entities;
}

std::shared_ptr<Entity> EntityStore::getEntity(std::shared_ptr<Entity> entity) const {
	std::unordered_set<std::shared_ptr<Entity>>::const_iterator got = this->entityStore.find(entity);
	if (got == this->entityStore.end()) {
		return nullptr;
	}
	return *got;
}