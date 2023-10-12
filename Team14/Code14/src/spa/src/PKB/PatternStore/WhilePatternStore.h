#pragma once

#include "PKB/Commons/DoubleMapStore.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "Commons/Entities/Entity.h"
#include "PKB/EntityStores/VariableStore.h"
#include "PKB/EntityStores/StatementStore.h"

/**
 * @brief A class that stores all the while patterns
 * @details A class that stores all the while patterns
 */
class WhilePatternStore : public DoubleMapStore<Statement, Variable, VariableStore, StatementStore, Entity, Entity> {
public:
    /**
     * @brief Construct a new WhilePatternStore object
     * @return A new WhilePatternStore object
     */
    WhilePatternStore();
};