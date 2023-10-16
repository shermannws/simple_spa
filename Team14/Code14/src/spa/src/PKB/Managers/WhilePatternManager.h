#pragma once

#include <cassert>

#include "PKB/Managers/ConditionPatternManager.h"
#include "PKB/PatternStore/WhilePatternStore.h"

/**
 * @class WhilePatternManager is responsible for storing and retrieving the
 * While statement patterns
 * @brief Manages the While statement patterns
 */
class WhilePatternManager : public ConditionPatternManager<WhilePatternStore> {
public:
    /**
     * @brief Constructs a WhilePatternManager object
     * @return A WhilePatternManager object
     */
    WhilePatternManager();

    /**
     * @brief Stores the While statement pattern
     * @param stmt The While statement
     * @param vars The vector of control variable in the While statement
     */
    void storeWhilePattern(
            std::shared_ptr<Statement> stmt,
            std::shared_ptr<std::vector<std::shared_ptr<Variable>>> vars);
};