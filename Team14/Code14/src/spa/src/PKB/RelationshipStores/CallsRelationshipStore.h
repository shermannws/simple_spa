#pragma once

#include "RelationshipStore.h"
#include "PKB/Relationships/CallsRelationship.h"

/**
 * @brief A class that stores CallsRelationships
 * @details A class that stores CallsRelationships
 */
class CallsRelationshipStore : public RelationshipStore<CallsRelationship> {
public:
    /**
     * @brief Construct a new FollowsRelationshipStore object
     * @return A new FollowsRelationshipStore object
     */
    CallsRelationshipStore();
};