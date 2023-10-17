#pragma once

#include "ProcToVarRelationshipManager.h"
#include "PKB/RelationshipStores/ModifiesProcRelationshipStore.h"

/**
 * @class ModifiesProcRelationshipManager is responsible for storing and retrieving the Modifies relationships (Procedure)
 * between procedurs and variables.
 * @brief Manages the Modifies (Procedure) relationships
 * @note A Modifies relationship is a relationship between a procedure and a variable where the procedure modifies the variable
 */
class ModifiesProcRelationshipManager : public ProcToVarRelationshipManager<ModifiesProcRelationshipStore> {
public:
    /**
     * @brief Constructs a ModifiesProcRelationshipManager object
     * @return A ModifiesProcRelationshipManager object
     */
    ModifiesProcRelationshipManager();
};
