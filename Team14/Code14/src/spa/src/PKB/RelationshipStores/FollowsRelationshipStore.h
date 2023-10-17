#pragma once

#include "Commons/Entities/Statement.h"
#include "RelationshipStore.h"

/**
 * @brief A class that stores FollowsRelationships
 * @details A class that stores FollowsRelationships
 */
class FollowsRelationshipStore
    : public RelationshipStore<Statement, Statement> {
public:
    /**
     * @brief Construct a new FollowsRelationshipStore object
     * @return A new FollowsRelationshipStore object
     */
    FollowsRelationshipStore();
};