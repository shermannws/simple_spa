#pragma once

#include <memory>
#include <unordered_set>
#include <vector>

/*!
 * @brief A template class that stores objects in a Set
 * @tparam T The type of the object that the SetStore stores
 * @tparam H The type of hash used to hash the stored object
 */
template<typename T, typename H>
class SetStore {
protected:
    /**
     * @brief The unordered_set that stores all the objects
     */
    std::unordered_set<std::shared_ptr<T>, std::hash<std::shared_ptr<H>>, std::equal_to<std::shared_ptr<H>>> storage;

public:
    /**
     * @brief Construct a new EntityStore object
     * @return A new EntityStore object
     */
    SetStore();

    /**
     * @brief Adds an object to the store
     * @param object The object to be stored
     * @return None
     */
    void store(std::shared_ptr<T> object);

    /**
     * @brief Retrieve the start iterator for the SetStore
     * @return The start iterator for the SetStore
     */
    typename std::unordered_set<std::shared_ptr<T>>::iterator getBeginIterator();

    /**
     * @brief Retrieve the end iterator for the SetStore
     * @return The end iterator for the SetStore
     */
    typename std::unordered_set<std::shared_ptr<T>>::iterator getEndIterator();

    /**
     * @brief Returns the object from the SetStore that is equal to the object passed in
     * @param object The object to be compared against
     * @return The object from the SetStore that is equal to the object passed in
     */
    std::shared_ptr<T> get(std::shared_ptr<T> object) const;

    /**
     * @brief Returns whether the SetStore is empty
     * @return True if the SetStore is empty, false otherwise
     */
    bool isEmpty() const;

    std::shared_ptr<T> first() const;
};

#include "SetStore.hpp"