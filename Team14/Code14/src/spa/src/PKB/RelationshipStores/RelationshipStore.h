#pragma once

#include <unordered_set>
#include <memory>

#include "../Relationships/Relationship.h"

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


// Definition in header file due to use of Generics to define base class RelationshipStore

template <typename T>
RelationshipStore<T>::RelationshipStore() {}

template <typename T>
void RelationshipStore<T>::storeRelationship(std::shared_ptr<T> relationship) {
    this->relationshipStore.insert(relationship);
}

template <typename T>
std::shared_ptr<T> RelationshipStore<T>::getRelationship(std::shared_ptr<T> relationship) const {
    std::unordered_set<std::shared_ptr<T>>::const_iterator got = this->relationshipStore.find(relationship);
    if (got == this->relationshipStore.end()) {
        return nullptr;
    }
    return *got;
}

template <typename T>
typename std::unordered_set<std::shared_ptr<T>>::iterator RelationshipStore<T>::getBeginIterator() {
    return this->relationshipStore.begin();
}

template <typename T>
typename std::unordered_set<std::shared_ptr<T>>::iterator RelationshipStore<T>::getEndIterator() {
    return this->relationshipStore.end();
}