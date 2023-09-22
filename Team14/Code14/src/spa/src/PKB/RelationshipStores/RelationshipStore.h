#pragma once

#include <unordered_set>
#include <memory>

#include "../Relationships/Relationship.h"
#include "../Relationships/RelationshipHash.h"

/**
 * @brief A class that stores all the Relationships in the SIMPLE source program
 * @details This class is a template class that takes in a Relationship as a template parameter
 * This class is the superclass of all RelationshipStores
 * @tparam T
 */
template <typename T>
class RelationshipStore {
private:
    /**
     * @brief The unordered_set that stores all the Relationships
     */
    std::unordered_set<
        std::shared_ptr<T>,
        RelationshipPtrHash<T>,
        RelationshipPtrComparator<T>
    > relationshipStore;

public:
    /**
     * @brief Construct a new RelationshipStore object
     * @return A new RelationshipStore object
     */
    RelationshipStore();

    /**
     * @brief Adds a Relationship object to the store
     * @param relationship The Relationship object to be added
     * @return None
     */
    void storeRelationship(std::shared_ptr<T> relationship);

    /**
     * @brief Returns the Relationship from the RelationshipStore that is equal to the Relationship passed in
     * @param relationship The Relationship to be compared against
     * @return The Relationship from the RelationshipStore that is equal to the Relationship passed in
     */
    std::shared_ptr<T> getRelationship(std::shared_ptr<T> relationship) const;

    /**
     * @brief Returns true if the RelationshipStore is empty, false otherwise
     * @return True if the RelationshipStore is empty, false otherwise
     */
    bool isEmpty() const;

    /**
     * @brief Returns an iterator to the beginning of the store
     * @return An iterator to the beginning of the store
     */
    typename std::unordered_set<std::shared_ptr<T>>::iterator getBeginIterator();

    /**
     * @brief Returns an iterator to the end of the store
     * @return An iterator to the end of the store
     */
    typename std::unordered_set<std::shared_ptr<T>>::iterator getEndIterator();
};

#include "RelationshipStore.hpp"