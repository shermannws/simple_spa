#pragma once

#include <memory>

#include "PKB/Managers/PkbReaderManager.h"
#include "PkbTypes.h"

/**
 * @brief The facade abstract class for reading from the PKB
 */
class PkbReader {
public:
    /**
      * @brief Returns all the variables in the SIMPLE program.
      * @return A vector of variables.
      */
    virtual std::vector<Entity> getAllVariables() const = 0;

    /**
     * @brief Returns all the constants in the SIMPLE program.
     * @return A vector of constants.
     */
    virtual std::vector<Entity> getAllConstants() const = 0;

    /**
     * @brief Returns all the procedures in the SIMPLE program.
     * @return A vector of procedures.
     */
    virtual std::vector<Entity> getAllProcedures() const = 0;

    /**
     * @brief Returns all the statements in the SIMPLE program.
     * @return A vector of statements.
     */
    virtual std::vector<Entity> getAllStatements() const = 0;

    /**
     * @brief Returns all the read statements in the SIMPLE program.
     * @return A vector of read statements.
     */
    virtual std::vector<Entity> getAllRead() const = 0;

    /**
     * @brief Returns all the print statements in the SIMPLE program.
     * @return A vector of print statements.
     */
    virtual std::vector<Entity> getAllPrint() const = 0;

    /**
     * @brief Returns all the while statements in the SIMPLE program.
     * @return A vector of while statements.
     */
    virtual std::vector<Entity> getAllWhile() const = 0;

    /**
     * @brief Returns all the if statements in the SIMPLE program.
     * @return A vector of if statements.
     */
    virtual std::vector<Entity> getAllIf() const = 0;

    /**
     * Returns a vector of Statement, Variable pair where the statement uses the variable. Retrieves the relationship where the statement is of the given type
     * @param type The type of the statement
     * @return A vector of Statement, Variable pair stored in a vector
     */
    virtual std::vector<std::vector<Entity>> getUsesStmtPair(StatementType type) const = 0;

    /**
     * Returns a vector of statements of StatementType type which uses the given variable
     * @param type The type of the statement to be retrieved
     * @param var The variable that is used by the statements
     * @return A vector of statements
    */
    virtual std::vector<Entity> getUsesTypeIdent(StatementType type, Variable& var) const = 0;

    /**
     * Returns a vector of statements of the given statement type which uses any variable
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    virtual std::vector<Entity> getUsesStmt(StatementType type) const = 0;

    /**
     * Returns a vector of variables which is used by the given statement
     * @param stmt The statement that uses the variables
     * @return A vector of variables
     */
    virtual std::vector<Entity> getUsesVar(Statement& stmt) const = 0;

    /**
     * Returns a boolean value indicating if the given statement uses the given variable
     * @param stmt The statement that uses the variable
     * @param var The variable that is used by the statement
     * @return True if the statement uses the variable, else false
     */
    virtual bool isStmtUsesVar(Statement& stmt, Variable& var) const = 0;

    /**
     * Returns a boolean value indicating if the given statement uses any variable
     * @param stmt The statement that uses the variable
     * @return True if the statement uses any variable, else false
     */
    virtual bool hasUses(Statement& stmt) const = 0;

    /**
     * Returns a vector of Statement, Statement pair where the first statement follows the second statement DIRECTLY. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return A vector of Statement, Statement pair stored in a vector
     */
    virtual std::vector<std::vector<Entity>> getFollowsPair(StatementType formerType, StatementType latterType) const = 0;

    /**
     * Returns a vector of Statement, Statement pair where the first statement follows the second statement DIRECTLY or INDIRECTLY. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return A vector of Statement, Statement pair stored in a vector
     */
    virtual std::vector<std::vector<Entity>> getFollowsStarPair(StatementType formerType, StatementType latterType) const = 0;

    /**
     * Returns a vector of statements of the given statement type which is followed by the given statement DIRECTLY i.e. the given statement is directly after the statement in the vector
     * @param type The type of the statement to be retrieved
     * @param statement The statement that succeeds the statements to be retrieved
     * @return A vector of statements
     */
    virtual std::vector<Entity> getFollowsTypeStmt(StatementType type, Statement& statement) const = 0;

