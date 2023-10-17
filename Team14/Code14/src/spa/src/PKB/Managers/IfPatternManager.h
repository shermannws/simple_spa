#pragma once

#include <cassert>

#include "PKB/Managers/ConditionPatternManager.h"
#include "PKB/PatternStore/IfPatternStore.h"

/**
 * @class IfPatternManager is responsible for storing and retrieving the If statement patterns
 * @brief Manages the If statement patterns
 */
class IfPatternManager : public ConditionPatternManager<IfPatternStore> {
public:
    /**
     * @brief Constructs a IfPatternManager object
     * @return A IfPatternManager object
     */
    IfPatternManager();

    /**
     * @brief Stores the If statement pattern
     * @param stmt The If statement
     * @param vars The vector of control variable in the If statement
     */
    void storeIfPattern(std::shared_ptr<Statement> stmt, std::shared_ptr<std::vector<std::shared_ptr<Variable>>> vars);
};