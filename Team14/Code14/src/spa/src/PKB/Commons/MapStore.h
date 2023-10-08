#pragma once

#include <unordered_map>
#include <memory>

#include "PKB/Commons/SetStore.h"

/**
 * @brief A class that stores objects using a map as the underlying data structure
 * @tparam K The type of object that the MapStore stores as the key
 * @tparam V The type of object that the MapStore stores as the value
 * @tparam H The type of hash used to hash the key in the map
 */
template <typename K, typename V, typename H>
class MapStore {
private:
    /**
     * @brief The unordered_map that stores K to V pairs in a Map
     */
    std::unordered_map<
            std::shared_ptr<K>,
            std::shared_ptr<V>,
            std::hash<std::shared_ptr<H>>,
            std::equal_to<std::shared_ptr<H>>
    > mapStore;

public:
    /**
     * @brief Construct a new DoubleMapStore object
     * @return A new DoubleMapStore object
     */
    MapStore();

    /**
     * @brief Adds an object pair to the store
     * @param key The key object to be added
     * @param value The value object to be added
     * @return None
     */
    void store(std::shared_ptr<K> key, std::shared_ptr<V> value);

    /**
     * @brief Return the value which the entity `key` maps to
     * @param key The key object used as key
     * @return The Store which the object `key` maps to
     */
    std::shared_ptr<V> getValueOf(std::shared_ptr<K> key) const;

    /**
     * @brief Returns the start iterator to the map store
     * @return The start iterator to the map store
     */
    typename std::unordered_map<std::shared_ptr<K>, std::shared_ptr<V>>::iterator getBeginIterator();

    /**
     * @brief Returns the end iterator to the map store
     * @return The end iterator to the map store
     */
    typename std::unordered_map<std::shared_ptr<K>, std::shared_ptr<V>>::iterator getEndIterator();

};
#include "DoubleMapStore.hpp"