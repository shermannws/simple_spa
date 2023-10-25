#pragma once

#include <algorithm>
#include <cassert>
#include <memory>
#include <regex>
#include <string>
#include <utility>
#include <vector>

#include "Commons/AppConstants.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "PKB/Commons/Assignment.h"
#include "PKB/Managers/ManagerUtils.h"
#include "PKB/PatternStore/AssignPatternStore.h"
#include "PKB/PkbTypes.h"

/**
 * The AssignPatternManager class is used to store and retrieve Assignment entities
 * from the PKB. It is also used to query for Assignment entities that match a
 * given pattern.
 */
class AssignPatternManager {
private:
    /**
     * The AssignPatternStore that stores all the Assignment objects
     */
    std::shared_ptr<AssignPatternStore> assignmentStore;

    /**
     * Matches the expression with the pattern using regex. Returns true if the Expression matches the pattern, else
     * false. Uses regex_match hasWildCard is false look for exact match. Uses regex_search if hasWildCard is true to
     * look for partial match.
     * @param expression The expression to be matched
     * @param pattern The pattern to be matched against
     * @param hasWildCard A boolean value indicating if the pattern has a wildcard.
     * @return True if the Expression matches the pattern, else false.
     */
    bool matchExpression(Expression &expression, std::regex &pattern, bool hasWildCard) const;

    /**
     * Parses the pattern to a regex object. Handles the escaping of special characters.
     * @param pattern The pattern to be parsed
     * @return The regex object parsed from the pattern
     */
    std::regex parsePattern(Expression &pattern) const;

public:
    /**
     * Constructs an AssignPatternManager object
     * @return An AssignPatternManager object
     */
    AssignPatternManager();

    /**
     * Stores a new Assignment object into the PKB
     * @param assignment The Assignment object to be stored
     */
    void storeAssignPattern(std::shared_ptr<Assignment> assignment);

    /**
     * Returns an unordered_set of Statements from all the Assignment objects in the store. Represents all the
     * Statements that are assignments
     * @return An unordered_set of all the Statement objects
     * @note Used for `pattern a (_,_)`
     */
    std::unordered_set<Entity> getAllAssignStmts() const;

    /**
     * Returns an unordered_set of Statement objects from Assignment objects in the store with Expressions that match
     * the given pattern. Represents all the statements that are assignments with Expressions that match the given
     * pattern
     * @param rhs The pattern to be matched against the Expressions
     * @param hasRhsWildCard A boolean value indicating if the pattern has a wildcard
     * @return An unordered_set of Statement objects
     * @note Used for `pattern a (_, "x")`
     */
    std::unordered_set<Entity> getAssignStmtsByRhs(Expression &rhs, bool hasRhsWildCard) const;

    /**
     * Returns an unordered_set of vectors containing Statement and Variable pairs from all the Assignment objects in
     * the store
     * @return An unordered_set of vectors containing Statement and Variable pairs
     * @note Used for `pattern a (v, _)`
     */
    std::unordered_set<std::vector<Entity>> getAllAssignStmtVarPair() const;

    /**
     * Returns an unordered_set of vectors containing Statement and Variable pairs from the Assignment objects in the
     * store with the Expression matching the given pattern
     * @param rhs The pattern to be matched against the Expressions
     * @param hasWildCard A boolean value indicating if the pattern has a wildcard
     * @return An unordered_set of vectors containing Statement and Variable pairs
     * @note Used for `pattern a (v, "x")`
     */
    std::unordered_set<std::vector<Entity>> getAssignStmtsVarPairByRhs(Expression &rhs, bool hasWildCard) const;

    /**
     * Returns an unordered_set of Statement objects from Assignment objects in the store where the Variable that is
     * assigned matches the given Variable.
     * @param lhs The Variable to be matched against
     * @return An unordered_set of Statement objects
     * @note Used for `pattern a ("x", _)`
     */
    std::unordered_set<Entity> getAssignStmtsByLhs(Variable &lhs) const;

    /**
     * Returns an unordered_set of Statement objects from Assignment objects in the store where the Variable that is
     * assigned matches the given Variable and the Expression matches the given pattern.
     * @param lhs The Variable to be matched against
     * @param rhs The pattern to be matched against the Expressions
     * @param hasRhsWildCard A boolean value indicating if the pattern has a wildcard
     * @return An unordered_set of Statement objects
     * @note Used for `pattern a ("x", "x")`
     */
    std::unordered_set<Entity> getAssignStmtsByLhsRhs(Variable &lhs, Expression &rhs, bool hasRhsWildCard) const;
};
