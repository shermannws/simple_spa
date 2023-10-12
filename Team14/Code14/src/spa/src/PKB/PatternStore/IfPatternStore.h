#pragma once

#include "PKB/Commons/DoubleMapStore.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "Commons/Entities/Entity.h"
#include "PKB/EntityStores/VariableStore.h"
#include "PKB/EntityStores/StatementStore.h"

/**
 * @brief A class that stores all the if patterns
 * @details A class that stores all the if patterns
 */
class IfPatternStore : public DoubleMapStore<Statement, Variable, VariableStore, StatementStore, Entity, Entity> {
public:
    /**
     * @brief Construct a new IfPatternStore object
     * @return A new IfPatternStore object
     */
    IfPatternStore();
};