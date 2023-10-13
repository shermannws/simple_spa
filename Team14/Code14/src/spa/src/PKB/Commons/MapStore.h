#pragma once

#include <unordered_map>
#include <memory>

#include "PKB/Commons/SetStore.h"

/**
 * @brief A class that stores objects using a map as the underlying data structure
 * @tparam K The type of object that the MapStore stores as the key
 * @tparam V The type of object that the MapStore stores as the value
 */
template <typename K, typename V>
class MapStore {
private:
    /**
     * @brief The unordered_map that stores K to V pairs in a Map
     */
    std::unordered_map<K, std::shared_ptr<V>> mapStore;

protected:
    /**
     * @brief Store the argument `map` as the mapStore
     * @param map The map to be stored
     */
    void setMapStore(std::unordered_map<K, std::shared_ptr<V>> map);

public:
    /**
     * @brief Construct a new MapStore object
     * @return A new MapStore object
     */
    MapStore();

    /**
     * @brief Returns the start iterator to the map store
     * @return The start iterator to the map store
     */
    typename std::unordered_map<K, std::shared_ptr<V>>::iterator getBeginIterator();

    /**
     * @brief Returns the end iterator to the map store
     * @return The end iterator to the map store
     */
    typename std::unordered_map<K, std::shared_ptr<V>>::iterator getEndIterator();

};
#include "MapStore.hpp"