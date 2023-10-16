#pragma once

#include "PKB/Managers/StmtToStmtRelationshipManager.h"
#include "PKB/RelationshipStores/ParentRelationshipStore.h"

/**
 * @class ParentRelationshipManager is responsible for storing and retrieving
 * the Parent relationships between statements.
 * @brief Manages the Parent relationships
 * @note A Parent relationship is a relationship between two statements where
 * the first statement is the parent of the second statement
 */
class ParentRelationshipManager
    : public StmtToStmtRelationshipManager<ParentRelationshipStore> {
public:
    /**
     * @brief Constructs a ParentRelationshipManager object
     */
    ParentRelationshipManager();
};