    /**
     * Returns a vector of statements of the given statement type which is followed by the given statement DIRECTLY or INDIRECTLY i.e. the given statement is directly or indirectly after the statement in the vector
     * @param type The type of the statement to be retrieved
     * @param statement The statement that succeeds the statements to be retrieved
     * @return A vector of statements
     */
    virtual std::vector<Entity> getFollowsStarTypeStmt(StatementType type, Statement& statement) const = 0;

    /**
     * Returns a vector of statements of the given statement type which is followed by any statement i.e. there exist a statement after the statement in the vector
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    virtual std::vector<Entity> getFollowsTypeWildcard(StatementType type) const = 0;

    /**
     * Returns a vector of statements of the given statement type which is followed by any statement i.e. there exist a statement after the statement in the vector
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    virtual std::vector<Entity> getFollowsStarTypeWildcard(StatementType type) const = 0;

    /**
     * Returns a vector of statements of the given statement type which follows the given statement DIRECTLY i.e. the given statement is directly before the statement in the vector
     * @param statement The statement that precedes the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    virtual std::vector<Entity> getFollowsStmtType(Statement& statement, StatementType type) const = 0;

    /**
     * Returns a vector of statements of the given statement type which follows the given statement DIRECTLY or INDIRECTLY i.e. the given statement is directly or indirectly before the statement in the vector
     * @param statement The statement that precedes the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    virtual std::vector<Entity> getFollowsStarStmtType(Statement& statement, StatementType type) const = 0;

    /**
     * Returns a vector of statements of the given statement type which follows any statement i.e. there exist a statement before the statement in the vector
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    virtual std::vector<Entity> getFollowsWildcardType(StatementType type) const = 0;

    /**
     * Returns a vector of statements of the given statement type which follows any statement i.e. there exist a statement before the statement in the vector
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    virtual std::vector<Entity> getFollowsStarWildcardType(StatementType type) const = 0;

    /**
     * Returns true if statement1 DIRECTLY precedes statement2, false otherwise
     * @param statement1 The preceding statement
     * @param statement2 The succeeding statement
     * @return True if statement1 directly precedes statement2, false otherwise
     */
    virtual bool isFollows(Statement& statement1, Statement& statement2) const = 0;

    /**
     * Returns true if statement1 DIRECTLY or INDIRECTLY precedes statement2, false otherwise
     * @param statement1 The preceding statement
     * @param statement2 The succeeding statement
     * @return True if statement1 directly or indirectly precedes statement2, false otherwise
     */
    virtual bool isFollowsStar(Statement& statement1, Statement& statement2) const = 0;

    /**
     * Returns true if there exists a follows relationship in the PKB, false otherwise
     * @return True if there exists a follows relationship in the PKB, false otherwise
     */
    virtual bool hasFollows() const = 0;

    /**
     * Returns true if there exists a follows star relationship in the PKB, false otherwise
     * @return True if there exists a follows star relationship in the PKB, false otherwise
     */
    virtual bool hasFollowsStar() const = 0;

    /**
     * Returns true if there exists a statement that succeeds the given statement, false otherwise i.e. there is a statement behind the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that succeeds the given statement, false otherwise
     */
    virtual bool hasLatterStmt(Statement& statement) const = 0;

    /**
     * Returns true if there exists a statement that precedes the given statement, false otherwise i.e. there is a statement in front of the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that precedes the given statement, false otherwise
     */
    virtual bool hasFormerStmt(Statement& statement) const = 0;

    /**
     * Returns true if there exists a statement that succeeds the given statement, false otherwise i.e. there is a statement behind the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that succeeds the given statement, false otherwise
     */
    virtual bool hasLatterStarStmt(Statement& statement) const = 0;

    /**
     * Returns true if there exists a statement that precedes the given statement, false otherwise i.e. there is a statement in front of the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that precedes the given statement, false otherwise
     */
    virtual bool hasFormerStarStmt(Statement& statement) const = 0;

    /**
     * Returns a vector of Statement, Variable pair where the statement modifies the variable. Retrieves the relationship where the statement is of the given type
     * @param type The type of the statement
     * @return A vector of Statement, Variable pair stored in a vector
     */
    virtual std::vector<std::vector<Entity>> getModifiesStmtPair(StatementType type) const = 0;

