#pragma once

#include "EntityStore.h"

template <typename T>
EntityStore<T>::EntityStore() = default;

template <typename T>
void EntityStore<T>::storeEntity(std::shared_ptr<T> entity) {
    this->entityStore.insert(entity);
}

template <typename T>
std::shared_ptr<std::vector<std::shared_ptr<Entity>>> EntityStore<T>::getAllEntities() const {
    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> entities = std::make_shared<std::vector<std::shared_ptr<Entity>>>();
    for (std::shared_ptr<Entity> entity : this->entityStore) {
        entities->push_back(entity);
    }
    return entities;
}

template <typename T>
std::shared_ptr<Entity> EntityStore<T>::getEntity(std::shared_ptr<T> entity) const {
    std::unordered_set<std::shared_ptr<T>>::const_iterator got = this->entityStore.find(entity);
    if (got == this->entityStore.end()) {
        return nullptr;
    }
    return *got;
}