#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "ProcToVarRelationshipManager.h"
#include "PKB/RelationshipStores/ModifiesProcRelationshipStore.h"
#include "Commons/Entities/Procedure.h"
#include "Commons/Entities/Variable.h"

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
