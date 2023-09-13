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

/*!
 * Defintions are in the header file due to C++ constraint for using generics
 * https://stackoverflow.com/questions/456713/why-do-i-get-unresolved-external-symbol-errors-when-using-templates
 */

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