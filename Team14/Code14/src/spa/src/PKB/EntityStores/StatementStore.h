#pragma once

#include "EntityStore.h"
#include "Commons/Entities/Statement.h"

/**
 * @brief A class that stores all the statements in the SIMPLE source program
 */
class StatementStore : public EntityStore<Statement> {
public:
    /**
     * @brief Construct a new StatementStore object
     * @return A new StatementStore object
     */
    StatementStore();
};