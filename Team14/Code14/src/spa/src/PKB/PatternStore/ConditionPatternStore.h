#pragma once

#include "PKB/Commons/DoubleMapStore.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "Commons/Entities/Entity.h"
#include "PKB/EntityStores/VariableStore.h"
#include "PKB/EntityStores/StatementStore.h"

/**
 * @brief A class that stores all the conditional patterns
 * @details A class that stores all the conditional patterns
 */
class ConditionPatternStore : public DoubleMapStore<Statement, Variable, EntityStore<Variable>, EntityStore<Statement>, Entity, Entity> {
public:
    /**
     * @brief Construct a new ConditionPatternStore object
     * @return A new ConditionPatternStore object
     */
    ConditionPatternStore();
};