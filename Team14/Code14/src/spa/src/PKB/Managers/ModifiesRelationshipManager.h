#pragma once

#include "PKB/Managers/StmtToVarRelationshipManager.h"
#include "PKB/RelationshipStores/ModifiesRelationshipStore.h"

/**
 * @class ModifiesRelationshipManager is responsible for storing and retrieving the Modifies relationships
 * between statements and variables.
 * @brief Manages the Modifies relationships
 * @note A Modifies relationship is a relationship between a statement and a variable where the statement modifies the
 * variable
 */
class ModifiesRelationshipManager : public StmtToVarRelationshipManager<ModifiesRelationshipStore> {
public:
    /**
     * @brief Constructs a ModifiesRelationshipManager object
     * @return A ModifiesRelationshipManager object
     */
    ModifiesRelationshipManager();
};
