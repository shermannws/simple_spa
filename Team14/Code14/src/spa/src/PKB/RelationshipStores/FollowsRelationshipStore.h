#pragma once

#include "RelationshipStore.h"
#include "PKB/Relationships/FollowsRelationship.h"

/**
 * @brief A class that stores FollowsRelationships
 * @details A class that stores FollowsRelationships
 */
class FollowsRelationshipStore : public RelationshipStore<FollowsRelationship> {
public:
    /**
     * @brief Construct a new FollowsRelationshipStore object
     * @return A new FollowsRelationshipStore object
     */
    FollowsRelationshipStore();
};