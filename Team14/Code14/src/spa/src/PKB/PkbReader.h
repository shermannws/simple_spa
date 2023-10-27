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
     * @return An unordered_set of variables.
     */
    virtual std::unordered_set<Entity> getAllVariables() const = 0;

    /**
     * @brief Returns all the constants in the SIMPLE program.
     * @return An unordered_set of constants.
     */
    virtual std::unordered_set<Entity> getAllConstants() const = 0;

    /**
     * @brief Returns all the procedures in the SIMPLE program.
     * @return An unordered_set of procedures.
     */
    virtual std::unordered_set<Entity> getAllProcedures() const = 0;

    /**
     * @brief Returns all the statements in the SIMPLE program.
     * @return An unordered_set of statements.
     */
    virtual std::unordered_set<Entity> getAllStatements() const = 0;

    /**
     * @brief Returns all the read statements in the SIMPLE program.
     * @return An unordered_set of read statements.
     */
    virtual std::unordered_set<Entity> getAllRead() const = 0;

    /**
     * @brief Returns all the print statements in the SIMPLE program.
     * @return An unordered_set of print statements.
     */
    virtual std::unordered_set<Entity> getAllPrint() const = 0;

    /**
     * @brief Returns all the while statements in the SIMPLE program.
     * @return An unordered_set of while statements.
     */
    virtual std::unordered_set<Entity> getAllWhile() const = 0;

    /**
     * @brief Returns all the if statements in the SIMPLE program.
     * @return An unordered_set of if statements.
     */
    virtual std::unordered_set<Entity> getAllIf() const = 0;

    /**
     * @brief Returns all the call statements in the SIMPLE program.
     * @return An unordered_set of call statements.
     */
    virtual std::unordered_set<Entity> getAllCall() const = 0;

    /**
     * Returns an unordered_set of Statement, Variable pair where the statement uses the variable. Retrieves the
     * relationship where the statement is of the given type
     * @param type The type of the statement
     * @return An unordered_set of Statement, Variable pair stored in a vector
     */
    virtual std::unordered_set<std::vector<Entity>> getUsesStmtPair(StatementType type) const = 0;

    /**
     * Returns an unordered_set of Procedure, Variable pair where the procedure uses the variable.
     * @return An unordered_set of Procedure, Variable pair stored in a vector
     */
    virtual std::unordered_set<std::vector<Entity>> getUsesProcPair() const = 0;

    /**
     * Returns an unordered_set of statements of StatementType type which uses the given variable
     * @param type The type of the statement to be retrieved
     * @param var The variable that is used by the statements
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getUsesTypeIdent(StatementType type, Variable &var) const = 0;

    /**
     * Returns an unordered_set of procedures which uses the given variable
     * @param var The variable that is used by the statements
     * @return An unordered_set of procedures
     */
    virtual std::unordered_set<Entity> getUsesProcIdent(Variable &var) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which uses any variable
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getUsesStmt(StatementType type) const = 0;

    /**
     * Returns an unordered_set of variables which is used by the given statement
     * @param stmt The statement that uses the variables
     * @return An unordered_set of variables
     */
    virtual std::unordered_set<Entity> getUsesVar(Statement &stmt) const = 0;

    /**
     * Returns an unordered_set of variables which is used by the given procedure
     * @param proc The procedure that uses the variables
     * @return An unordered_set of variables
     */
    virtual std::unordered_set<Entity> getUsesVar(Procedure &proc) const = 0;

    /**
     * Returns an unordered_set of procedures which uses any variable
     * @return An unordered_set of procedures
     */
    virtual std::unordered_set<Entity> getUsesProc() const = 0;

    /**
     * Returns a boolean value indicating if the given statement uses the given variable
     * @param stmt The statement that uses the variable
     * @param var The variable that is used by the statement
     * @return True if the statement uses the variable, else false
     */
    virtual bool isStmtUsesVar(Statement &stmt, Variable &var) const = 0;

    /**
     * Returns a boolean value indicating if the given procedure uses the given variable
     * @param proc The procedure that uses the variable
     * @param var The variable that is used by the procedure
     * @return True if the procedure uses the variable, else false
     */
    virtual bool isProcUsesVar(Procedure &proc, Variable &var) const = 0;

    /**
     * Returns a boolean value indicating if the given statement uses any variable
     * @param stmt The statement to check
     * @return True if the statement uses any variable, else false
     */
    virtual bool hasUses(Statement &stmt) const = 0;

    /**
     * Returns a boolean value indicating if the given procedure uses any variable
     * @param proc The procedure to check
     * @return True if the statement uses any variable, else false
     */
    virtual bool hasUses(Procedure &proc) const = 0;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement follows the second statement
     * DIRECTLY. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return An unordered_set of Statement, Statement pair stored in a vector
     */
    virtual std::unordered_set<std::vector<Entity>> getFollowsPair(StatementType formerType,
                                                                   StatementType latterType) const = 0;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement follows the second statement
     * DIRECTLY or INDIRECTLY. Retrieves the relationship where the first and second statement are both of the given
     * type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return An unordered_set of Statement, Statement pair stored in a vector
     */
    virtual std::unordered_set<std::vector<Entity>> getFollowsStarPair(StatementType formerType,
                                                                       StatementType latterType) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is followed by the given statement
     * DIRECTLY i.e. the given statement is directly after the statement in the set
     * @param type The type of the statement to be retrieved
     * @param statement The statement that succeeds the statements to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getFollowsTypeStmt(StatementType type, Statement &statement) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is followed by the given statement
     * DIRECTLY or INDIRECTLY i.e. the given statement is directly or indirectly after the statement in the set
     * @param type The type of the statement to be retrieved
     * @param statement The statement that succeeds the statements to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getFollowsStarTypeStmt(StatementType type, Statement &statement) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is followed by any statement i.e. there
     * exist a statement after the statement in the set
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getFollowsTypeWildcard(StatementType type) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is followed by any statement i.e. there
     * exist a statement after the statement in the set
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getFollowsStarTypeWildcard(StatementType type) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which follows the given statement DIRECTLY
     * i.e. the given statement is directly before the statement in the set
     * @param statement The statement that precedes the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getFollowsStmtType(Statement &statement, StatementType type) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which follows the given statement DIRECTLY or
     * INDIRECTLY i.e. the given statement is directly or indirectly before the statement in the set
     * @param statement The statement that precedes the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getFollowsStarStmtType(Statement &statement, StatementType type) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which follows any statement i.e. there exist a
     * statement before the statement in the set
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getFollowsWildcardType(StatementType type) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which follows any statement i.e. there exist a
     * statement before the statement in the set
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getFollowsStarWildcardType(StatementType type) const = 0;

    /**
     * Returns true if statement1 DIRECTLY precedes statement2, false otherwise
     * @param statement1 The preceding statement
     * @param statement2 The succeeding statement
     * @return True if statement1 directly precedes statement2, false otherwise
     */
    virtual bool isFollows(Statement &statement1, Statement &statement2) const = 0;

    /**
     * Returns true if statement1 DIRECTLY or INDIRECTLY precedes statement2, false otherwise
     * @param statement1 The preceding statement
     * @param statement2 The succeeding statement
     * @return True if statement1 directly or indirectly precedes statement2, false otherwise
     */
    virtual bool isFollowsStar(Statement &statement1, Statement &statement2) const = 0;

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
     * Returns true if there exists a statement that succeeds the given statement, false otherwise i.e. there is a
     * statement behind the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that succeeds the given statement, false otherwise
     */
    virtual bool hasLatterStmt(Statement &statement) const = 0;

    /**
     * Returns true if there exists a statement that precedes the given statement, false otherwise i.e. there is a
     * statement in front of the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that precedes the given statement, false otherwise
     */
    virtual bool hasFormerStmt(Statement &statement) const = 0;

    /**
     * Returns true if there exists a statement that succeeds the given statement, false otherwise i.e. there is a
     * statement behind the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that succeeds the given statement, false otherwise
     */
    virtual bool hasLatterStarStmt(Statement &statement) const = 0;

    /**
     * Returns true if there exists a statement that precedes the given statement, false otherwise i.e. there is a
     * statement in front of the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that precedes the given statement, false otherwise
     */
    virtual bool hasFormerStarStmt(Statement &statement) const = 0;

    /**
     * Returns an unordered_set of Statement, Variable pair where the statement modifies the variable. Retrieves the
     * relationship where the statement is of the given type
     * @param type The type of the statement
     * @return An unordered_set of Statement, Variable pair stored in a vector
     */
    virtual std::unordered_set<std::vector<Entity>> getModifiesStmtPair(StatementType type) const = 0;

    /**
     * Returns an unordered_set of Procedure, Variable pair where the procedure modifies the variable.
     * @return An unordered_set of Procedure, Variable pair stored in a vector
     */
    virtual std::unordered_set<std::vector<Entity>> getModifiesProcPair() const = 0;

    /**
     * Returns an unordered_set of statements of StatementType type which modifies the given variable
     * @param type The type of the statement to be retrieved
     * @param var The variable that is modified by the statements
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getModifiesTypeIdent(StatementType type, Variable &var) const = 0;

    /**
     * Returns an unordered_set of procedures which modifies the given variable
     * @param var The variable that is modified by the procedure
     * @return An unordered_set of procedures
     */
    virtual std::unordered_set<Entity> getModifiesProcIdent(Variable &var) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which modifies any variable
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getModifiesStmt(StatementType type) const = 0;

    /**
     * Returns an unordered_set of procedures which modifies any variable
     * @return An unordered_set of procedures
     */
    virtual std::unordered_set<Entity> getModifiesProc() const = 0;

    /**
     * Returns an unordered_set of variables which is modified by the given statement
     * @param stmt The statement that modifies the variables
     * @return An unordered_set of variables
     */
    virtual std::unordered_set<Entity> getModifiesVar(Statement &stmt) const = 0;

    /**
     * Returns an unordered_set of variables which is modified by the given procedure
     * @param proc The procedure that modifies the variables
     * @return An unordered_set of variables
     */
    virtual std::unordered_set<Entity> getModifiesVar(Procedure &proc) const = 0;

    /**
     * Returns a boolean value indicating if the given statement modifies the given variable
     * @param stmt The statement that modifies the variable
     * @param var The variable that is modified by the statement
     * @return A boolean value indicating if the statement modifies the variable
     */
    virtual bool isStmtModifiesVar(Statement &stmt, Variable &var) const = 0;

    /**
     * Returns a boolean value indicating if the given procedure modifies the given variable
     * @param proc The procedure that modifies the variable
     * @param var The variable that is modified by the procedure
     * @return A boolean value indicating if the procedure modifies the variable
     */
    virtual bool isProcModifiesVar(Procedure &proc, Variable &var) const = 0;

    /**
     * Returns a boolean value indicating if the given statement modifies any variable
     * @param stmt The statement to be checked
     * @return A boolean value indicating if the statement modifies any variable
     */
    virtual bool hasModifies(Statement &stmt) const = 0;

    /**
     * Returns a boolean value indicating if the given procedure modifies any variable
     * @param stmt The procedure to be checked
     * @return A boolean value indicating if the procedure modifies any variable
     */
    virtual bool hasModifies(Procedure &proc) const = 0;

    /**
     * Returns an unordered_set of Statements from all the Assignment objects in the store. Represents all the
     * Statements that are assignments
     * @return An unordered_set of all the Statement objects
     * @note Used for `pattern a (_,_)`
     */
    virtual std::unordered_set<Entity> getAllAssign() const = 0;

    /**
     * Returns an unordered_set of Statement objects from Assignment objects in the store with Expressions that match
     * the given pattern. Represents all the statements that are assignments with Expressions that match the given
     * pattern
     * @param rhs The pattern to be matched against the Expressions
     * @param hasRhsWildCard A boolean value indicating if the pattern has a wildcard
     * @return An unordered_set of Statement objects
     * @note Used for `pattern a (_, "x")`
     */
    virtual std::unordered_set<Entity> getAssignStmtsByRhs(Expression &rhs, bool hasRhsWildCard) const = 0;

    /**
     * Returns an unordered_set of vectors containing Statement and Variable pairs from all the Assignment objects in
     * the store
     * @return An unordered_set of vectors containing Statement and Variable pairs
     * @note Used for `pattern a (v, _)`
     */
    virtual std::unordered_set<std::vector<Entity>> getAllAssignStmtVarPair() const = 0;

    /**
     * Returns an unordered_set of vectors containing Statement and Variable pairs from the Assignment objects in the
     * store with the Expression matching the given pattern
     * @param rhs The pattern to be matched against the Expressions
     * @param hasWildCard A boolean value indicating if the pattern has a wildcard
     * @return An unordered_set of vectors containing Statement and Variable pairs
     * @note Used for `pattern a (v, "x")`
     */
    virtual std::unordered_set<std::vector<Entity>> getAssignStmtsVarPairByRhs(Expression &rhs,
                                                                               bool hasWildCard) const = 0;

    /**
     * Returns an unordered_set of Statement objects from Assignment objects in the store where the Variable that is
     * assigned matches the given Variable.
     * @param lhs The Variable to be matched against
     * @return An unordered_set of Statement objects
     * @note Used for `pattern a ("x", _)`
     */
    virtual std::unordered_set<Entity> getAssignStmtsByLhs(Variable &lhs) const = 0;

    /**
     * Returns an unordered_set of Statement objects from Assignment objects in the store where the Variable that is
     * assigned matches the given Variable and the Expression matches the given pattern.
     * @param lhs The Variable to be matched against
     * @param rhs The pattern to be matched against the Expressions
     * @param hasRhsWildCard A boolean value indicating if the pattern has a wildcard
     * @return An unordered_set of Statement objects
     * @note Used for `pattern a ("x", "x")`
     */
    virtual std::unordered_set<Entity> getAssignStmtsByLhsRhs(Variable &lhs, Expression &rhs,
                                                              bool hasRhsWildCard) const = 0;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement is the DIRECT parent of the
     * second statement. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return An unordered_set of Statement, Statement pair stored in a vector
     */
    virtual std::unordered_set<std::vector<Entity>> getParentPair(StatementType formerType,
                                                                  StatementType latterType) const = 0;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement is the DIRECT or INDIRECT parent
     * of the second statement. Retrieves the relationship where the first and second statement are both of the given
     * type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return An unordered_set of Statement, Statement pair stored in a vector
     */
    virtual std::unordered_set<std::vector<Entity>> getParentStarPair(StatementType formerType,
                                                                      StatementType latterType) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is the DIRECT parent of the given
     * statement
     * @param type The type of the statement to be retrieved
     * @param statement The statement that is the direct child of the statements to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getParentTypeStmt(StatementType type, Statement &statement) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is the DIRECT or INDIRECT parent of the
     * given statement
     * @param type The type of the statement to be retrieved
     * @param statement The statement that is the direct or indirect child of the statements to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getParentStarTypeStmt(StatementType type, Statement &statement) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is the direct parent of any statement
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getParentTypeWildcard(StatementType type) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is the direct or indirect parent of any
     * statement
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getParentStarTypeWildcard(StatementType type) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is the DIRECT child of the given
     * statement
     * @param statement The statement that is the direct parent of the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getParentStmtType(Statement &statement, StatementType type) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is the DIRECT or INDIRECT child of the
     * given statement
     * @param statement The statement that is the direct or indirect parent of the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getParentStarStmtType(Statement &statement, StatementType type) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is the direct child of any statement
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getParentWildcardType(StatementType type) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is the direct or indirect child of any
     * statement
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getParentStarWildcardType(StatementType type) const = 0;

    /**
     * Returns a boolean value indicating if the first statement is the DIRECT parent of the second statement
     * @param statement1 The parent statement
     * @param statement2 The child statement
     * @return True if the first statement is the direct parent of the second statement, false otherwise
     */
    virtual bool isParent(Statement &statement1, Statement &statement2) const = 0;

    /**
     * Returns a boolean value indicating if the first statement is the DIRECT or INDIRECT parent of the second
     * statement
     * @param statement1 The parent statement
     * @param statement2 The child statement
     * @return True if the first statement is the direct or indirect parent of the second statement, false otherwise
     */
    virtual bool isParentStar(Statement &statement1, Statement &statement2) const = 0;

    /**
     * Returns a boolean value indicating if there exists a Parent relationship
     * @return True if there exists a Parent relationship, false otherwise
     */
    virtual bool hasParent() const = 0;

    /**
     * Returns a boolean value indicating if there exists a Parent Star relationship
     * @return True if there exists a Parent Star relationship, false otherwise
     */
    virtual bool hasParentStar() const = 0;

    /**
     * Returns a boolean value indicating if the given statement is the direct child of any statement
     * @param statement The statement to be checked
     * @return True if the given statement is the child of any statement, false otherwise
     */
    virtual bool hasParentStmt(Statement &statement) const = 0;

    /**
     * Returns a boolean value indicating if the given statement is the direct or indirect child of any statement
     * @param statement The statement to be checked
     * @return True if the given statement is the child of any statement, false otherwise
     */
    virtual bool hasParentStarStmt(Statement &statement) const = 0;

    /**
     * Returns a boolean value indicating if the given statement is the direct parent of any statement
     * @param statement The statement to be checked
     * @return True if the given statement is the parent of any statement, false otherwise
     */
    virtual bool hasChildStmt(Statement &statement) const = 0;

    /**
     * Returns a boolean value indicating if the given statement is the direct or indirect parent of any statement
     * @param statement The statement to be checked
     * @return True if the given statement is the parent of any statement, false otherwise
     */
    virtual bool hasChildStarStmt(Statement &statement) const = 0;

    /**
     * Returns a boolean value indicating if there exists a Calls relationship
     * @return True if there exists a Calls relationship, false otherwise
     */
    virtual bool hasCalls() const = 0;

    /**
     * Returns a boolean value indicating if there exists a Calls Star relationship
     * @return True if there exists a Calls Star relationship, false otherwise
     */
    virtual bool hasCallsStar() const = 0;

    /**
     * Returns a boolean value indicating if the given procedure is called directly by any other procedure
     * @param proc The procedure to be checked
     * @return True if the given procedure is called directly by any other procedure, false otherwise
     */
    virtual bool isCallee(Procedure &proc) const = 0;

    /**
     * Returns a boolean value indicating if the given procedure is called directly or indirectly by any other procedure
     * @param proc The procedure to be checked
     * @return True if the given procedure is called directly or indirectly by any other procedure, false otherwise
     */
    virtual bool isCalleeStar(Procedure &proc) const = 0;

    /**
     * Returns a boolean value indicating if the given procedure calls any other procedure directly
     * @param proc The procedure to be checked
     * @return True if the given procedure calls any other procedure directly, false otherwise
     */
    virtual bool isCaller(Procedure &proc) const = 0;

    /**
     * Returns a boolean value indicating if the given procedure calls any other procedure directly or indirectly
     * @param proc The procedure to be checked
     * @return True if the given procedure calls any other procedure directly or indirectly, false otherwise
     */
    virtual bool isCallerStar(Procedure &proc) const = 0;

    /**
     * Returns a boolean value indicating if the first procedure calls the second procedure directly
     * @param caller The calling procedure
     * @param callee The called procedure
     * @return True if the first procedure calls the second procedure directly, false otherwise
     */
    virtual bool isCalls(Procedure &caller, Procedure &callee) const = 0;

    /**
     * Returns a boolean value indicating if the first procedure calls the second procedure directly or indirectly
     * @param caller The calling procedure
     * @param callee The called procedure
     * @return True if the first procedure calls the second procedure directly or indirectly, false otherwise
     */
    virtual bool isCallsStar(Procedure &caller, Procedure &callee) const = 0;

    /**
     * Returns an unordered_set of procedures which is called directly by any other procedure
     * @return An unordered_set of procedures
     */
    virtual std::unordered_set<Entity> getCallees() const = 0;

    /**
     * Returns an unordered_set of procedures which is called directly or indirectly by any other procedure
     * @return An unordered_set of procedures
     */
    virtual std::unordered_set<Entity> getCalleesStar() const = 0;

    /**
     * Returns an unordered_set of procedures which calls any other procedure directly
     * @return An unordered_set of procedures
     */
    virtual std::unordered_set<Entity> getCallers() const = 0;

    /**
     * Returns an unordered_set of procedures which calls any other procedure directly or indirectly
     * @return An unordered_set of procedures
     */
    virtual std::unordered_set<Entity> getCallersStar() const = 0;

    /**
     * Returns an unordered_set of Procedure, Procedure pair where the first procedure calls the second procedure
     * DIRECTLY
     * @return An unordered_set of Procedure, Procedure pair stored in a vector
     */
    virtual std::unordered_set<std::vector<Entity>> getCallsPair() const = 0;

    /**
     * Returns an unordered_set of Procedure, Procedure pair where the first procedure calls the second procedure
     * DIRECTLY or INDIRECTLY
     * @return An unordered_set of Procedure, Procedure pair stored in a vector
     */
    virtual std::unordered_set<std::vector<Entity>> getCallsStarPair() const = 0;

    /**
     * Returns an unordered_set of procedures which calls the given procedure DIRECTLY
     * @param callee The procedure that is called by the procedures to be retrieved
     * @return An unordered_set of procedures
     */
    virtual std::unordered_set<Entity> getCallers(Procedure &callee) const = 0;

    /**
     * Returns an unordered_set of procedures which calls the given procedure DIRECTLY or INDIRECTLY
     * @param callee The procedure that is called by the procedures to be retrieved
     * @return An unordered_set of procedures
     */
    virtual std::unordered_set<Entity> getCallersStar(Procedure &callee) const = 0;

    /**
     * Returns an unordered_set of procedures which is called DIRECTLY by the given procedure
     * @param caller The procedure that calls the procedures to be retrieved
     * @return An unordered_set of procedures
     */
    virtual std::unordered_set<Entity> getCallees(Procedure &caller) const = 0;

    /**
     * Returns an unordered_set of procedures which is called DIRECTLY or INDIRECTLY by the given procedure
     * @param caller The procedure that calls the procedures to be retrieved
     * @return An unordered_set of procedures
     */
    virtual std::unordered_set<Entity> getCalleesStar(Procedure &caller) const = 0;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement is is executed IMMEDIATELY before
     * second statement. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return An unordered_set of Statement, Statement pair stored in a vector
     */
    virtual std::unordered_set<std::vector<Entity>> getNextPair(StatementType formerType,
                                                                StatementType latterType) const = 0;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement is executed before of the second
     * statement, either immediately or after some execution sequence. Retrieves the relationship where the first and
     * second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return An unordered_set of Statement, Statement pair stored in a vector
     */
    virtual std::unordered_set<std::vector<Entity>> getNextStarPair(StatementType formerType,
                                                                    StatementType latterType) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed again after it has been
     * executed
     * @param stmtType The type of statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getNextStarSameStmt(StatementType stmtType) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed IMMEDIATELY before the given
     * statement
     * @param type The type of the statement to be retrieved
     * @param statement The statement that executed IMMEDIATELY after the statements to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getNextTypeStmt(StatementType type, Statement &statement) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed before the given statement,
     * either immediately or after some execution sequence
     * @param type The type of the statement to be retrieved
     * @param statement The statement that is executed after the statements to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getNextStarTypeStmt(StatementType type, Statement &statement) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type that is executed IMMEDIATELY before any
     * statement
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getNextTypeWildcard(StatementType type) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed before any statement, either
     * immediately or after some execution sequence
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getNextStarTypeWildcard(StatementType type) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed IMMEDIATELY after the given
     * statement
     * @param statement The statement that is executed IMMEDIATELY before the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getNextStmtType(Statement &statement, StatementType type) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed after the given statement,
     * either immediately or after some execution sequence
     * @param statement The statement that is executed after the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getNextStarStmtType(Statement &statement, StatementType type) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed IMMEDIATELY after any
     * statement
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getNextWildcardType(StatementType type) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed after any statement, either
     * immediately or after some execution sequence
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getNextStarWildcardType(StatementType type) const = 0;

    /**
     * Returns a boolean value indicating if the first statement is executed IMMEDIATELY before the second statement
     * @param statement1 The parent statement
     * @param statement2 The child statement
     * @return True if the first statement is executed IMMEDIATELY before the second statement, false otherwise
     */
    virtual bool isNext(Statement &statement1, Statement &statement2) const = 0;

    /**
     * Returns a boolean value indicating if the first statement is executed before the second statement, either
     * immediately or after some execution sequence
     * @param statement1 The parent statement
     * @param statement2 The child statement
     * @return True if the first statement is executed before the second statement, false otherwise
     */
    virtual bool isNextStar(Statement &statement1, Statement &statement2) const = 0;

    /**
     * Returns a boolean value indicating if there exists a Next relationship
     * @return True if there exists a Next relationship, false otherwise
     */
    virtual bool hasNext() const = 0;

    /**
     * Returns a boolean value indicating if there exists a Next Star relationship
     * @return True if there exists a Next Star relationship, false otherwise
     */
    virtual bool hasNextStar() const = 0;

    /**
     * Returns a boolean value indicating if the given statement is executed IMMEDIATELY after any statement
     * @param statement The statement to be checked
     * @return True if the given statement is executed IMMEDIATELY after any statement, false otherwise
     */
    virtual bool hasBeforeStmt(Statement &statement) const = 0;

    /**
     * Returns a boolean value indicating if the given statement is executed after any statement, either immediately or
     * after some execution sequence
     * @param statement The statement to be checked
     * @return True if the given statement is executed after any statement, false otherwise
     */
    virtual bool hasBeforeStarStmt(Statement &statement) const = 0;

    /**
     * Returns a boolean value indicating if the given statement is executed IMMEDIATELY before any statement
     * @param statement The statement to be checked
     * @return True if the given statement is executed IMMEDIATELY before any statement, false otherwise
     */
    virtual bool hasAfterStmt(Statement &statement) const = 0;

    /**
     * Returns a boolean value indicating if the given statement is executed before any statement, either immediately or
     * after some execution sequence
     * @param statement The statement to be checked
     * @return True if the given statement is executed before any statement, false otherwise
     */
    virtual bool hasAfterStarStmt(Statement &statement) const = 0;

    /**
     * Returns an unordered_set of If Statements that has variables as control variables
     * @return An unordered_set of Statements
     */
    virtual std::unordered_set<Entity> getAllIfPatternStmts() const = 0;

    /**
     * Returns an unordered_set of If Statements with the given variable as a control variable
     * @param var The variable to be checked
     * @return An unordered_set of If Statements
     */
    virtual std::unordered_set<Entity> getIfStmtsByVar(Variable &var) const = 0;

    /**
     * Returns an unordered_set of vectors containing If Statement and Variable pairs where the variable is the control
     * variable of the If Statement
     * @return An unordered_set of vectors containing If Statement and Variable pairs
     */
    virtual std::unordered_set<std::vector<Entity>> getAllIfStmtVarPair() const = 0;

    /**
     * Returns an unordered_set of While Statements that has variables as control variables
     * @return An unordered_set of Statements
     */
    virtual std::unordered_set<Entity> getAllWhilePatternStmts() const = 0;

    /**
     * Returns an unordered_set of While Statements with the given variable as a control variable
     * @param var The variable to be checked
     * @return An unordered_set of While Statements
     */
    virtual std::unordered_set<Entity> getWhileStmtsByVar(Variable &var) const = 0;

    /**
     * Returns an unordered_set of vectors containing While Statement and Variable pairs where the variable is the
     * control variable of the While Statement
     * @return An unordered_set of vectors containing While Statement and Variable pairs
     */
    virtual std::unordered_set<std::vector<Entity>> getAllWhileStmtVarPair() const = 0;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement affects the second statement
     * DIRECTLY. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return An unordered_set of Statement, Statement pair stored in a vector
     */
    virtual std::unordered_set<std::vector<Entity>> getAffectsPair(StatementType formerType,
                                                                   StatementType latterType) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which affects the given statement DIRECTLY
     * @param type The type of the statement to be retrieved
     * @param statement The statement that succeeds the statements to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getAffectsTypeStmt(StatementType type, Statement &statement) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is affects any statement DIRECTLY
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getAffectsTypeWildcard(StatementType type) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is affected by the given statement
     * DIRECTLY
     * @param statement The statement that precedes the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getAffectsStmtType(Statement &statement, StatementType type) const = 0;

    /**
     * Returns an unordered_set of statements of the given statement type which is affected by any statement DIRECTLY
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    virtual std::unordered_set<Entity> getAffectsWildcardType(StatementType type) const = 0;

    /**
     * Returns true if statement1 DIRECTLY affects statement2, false otherwise
     * @param statement1 The preceding statement
     * @param statement2 The succeeding statement
     * @return True if statement1 directly affects statement2, false otherwise
     */
    virtual bool isAffects(Statement &statement1, Statement &statement2) const = 0;

    /**
     * Returns true if there exists a affects relationship in the PKB, false otherwise
     * @return True if there exists a affects relationship in the PKB, false otherwise
     */
    virtual bool hasAffects() const = 0;

    /**
     * Returns true if there exists a statement that is affected by the given statement, false otherwise i.e. there is a
     * statement in behind of the given statement that is affected by the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that is affected by the given statement, false otherwise
     */
    virtual bool hasAffectedStmt(Statement &statement) const = 0;

    /**
     * Returns true if there exists a statement that affects the given statement, false otherwise i.e. there is a
     * statement in front of the given statement that affects the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that affects the given statement, false otherwise
     */
    virtual bool hasAffectsStmt(Statement &statement) const = 0;
};