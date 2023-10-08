#pragma once

#include <memory>
#include <vector>

#include "PKB/RelationshipStores/ParentRelationshipStore.h"
#include "Commons/Entities/Statement.h"
#include "PKB/Managers/StmtToStmtRelationshipManager.h"

/**
 * @class ParentRelationshipManager is responsible for storing and retrieving the Parent relationships
 * between statements.
 * @brief Manages the Parent relationships
 * @note A Parent relationship is a relationship between two statements where the first statement is the parent of the second statement
 */
class ParentRelationshipManager : public StmtToStmtRelationshipManager<ParentRelationshipStore> {
public:
    /**
     * @brief Constructs a ParentRelationshipManager object
     */
    ParentRelationshipManager();

};
