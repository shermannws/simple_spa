#pragma once

#include "PKB/Managers/StmtToVarRelationshipManager.h"
#include "PKB/RelationshipStores/UsesRelationshipStore.h"

/**
 * @class UsesRelationshipManager is responsible for storing and retrieving the Uses relationships
 * between statements and variables.
 * @brief Manages the Uses relationships
 * @note A Uses relationship is a relationship between a statement and a variable where the statement uses the variable
 */
class UsesRelationshipManager : public StmtToVarRelationshipManager<UsesRelationshipStore> {
public:
    /**
     * @brief Constructs a UsesRelationshipManager object
     * @return A UsesRelationshipManager object
     */
    UsesRelationshipManager();
};