    /**
     * Returns a vector of statements of StatementType type which modifies the given variable
     * @param type The type of the statement to be retrieved
     * @param var The variable that is modified by the statements
     * @return A vector of statements
     */
    virtual std::vector<Entity> getModifiesTypeIdent(StatementType type, Variable& var) const = 0;

    /**
     * Returns a vector of statements of the given statement type which modifies any variable
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    virtual std::vector<Entity> getModifiesStmt(StatementType type) const = 0;

    /**
     * Returns a vector of variables which is modified by the given statement
     * @param stmt The statement that modifies the variables
     * @return A vector of variables
     * @note The vector will only contain one variable
     */
    virtual std::vector<Entity> getModifiesVar(Statement& stmt) const = 0;

    /**
     * Returns a boolean value indicating if the given statement modifies the given variable
     * @param stmt The statement that modifies the variable
     * @param var The variable that is modified by the statement
     * @return A boolean value indicating if the statement modifies the variable
     */
    virtual bool isStmtModifiesVar(Statement& stmt, Variable& var) const = 0;

    /**
     * Returns a boolean value indicating if the given statement modifies any variable
     * @param stmt The statement to be checked
     * @return A boolean value indicating if the statement modifies any variable
     */
    virtual bool hasModifies(Statement& stmt) const = 0;

    /**
     * Returns a vector of Statements from all the Assignment objects in the store. Represents all the Statements that are assignments
     * @return A vector of all the Statement objects
     * @note Used for `pattern a (_,_)`
     */
    virtual std::vector<Entity> getAllAssign() const = 0;

    /**
     * Returns a vector of Statement objects from Assignment objects in the store with Expressions that match the given pattern. Represents all the statements that are assignments with Expressions that match the given pattern
     * @param rhs The pattern to be matched against the Expressions
     * @param hasRhsWildCard A boolean value indicating if the pattern has a wildcard
     * @return A vector of Statement objects
     * @note Used for `pattern a (_, "x")`
     */
    virtual std::vector<Entity> getAssignStmtsByRhs(Expression& rhs, bool hasRhsWildCard) const = 0;

    /**
     * Returns a vector of vectors containing Statement and Variable pairs from all the Assignment objects in the store
     * @return A vector of vectors containing Statement and Variable pairs
     * @note Used for `pattern a (v, _)`
     */
    virtual std::vector<std::vector<Entity>> getAllAssignStmtVarPair() const = 0;

    /**
     * Returns a vector of vectors containing Statement and Variable pairs from the Assignment objects in the store with the Expression matching the given pattern
     * @param rhs The pattern to be matched against the Expressions
     * @param hasWildCard A boolean value indicating if the pattern has a wildcard
     * @return A vector of vectors containing Statement and Variable pairs
     * @note Used for `pattern a (v, "x")`
     */
    virtual std::vector<std::vector<Entity>> getAssignStmtsVarPairByRhs(Expression& rhs, bool hasWildCard) const = 0;

    /**
     * Returns a vector of Statement objects from Assignment objects in the store where the Variable that is assigned matches the given Variable.
     * @param lhs The Variable to be matched against
     * @return A vector of Statement objects
     * @note Used for `pattern a ("x", _)`
     */
    virtual std::vector<Entity> getAssignStmtsByLhs(Variable& lhs) const = 0;

    /**
     * Returns a vector of Statement objects from Assignment objects in the store where the Variable that is assigned matches the given Variable and the Expression matches the given pattern.
     * @param lhs The Variable to be matched against
     * @param rhs The pattern to be matched against the Expressions
     * @param hasRhsWildCard A boolean value indicating if the pattern has a wildcard
     * @return A vector of Statement objects
     * @note Used for `pattern a ("x", "x")`
     */
    virtual std::vector<Entity> getAssignStmtsByLhsRhs(Variable& lhs, Expression& rhs, bool hasRhsWildCard) const = 0;

    /**
     * Returns a vector of Statement, Statement pair where the first statement is the DIRECT parent of the second statement. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return A vector of Statement, Statement pair stored in a vector
     */
    virtual std::vector<std::vector<Entity>> getParentPair(StatementType formerType, StatementType latterType) const = 0;

