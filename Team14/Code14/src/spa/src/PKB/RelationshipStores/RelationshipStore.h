#pragma once

#include <memory>

#include "Commons/Entities/Entity.h"
#include "PKB/Commons/DoubleMapStore.h"
#include "PKB/EntityStores/EntityStore.h"

/**
 * @brief A class that stores Relationships in the SIMPLE source program using two Hashmaps as the underlying data structure
 * @details This class is a template class that takes in two Entity subclasses as a template parameter
 * This class is the superclass of ModifiesProcStores, UsesProcStores
 * @tparam T The type of Entity that the EntityMapStore stores on the left
 * @tparam U The type of Entity that the EntityMapStore stores on the right
 */
template <typename T, typename U>
class RelationshipStore : public DoubleMapStore<T, U, EntityStore<U>, EntityStore<T>, Entity, Entity> {
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

};
#include "RelationshipStore.hpp"