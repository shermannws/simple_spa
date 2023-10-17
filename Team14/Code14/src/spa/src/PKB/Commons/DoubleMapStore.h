#pragma once

#include <memory>
#include <unordered_map>

#include "PKB/Commons/SetStore.h"

/**
 * @brief A class that stores objects using two Hashmaps as the underlying data structure
 * @tparam K1 The type of object that the DoubleMapStore stores on the left
 * @tparam K2 The type of object that the DoubleMapStore stores on the right
 * @tparam V1 The type of store that is used to store K2 in the leftToRightStore
 * @tparam V2 The type of store that is used to store K1 in the rightToLeftStore
 * @tparam H1 The type of hash used to hash the key in the leftToRightStore
 * @tparam H2 The type of hash used to hash the key in the rightToLeftStore
 */
template<typename K1, typename K2, typename V1, typename V2, typename H1, typename H2>
class DoubleMapStore {
private:
    /**
     * @brief The unordered_map that stores K1 to K2 pairs using V1 as the underlying data structure
     */
    std::unordered_map<std::shared_ptr<K1>, std::shared_ptr<V1>, std::hash<std::shared_ptr<H1>>,
                       std::equal_to<std::shared_ptr<H1>>>
            leftToRightStore;

    /**
     * @brief The unordered_map that stores K2 to K1 pairs using V2 as the underlying data structure
     */
    std::unordered_map<std::shared_ptr<K2>, std::shared_ptr<V2>, std::hash<std::shared_ptr<H2>>,
                       std::equal_to<std::shared_ptr<H2>>>
            rightToLeftStore;

public:
    /**
     * @brief Construct a new DoubleMapStore object
     * @return A new DoubleMapStore object
     */
    DoubleMapStore();

    /**
     * @brief Adds an object pair pair to the store
     * @param left The left object to be added
     * @param right The right object to be added
     * @return None
     */
    void store(std::shared_ptr<K1> left, std::shared_ptr<K2> right);

    /**
     * @brief Return the Store which the entity `left` maps to
     * @param left The left object used as key
     * @return The Store which the object `left` maps to
     */
    std::shared_ptr<V1> getRightEntitiesOf(std::shared_ptr<K1> left) const;

    /**
     * @brief Return the Store which the entity `right` maps to
     * @param right The right object used as key
     * @return The Store which the object `right` maps to
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

    /**
     * @brief Returns whether the DoubleMapStore is empty
     * @return True if the DoubleMapStore is empty, false otherwise
     */
    bool isEmpty() const;

    /**
     * @brief Clears the DoubleMapStore
     * @return None
     */
    void clear();
};
#include "DoubleMapStore.hpp"