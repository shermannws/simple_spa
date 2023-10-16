#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "Commons/Entities/Procedure.h"
#include "Commons/Entities/Variable.h"
#include "PKB/RelationshipStores/UsesProcRelationshipStore.h"
#include "ProcToVarRelationshipManager.h"

/**
 * @class UsesProcRelationshipManager is responsible for storing and retrieving
 * the Uses relationships (Procedure) between procedurs and variables.
 * @brief Manages the Uses (Procedure) relationships
 * @note A Uses relationship is a relationship between a procedure and a
 * variable where the procedure uses the variable
 */
class UsesProcRelationshipManager
    : public ProcToVarRelationshipManager<UsesProcRelationshipStore> {
public:
    /**
     * @brief Constructs a UsesProcRelationshipManager object
     * @return A UsesProcRelationshipManager object
     */
    UsesProcRelationshipManager();
};
