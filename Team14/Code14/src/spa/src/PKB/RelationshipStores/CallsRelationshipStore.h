#pragma once

#include "Commons/Entities/Procedure.h"
#include "PKB/RelationshipStores/RelationshipStore.h"

/**
 * @brief A class that stores CallsRelationships
 * @details A class that stores CallsRelationships
 */
class CallsRelationshipStore : public RelationshipStore<Procedure, Procedure> {
public:
    /**
     * @brief Construct a new FollowsRelationshipStore object
     * @return A new FollowsRelationshipStore object
     */
    CallsRelationshipStore();
};