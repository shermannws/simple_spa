#pragma once

#include <unordered_set>
#include <vector>
#include <memory>

#include "../../Commons/Entities/Entity.h"

template <typename T>
class EntityStore {
private:
    std::unordered_set<
        std::shared_ptr<T>,
        std::hash<std::shared_ptr<Entity>>,
        std::equal_to<std::shared_ptr<Entity>>
    > entityStore;

public:
    /*!
     * Constructor for EntityStore
     */
    EntityStore();

    /*!
     * Takes in as argumennt an entity and store it into the EntityStore
     */
    void storeEntity(std::shared_ptr<T> entity);

    /*!
     * Takes in as argumet an entity and retrieves an entiy that == the argument
     * Returns the Entity if it exists, retur nullptr otherwise
     */
    std::shared_ptr<Entity> getEntity(std::shared_ptr<T> entity) const;

    /*!
     * Returns all the Entities in the EntityStore in a vector
     */
    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getAllEntities() const;
};

#include "EntityStore.cpp"