#pragma once

#include <unordered_map>
#include <memory>

#include "PKB/Commons/SetStore.h"

/**
 * @brief A class that stores Relationships in the SIMPLE source program using two Hashmaps as the underlying data structure
 * @details This class is a template class that takes in two Entity subclasses as a template parameter
 * This class is the superclass of ModifiesProcStores, UsesProcStores
 * @tparam T The type of Entity that the EntityMapStore stores on the left
 * @tparam U The type of Entity that the EntityMapStore stores on the right
 */
template <typename K1, typename K2, typename V1, typename V2, typename H1, typename H2>
class DoubleMapStore {
private:
    /**
     * @brief The unordered_map that stores all the Relationships of Entity Pairs (T, U)
     */
    std::unordered_map<
            std::shared_ptr<K1>,
            std::shared_ptr<V1>,
            std::hash<std::shared_ptr<H1>>,
            std::equal_to<std::shared_ptr<H1>>
    > leftToRightStore;

    /**
     * @brief The unordered_map that stores all the Relationships of Entity Pairs (U, T)
     */
    std::unordered_map<
            std::shared_ptr<K2>,
            std::shared_ptr<V2>,
            std::hash<std::shared_ptr<H2>>,
            std::equal_to<std::shared_ptr<H2>>
    > rightToLeftStore;

public:
    /**
     * @brief Construct a new EntityMapStore object
     * @return A new EntityMapStore object
     */
    DoubleMapStore();

    /**
     * @brief Adds an Entity pair to the store
     * @param left The left entity object to be added
     * @param right The right entity object to be added
     * @return None
     */
    void store(std::shared_ptr<K1> left, std::shared_ptr<K2> right);

    /**
     * @brief Return the EntityStore which the entity `left` maps to
     * @param left The left entity object used as key
     * @return The EntityStore which the entity `left` maps to
     */
    std::shared_ptr<V1> getRightEntitiesOf(std::shared_ptr<K1> left) const;

    /**
     * @brief Return the EntityStore which the entity `right` maps to
     * @param right The right entity object used as key
     * @return The EntityStore which the entity `right` maps to
     */
    std::shared_ptr<V2> getLeftEntitiesOf(std::shared_ptr<K2> right) const;

    /**
     * @brief Returns the start iterator to the leftToRight store
     * @return The start iterator to the leftToRight store
     */
    typename std::unordered_map<std::shared_ptr<K1>, std::shared_ptr<V1>>::iterator getLeftToRightBeginIterator();

    /**
     * @brief Returns the end iterator to the leftToRight store
     * @return The end iterator to the leftToRight store
     */
    typename std::unordered_map<std::shared_ptr<K1>, std::shared_ptr<V1>>::iterator getLeftToRightEndIterator();

    /**
     * @brief Returns the start iterator to the rightToLeft store
     * @return The start iterator to the rightToLeft store
     */
    typename std::unordered_map<std::shared_ptr<K2>, std::shared_ptr<V2>>::iterator getRightToLeftBeginIterator();

    /**
     * @brief Returns the end iterator to the rightToLeft store
     * @return The end iterator to the rightToLeft store
     */
    typename std::unordered_map<std::shared_ptr<K2>, std::shared_ptr<V2>>::iterator getRightToLeftEndIterator();

    bool isEmpty() const;

    void clear();
};
#include "DoubleMapStore.hpp"