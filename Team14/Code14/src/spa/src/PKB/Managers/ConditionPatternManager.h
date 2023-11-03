#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "PKB/Managers/ManagerUtils.h"
#include "PKB/PkbTypes.h"

/**
 * @class ConditionPatterManager is responsible for storing and retrieving the statement patterns
 * This class is a template class that is inherited by the Pattern Managers
 * @brief Manages the patterns
 */
template<typename S>
class ConditionPatternManager {
private:
    /**
     * @brief The pattern store
     */
    std::shared_ptr<S> patternStore;

protected:
    /**
     * Stores a new statement pattern into PKB via the Manager
     * @param statement The statement that is related to the variable
     * @param variable The variable that is related to the statement
     */
    void storePattern(std::shared_ptr<Statement> statement,
                      std::shared_ptr<std::vector<std::shared_ptr<Variable>>> variables);

public:
    /**
     * @brief Constructs a ConditionPatternManager object
     * @return A ConditionPatternManager object
     */
    ConditionPatternManager();

    /**
     * Returns an unordered_set of Statements in the store.
     * @return An unordered_set of all the Statement objects
     */
    EntitySet getAllStmts() const;

    /**
     * Returns an unordered_set of Statement objects the store with pattern using the given variable.
     * @param var The variable to be matched against
     * @return An unordered_set of Statement objects
     */
    EntitySet getStmtsByVar(Variable &var) const;

    /**
     * Returns an unordered_set of vectors containing all the Statement and Variable pairs in the store
     * @return An unordered_set of vectors containing Statement and Variable pairs
     */
    EntityPairSet getAllStmtVarPair() const;
};

#include "ConditionPatternManager.hpp"