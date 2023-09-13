#pragma once

#include <unordered_set>
#include <memory>

#include "../Relationships/Relationship.h"

class RelationshipStore {
private:
    std::unordered_set<
        std::shared_ptr<Relationship>,
        std::hash<std::shared_ptr<Relationship>>,
        std::equal_to<std::shared_ptr<Relationship>>
    > relationshipStore;

public:
    /*!
     * Constructor for RelationshipStore
     */
    RelationshipStore();

    /*!
     * Takes in a shared_ptr to a Relationship and store it into the RelationshipStore
     */
    void storeRelationship(std::shared_ptr<Relationship> relationship);

    /*!
     * Takes in another Relationship object as argument and retrieves from the store the object that == the argument
     * Returns the Relatioship in the store if it exists, returns nullptr otherwise
     */
    std::shared_ptr<Relationship> getRelationship(std::shared_ptr<Relationship> relationship) const;

    /*!
     * Retrieve the begin iterator for the RelationshipStore
     */
    std::unordered_set<std::shared_ptr<Relationship>>::iterator getBeginIterator();

    /*!
     * Retrieve the end iterator for the RelationshipStore
     */
    std::unordered_set<std::shared_ptr<Relationship>>::iterator getEndIterator();
};

