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
    RelationshipStore();

    void storeRelationship(std::shared_ptr<Relationship> relationship);

    std::shared_ptr<Relationship> getRelationship(std::shared_ptr<Relationship> relationship) const;

    std::unordered_set<std::shared_ptr<Relationship>>::iterator getBeginIterator();

    std::unordered_set<std::shared_ptr<Relationship>>::iterator getEndIterator();
};