    /**
     * Returns a vector of Statement, Statement pair where the first statement is the DIRECT or INDIRECT parent of the second statement. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return A vector of Statement, Statement pair stored in a vector
     */
    virtual std::vector<std::vector<Entity>> getParentStarPair(StatementType formerType, StatementType latterType) const = 0;

    /**
     * Returns a vector of statements of the given statement type which is the DIRECT parent of the given statement
     * @param type The type of the statement to be retrieved
     * @param statement The statement that is the direct child of the statements to be retrieved
     * @return A vector of statements
     */
    virtual std::vector<Entity> getParentTypeStmt(StatementType type, Statement& statement) const = 0;

    /**
     * Returns a vector of statements of the given statement type which is the DIRECT or INDIRECT parent of the given statement
     * @param type The type of the statement to be retrieved
     * @param statement The statement that is the direct or indirect child of the statements to be retrieved
     * @return A vector of statements
     */
    virtual std::vector<Entity> getParentStarTypeStmt(StatementType type, Statement& statement) const = 0;

    /**
     * Returns a vector of statements of the given statement type which is the direct parent of any statement
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    virtual std::vector<Entity> getParentTypeWildcard(StatementType type) const = 0;

    /**
     * Returns a vector of statements of the given statement type which is the direct or indirect parent of any statement
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    virtual std::vector<Entity> getParentStarTypeWildcard(StatementType type) const = 0;

    /**
     * Returns a vector of statements of the given statement type which is the DIRECT child of the given statement
     * @param statement The statement that is the direct parent of the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    virtual std::vector<Entity> getParentStmtType(Statement& statement, StatementType type) const = 0;

    /**
     * Returns a vector of statements of the given statement type which is the DIRECT or INDIRECT child of the given statement
     * @param statement The statement that is the direct or indirect parent of the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    virtual std::vector<Entity> getParentStarStmtType(Statement& statement, StatementType type) const = 0;

    /**
     * Returns a vector of statements of the given statement type which is the direct child of any statement
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    virtual std::vector<Entity> getParentWildcardType(StatementType type) const = 0;

    /**
     * Returns a vector of statements of the given statement type which is the direct or indirect child of any statement
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    virtual std::vector<Entity> getParentStarWildcardType(StatementType type) const = 0;

    /**
     * Returns a boolean value indicating if the first statement is the DIRECT parent of the second statement
     * @param statement1 The parent statement
     * @param statement2 The child statement
     * @return True if the first statement is the direct parent of the second statement, false otherwise
     */
    virtual bool isParent(Statement& statement1, Statement& statement2) const = 0;

    /**
     * Returns a boolean value indicating if the first statement is the DIRECT or INDIRECT parent of the second statement
     * @param statement1 The parent statement
     * @param statement2 The child statement
     * @return True if the first statement is the direct or indirect parent of the second statement, false otherwise
     */
    virtual bool isParentStar(Statement& statement1, Statement& statement2) const = 0;

    /**
     * Returns a boolean value indicating if there exists a Parent relationship
     * @return True if there exists a Parent relationship, false otherwise
     */
    virtual bool hasParent() const = 0;

    /**
     * Returns a boolean value indicating if there exists a Parent Star relationship
     * @return True if there exists a Parent relationship, false otherwise
     */
    virtual bool hasParentStar() const = 0;

    /**
     * Returns a boolean value indicating if the given statement is the direct child of any statement
     * @param statement The statement to be checked
     * @return True if the given statement is the child of any statement, false otherwise
     */
    virtual bool hasParentStmt(Statement& statement) const = 0;

    /**
     * Returns a boolean value indicating if the given statement is the direct or indirect child of any statement
     * @param statement The statement to be checked
     * @return True if the given statement is the child of any statement, false otherwise
     */
    virtual bool hasParentStarStmt(Statement& statement) const = 0;

    /**
     * Returns a boolean value indicating if the given statement is the direct parent of any statement
     * @param statement The statement to be checked
     * @return True if the given statement is the parent of any statement, false otherwise
     */
    virtual bool hasChildStmt(Statement& statement) const = 0;

    /**
     * Returns a boolean value indicating if the given statement is the direct or indirect parent of any statement
     * @param statement The statement to be checked
     * @return True if the given statement is the parent of any statement, false otherwise
     */
    virtual bool hasChildStarStmt(Statement& statement) const = 0;
};