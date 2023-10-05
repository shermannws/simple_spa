#pragma once

#include <unordered_map>
#include <memory>

#include "Commons/Entities/Entity.h"
#include "PKB/EntityStores/EntityStore.h"

/**
 * @brief A class that stores Relationships in the SIMPLE source program using two Hashmaps as the underlying data structure
 * @details This class is a template class that takes in two Entity subclasses as a template parameter
 * This class is the superclass of ModifiesProcStores, UsesProcStores
 * @tparam T The type of Entity that the EntityMapStore stores on the left
 * @tparam U The type of Entity that the EntityMapStore stores on the right
 */
template <typename T, typename U>
class RelationshipStore {
private:
    /**
     * @brief The unordered_map that stores all the Relationships of Entity Pairs (T, U)
     */
    std::unordered_map<
            std::shared_ptr<T>,
            std::shared_ptr<EntityStore<U>>,
            std::hash<std::shared_ptr<Entity>>,
            std::equal_to<std::shared_ptr<Entity>>
    > leftToRightStore;

    /**
     * @brief The unordered_map that stores all the Relationships of Entity Pairs (U, T)
     */
    std::unordered_map<
            std::shared_ptr<U>,
            std::shared_ptr<EntityStore<T>>,
            std::hash<std::shared_ptr<Entity>>,
            std::equal_to<std::shared_ptr<Entity>>
    > rightToLeftStore;

public:
    /**
     * @brief Construct a new EntityMapStore object
     * @return A new EntityMapStore object
     */
    RelationshipStore();

    /**
     * @brief Adds an Entity pair to the store
     * @param left The left entity object to be added
     * @param right The right entity object to be added
     * @return None
     */
    void storeRelationship(std::shared_ptr<T> left, std::shared_ptr<U> right);

    /**
     * @brief Return the EntityStore which the entity `left` maps to
     * @param left The left entity object used as key
     * @return The EntityStore which the entity `left` maps to
     */
    std::shared_ptr<EntityStore<U>> getRightEntitiesOf(std::shared_ptr<T> left) const;

    /**
     * @brief Return the EntityStore which the entity `right` maps to
     * @param right The right entity object used as key
     * @return The EntityStore which the entity `right` maps to
     */
    std::shared_ptr<EntityStore<T>> getLeftEntitiesOf(std::shared_ptr<U> right) const;

    /**
     * @brief Returns the start iterator to the leftToRight store
     * @return The start iterator to the leftToRight store
     */
    typename std::unordered_map<std::shared_ptr<T>, std::shared_ptr<EntityStore<U>>>::iterator getLeftToRightBeginIterator();

    /**
     * @brief Returns the end iterator to the leftToRight store
     * @return The end iterator to the leftToRight store
     */
    typename std::unordered_map<std::shared_ptr<T>, std::shared_ptr<EntityStore<U>>>::iterator getLeftToRightEndIterator();

    /**
     * @brief Returns the start iterator to the rightToLeft store
     * @return The start iterator to the rightToLeft store
     */
    typename std::unordered_map<std::shared_ptr<T>, std::shared_ptr<EntityStore<U>>>::iterator getRightToLeftBeginIterator();

    /**
     * @brief Returns the end iterator to the rightToLeft store
     * @return The end iterator to the rightToLeft store
     */
    typename std::unordered_map<std::shared_ptr<T>, std::shared_ptr<EntityStore<U>>>::iterator getRightToLeftEndIterator();

    bool isEmpty() const;

    void clear();
};
#include "RelationshipStore.hpp"