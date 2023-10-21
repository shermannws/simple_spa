#pragma once

#include "Commons/Entities/Constant.h"
#include "EntityStore.h"

/**
 * @brief A class that stores all the constants in the SIMPLE source program
 * @details A class that stores all the constants in the SIMPLE source program
 */
class ConstantStore : public EntityStore<Constant> {
public:
    /**
     * @brief Construct a new ConstantStore object
     * @return A new ConstantStore object
     */
    ConstantStore();
};