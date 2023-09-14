#pragma once

#include <unordered_set>
#include <memory>

#include "../Relationships/Relationship.h"
#include "../Relationships/RelationshipHash.h"

template <typename T>
class RelationshipStore {
private:
    std::unordered_set<
        std::shared_ptr<T>,
        std::hash<std::shared_ptr<T>>,
        std::equal_to<std::shared_ptr<T>>
    > relationshipStore;

public:
    /*!
     * Constructor for RelationshipStore
     */
    RelationshipStore();

    /*!
     * Takes in a shared_ptr to a Relationship and store it into the RelationshipStore
     */
    void storeRelationship(std::shared_ptr<T> relationship);

    /*!
     * Takes in another Relationship object as argument and retrieves from the store the object that == the argument
     * Returns the Relatioship in the store if it exists, returns nullptr otherwise
     */
    std::shared_ptr<T> getRelationship(std::shared_ptr<T> relationship) const;

    /*!
     * Retrieve the begin iterator for the RelationshipStore
     */
    typename std::unordered_set<std::shared_ptr<T>>::iterator getBeginIterator();

    /*!
     * Retrieve the end iterator for the RelationshipStore
     */
    typename std::unordered_set<std::shared_ptr<T>>::iterator getEndIterator();
};

#include "RelationshipStore.cpp"