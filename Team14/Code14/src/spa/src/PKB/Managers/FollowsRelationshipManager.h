#pragma once

#include "PKB/Managers/StmtToStmtRelationshipManager.h"
#include "PKB/RelationshipStores/FollowsRelationshipStore.h"

/**
 * @class FollowsRelationshipManager is responsible for storing the Follows
 * relationship
 * @brief Manages the Follows relationship
 * @note: A Follows relationship is a relationship between two statements where
 * the first statement is executed before the second statement
 */
class FollowsRelationshipManager
    : public StmtToStmtRelationshipManager<FollowsRelationshipStore> {
public:
    /**
     * @brief Constructs a FollowsRelationshipManager object
     * @return A FollowsRelationshipManager object
     */
    FollowsRelationshipManager();
};
