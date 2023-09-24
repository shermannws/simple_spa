#pragma once

#include <string>
#include <memory>
#include <vector>

#include "Commons/Entities/Entity.h"
#include "PKB/RelationshipStores/RelationshipStore.h"
#include "PKB/EntityStores/EntityStore.h"

/**
 * @brief A class that contains utility functions for the Managers
 * @details A class that contains utility functions for the Managers
 */
class ManagerUtils {
public:
    /**
     * @brief A function that retrieves objects from a store based on a matcher and getter function
     * @tparam E The type of the object to be retrieved
     * @tparam S The type of the store to be retrieved from
     * @tparam R The type of the object stored in the store
     * @param store The store to be retrieved from
     * @param matcher The matcher function that returns a boolean value indicating if the object matches the criteria
     * @param getter The getter function that returns the object
     * @return A vector of entities
     */
    template<typename E, typename S, typename R>
    static std::vector<E>
    getFromStore(std::shared_ptr<S> store, std::function<bool(R&)> matcher, std::function<E(R&)> getter);

    /**
     * @brief A function that retrieves entities from a store based on a matcher and getter function
     * @tparam S The type of the store to be retrieved from
     * @tparam R The type of the object stored in the store
     * @param store The store to be retrieved from
     * @param matcher The matcher function that returns a boolean value indicating if the object matches the criteria
     * @param getter The getter function that returns the entity
     * @return A vector of entities
     */
    template<typename S, typename R>
    static std::vector<Entity>
    getEntitiesFromStore(std::shared_ptr<S> store, std::function<bool(R&)> matcher, std::function<Entity(R&)> getter);

    /**
     * @brief A function that retrieves entities from a relationship store based on a matcher and getter function
     * @tparam R The type of the relationship stored in the store
     * @param store The store to be retrieved from
     * @param matcher The matcher function that returns a boolean value indicating if the relationship matches the criteria
     * @param getter The getter function that returns the entity
     * @return A vector of entities
     */
    template<typename R>
    static std::vector<Entity>
    getEntitiesFromRelationshipStore(std::shared_ptr<RelationshipStore<R>> store, std::function<bool(R&)> matcher, std::function<Entity(R&)> getter);

    /**
     * @brief A function that retrieves entities from an entity store based on a matcher and getter function
     * @tparam E The type of the entity to be retrieved
     * @param store The store to be retrieved from
     * @param matcher The matcher function that returns a boolean value indicating if the entity matches the criteria
     * @param getter The getter function that returns the entity
     * @return A vector of entities
     */
    template<typename E>
    static std::vector<Entity>
    getEntitiesFromEntityStore(std::shared_ptr<EntityStore<E>> store, std::function<bool(E&)> matcher, std::function<Entity(E&)> getter);

    /**
     * @brief A function that retrieves entity pairs from a store based on a matcher and getter function
     * @tparam S The type of store to be retrieved from
     * @tparam R The type of the object stored in the store
     * @param store The store to be retrieved from
     * @param matcher The matcher function that returns a boolean value indicating if the object matches the criteria
     * @param getter The getter function that returns the entity pair
     * @return A vector of entity pairs
     */
    template<typename S, typename R>
    static std::vector<std::vector<Entity>>
    getEntityPairsFromStore(std::shared_ptr<S> store, std::function<bool(R&)> matcher, std::function<std::vector<Entity>(R&)> getter);

    /**
     * @brief A function that retrieves entity pairs from a relationship store based on a matcher and getter function
     * @tparam R The type of the relationship stored in the store
     * @param store The store to be retrieved from
     * @param matcher The matcher function that returns a boolean value indicating if the relationship matches the criteria
     * @param getter The getter function that returns the entity pair
     * @return A vector of entity pairs
     */
    template<typename R>
    static std::vector<std::vector<Entity>>
    getEntityPairsFromRelationshipStore(std::shared_ptr<RelationshipStore<R>> store, std::function<bool(R&)> matcher, std::function<std::vector<Entity>(R&)> getter);
};