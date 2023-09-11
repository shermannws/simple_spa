#pragma once

#include "EntityStorage.h"

EntityStorage::EntityStorage() = default;

void EntityStorage::storeEntity(std::shared_ptr<Entity> entity) {
	this->entityStore.insert(entity);
}

std::shared_ptr<std::vector<std::shared_ptr<Entity>>> EntityStorage::getAllEntities() const {
    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> entities = std::make_shared<std::vector<std::shared_ptr<Entity>>>();
    for (std::shared_ptr<Entity> entity : this->entityStore) {
        entities->push_back(entity);
    }
    return entities;
}

std::shared_ptr<Entity> EntityStorage::getEntity(std::shared_ptr<Entity> entity) const {
	std::unordered_set<std::shared_ptr<Entity>>::const_iterator got = this->entityStore.find(entity);
	if (got == this->entityStore.end()) {
		return nullptr;
	}
	return *got;
}