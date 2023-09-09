#pragma once

#include <unordered_set>
#include <memory>

#include "../Relationships/Relationship.h"

class RelationshipStorage {
private:
    std::unordered_set<
        std::shared_ptr<Relationship>,
        std::hash<std::shared_ptr<Relationship>>,
        std::equal_to<std::shared_ptr<Relationship>>
    > relationshipStore;

public:
    RelationshipStorage();

    void storeRelationship(std::shared_ptr<Relationship> relationship);

    Relationship* getRelationship(std::shared_ptr<Relationship> relationship) const;
};

