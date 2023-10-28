#pragma once

#include <memory>

#include "PKB/Managers/PkbReaderManager.h"
#include "PkbReader.h"
#include "PkbTypes.h"

/**
 * @brief The facade class is responsible for reading from the PKB.
 */
class PkbConcreteReader : public PkbReader {
private:
    /**
     * @brief The reader manager
     */
    std::shared_ptr<PkbReaderManager> readerManager;

public:
    /**
     * @brief Constructs a PkbConcreteReader object.
     * @param readerManager The reader manager.
     */
    PkbConcreteReader(std::shared_ptr<PkbReaderManager> readerManager);

    /**
     * @brief Returns all the variables in the SIMPLE program.
     * @return An unordered set of variables.
     */
    std::unordered_set<Entity> getAllVariables() const override;

    /**
     * @brief Returns all the constants in the SIMPLE program.
     * @return An unordered set of constants.
     */
    std::unordered_set<Entity> getAllConstants() const override;

    /**
     * @brief Returns all the procedures in the SIMPLE program.
     * @return An unordered set of procedures.
     */
    std::unordered_set<Entity> getAllProcedures() const override;

    /**
     * @brief Returns all the statements in the SIMPLE program.
     * @return An unordered set of statements.
     */
    std::unordered_set<Entity> getAllStatements() const override;

    /**
     * @brief Returns all the read statements in the SIMPLE program.
     * @return An unordered set of read statements.
     */
    std::unordered_set<Entity> getAllRead() const override;

    /**
     * @brief Returns all the print statements in the SIMPLE program.
     * @return An unordered set of print statements.
     */
    std::unordered_set<Entity> getAllPrint() const override;

    /**
     * @brief Returns all the while statements in the SIMPLE program.
     * @return An unordered set of while statements.
     */
    std::unordered_set<Entity> getAllWhile() const override;

    /**
     * @brief Returns all the if statements in the SIMPLE program.
     * @return An unordered set of if statements.
     */
    std::unordered_set<Entity> getAllIf() const override;

    /**
     * @brief Returns all the call statements in the SIMPLE program.
     * @return An unordered set of call statements.
     */
    std::unordered_set<Entity> getAllCall() const override;

    /**
     * Returns an unordered_set of Statement, Variable pair where the statement uses the variable. Retrieves the
     * relationship where the statement is of the given type
     * @param type The type of the statement
     * @return An unordered set of Statement, Variable pair stored in a vector
     */
    std::unordered_set<std::vector<Entity>> getUsesStmtPair(StatementType type) const override;

    /**
     * Returns an unordered_set of Procedure, Variable pair where the procedure uses the variable.
     * @return An unordered set of Procedure, Variable pair stored in a vector
     */
    std::unordered_set<std::vector<Entity>> getUsesProcPair() const override;

    /**
     * Returns an unordered_set of statements of StatementType type which uses the given variable
     * @param type The type of the statement to be retrieved
     * @param var The variable that is used by the statements
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getUsesTypeIdent(StatementType type, Variable &var) const override;

    /**
     * Returns an unordered_set of procedures which uses the given variable
     * @param var The variable that is used by the statements
     * @return An unordered set of procedures
     */
    std::unordered_set<Entity> getUsesProcIdent(Variable &var) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which uses any variable
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getUsesStmt(StatementType type) const override;

    /**
     * Returns an unordered_set of procedures which uses any variable
     * @return An unordered set of procedures
     */
    std::unordered_set<Entity> getUsesProc() const override;

    /**
     * Returns an unordered_set of variables which is used by the given statement
     * @param stmt The statement that uses the variables
     * @return An unordered set of variables
     */
    std::unordered_set<Entity> getUsesVar(Statement &stmt) const override;

    /**
     * Returns an unordered_set of variables which is used by the given procedure
     * @param proc The procedure that uses the variables
     * @return An unordered set of variables
     */
    std::unordered_set<Entity> getUsesVar(Procedure &proc) const override;

    /**
     * Returns a boolean value indicating if the given statement uses the given variable
     * @param stmt The statement that uses the variable
     * @param var The variable that is used by the statement
     * @return True if the statement uses the variable, else false
     */
    bool isStmtUsesVar(Statement &stmt, Variable &var) const override;

    /**
     * Returns a boolean value indicating if the given procedure uses the given variable
     * @param proc The procedure that uses the variable
     * @param var The variable that is used by the procedure
     * @return True if the procedure uses the variable, else false
     */
    bool isProcUsesVar(Procedure &proc, Variable &var) const override;

    /**
     * Returns a boolean value indicating if the given statement uses any variable
     * @param stmt The statement to check
     * @return True if the statement uses any variable, else false
     */
    bool hasUses(Statement &stmt) const override;

    /**
     * Returns a boolean value indicating if the given procedure uses any variable
     * @param proc The procedure to check
     * @return True if the statement uses any variable, else false
     */
    bool hasUses(Procedure &proc) const override;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement follows the second statement
     * DIRECTLY. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return An unordered set of Statement, Statement pair stored in a vector
     */
    std::unordered_set<std::vector<Entity>> getFollowsPair(StatementType formerType,
                                                           StatementType latterType) const override;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement follows the second statement
     * DIRECTLY or INDIRECTLY. Retrieves the relationship where the first and second statement are both of the given
     * type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return An unordered set of Statement, Statement pair stored in a vector
     */
    std::unordered_set<std::vector<Entity>> getFollowsStarPair(StatementType formerType,
                                                               StatementType latterType) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is followed by the given statement
     * DIRECTLY i.e. the given statement is directly after the statement in the set
     * @param type The type of the statement to be retrieved
     * @param statement The statement that succeeds the statements to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getFollowsTypeStmt(StatementType type, Statement &statement) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is followed by the given statement
     * DIRECTLY or INDIRECTLY i.e. the given statement is directly or indirectly after the statement in the set
     * @param type The type of the statement to be retrieved
     * @param statement The statement that succeeds the statements to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getFollowsStarTypeStmt(StatementType type, Statement &statement) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is followed by any statement i.e. there
     * exist a statement after the statement in the set
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getFollowsTypeWildcard(StatementType type) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is followed by any statement i.e. there
     * exist a statement after the statement in the set
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getFollowsStarTypeWildcard(StatementType type) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which follows the given statement DIRECTLY
     * i.e. the given statement is directly before the statement in the set
     * @param statement The statement that precedes the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getFollowsStmtType(Statement &statement, StatementType type) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which follows the given statement DIRECTLY or
     * INDIRECTLY i.e. the given statement is directly or indirectly before the statement in the set
     * @param statement The statement that precedes the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getFollowsStarStmtType(Statement &statement, StatementType type) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which follows any statement i.e. there exist a
     * statement before the statement in the set
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getFollowsWildcardType(StatementType type) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which follows any statement i.e. there exist a
     * statement before the statement in the set
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getFollowsStarWildcardType(StatementType type) const override;

    /**
     * Returns true if statement1 DIRECTLY precedes statement2, false otherwise
     * @param statement1 The preceding statement
     * @param statement2 The succeeding statement
     * @return True if statement1 directly precedes statement2, false otherwise
     */
    bool isFollows(Statement &statement1, Statement &statement2) const override;

    /**
     * Returns true if statement1 DIRECTLY or INDIRECTLY precedes statement2, false otherwise
     * @param statement1 The preceding statement
     * @param statement2 The succeeding statement
     * @return True if statement1 directly or indirectly precedes statement2, false otherwise
     */
    bool isFollowsStar(Statement &statement1, Statement &statement2) const override;

    /**
     * Returns true if there exists a follows relationship in the PKB, false otherwise
     * @return True if there exists a follows relationship in the PKB, false otherwise
     */
    bool hasFollows() const override;

    /**
     * Returns true if there exists a follows star relationship in the PKB, false otherwise
     * @return True if there exists a follows star relationship in the PKB, false otherwise
     */
    bool hasFollowsStar() const override;

    /**
     * Returns true if there exists a statement that succeeds the given statement, false otherwise i.e. there is a
     * statement behind the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that succeeds the given statement, false otherwise
     */
    bool hasLatterStmt(Statement &statement) const override;

    /**
     * Returns true if there exists a statement that precedes the given statement, false otherwise i.e. there is a
     * statement in front of the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that precedes the given statement, false otherwise
     */
    bool hasFormerStmt(Statement &statement) const override;

    /**
     * Returns true if there exists a statement that succeeds the given statement, false otherwise i.e. there is a
     * statement behind the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that succeeds the given statement, false otherwise
     */
    bool hasLatterStarStmt(Statement &statement) const override;

    /**
     * Returns true if there exists a statement that precedes the given statement, false otherwise i.e. there is a
     * statement in front of the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that precedes the given statement, false otherwise
     */
    bool hasFormerStarStmt(Statement &statement) const override;

    /**
     * Returns an unordered_set of Statement, Variable pair where the statement modifies the variable. Retrieves the
     * relationship where the statement is of the given type
     * @param type The type of the statement
     * @return An unordered set of Statement, Variable pair stored in a vector
     */
    std::unordered_set<std::vector<Entity>> getModifiesStmtPair(StatementType type) const override;

    /**
     * Returns an unordered_set of Procedure, Variable pair where the procedure modifies the variable.
     * @return An unordered set of Procedure, Variable pair stored in a vector
     */
    std::unordered_set<std::vector<Entity>> getModifiesProcPair() const override;

    /**
     * Returns an unordered_set of statements of StatementType type which modifies the given variable
     * @param type The type of the statement to be retrieved
     * @param var The variable that is modified by the statements
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getModifiesTypeIdent(StatementType type, Variable &var) const override;

    /**
     * Returns an unordered_set of procedures which modifies the given variable
     * @param var The variable that is modified by the procedure
     * @return An unordered set of procedures
     */
    std::unordered_set<Entity> getModifiesProcIdent(Variable &var) const override;


    /**
     * Returns an unordered_set of statements of the given statement type which modifies any variable
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getModifiesStmt(StatementType type) const override;

    /**
     * Returns an unordered_set of procedures which modifies any variable
     * @return An unordered set of procedures
     */
    std::unordered_set<Entity> getModifiesProc() const override;

    /**
     * Returns an unordered_set of variables which is modified by the given statement
     * @param stmt The statement that modifies the variables
     * @return An unordered set of variables
     */
    std::unordered_set<Entity> getModifiesVar(Statement &stmt) const override;

    /**
     * Returns an unordered_set of variables which is modified by the given procedure
     * @param proc The procedure that modifies the variables
     * @return An unordered set of variables
     */
    std::unordered_set<Entity> getModifiesVar(Procedure &proc) const override;

    /**
     * Returns a boolean value indicating if the given statement modifies the given variable
     * @param stmt The statement that modifies the variable
     * @param var The variable that is modified by the statement
     * @return A boolean value indicating if the statement modifies the variable
     */
    bool isStmtModifiesVar(Statement &stmt, Variable &var) const override;

    /**
     * Returns a boolean value indicating if the given procedure modifies the given variable
     * @param proc The procedure that modifies the variable
     * @param var The variable that is modified by the procedure
     * @return A boolean value indicating if the procedure modifies the variable
     */
    bool isProcModifiesVar(Procedure &proc, Variable &var) const override;

    /**
     * Returns a boolean value indicating if the given statement modifies any variable
     * @param stmt The statement to be checked
     * @return A boolean value indicating if the statement modifies any variable
     */
    bool hasModifies(Statement &stmt) const override;

    /**
     * Returns a boolean value indicating if the given procedure modifies any variable
     * @param stmt The procedure to be checked
     * @return A boolean value indicating if the procedure modifies any variable
     */
    bool hasModifies(Procedure &proc) const override;

    /**
     * Returns an unordered_set of Statements from all the Assignment objects in the store. Represents all the
     * Statements that are assignments
     * @return An unordered set of all the Statement objects
     * @note Used for `pattern a (_,_)`
     */
    std::unordered_set<Entity> getAllAssign() const override;

    /**
     * Returns an unordered_set of Statement objects from Assignment objects in the store with Expressions that match
     * the given pattern. Represents all the statements that are assignments with Expressions that match the given
     * pattern
     * @param rhs The pattern to be matched against the Expressions
     * @param hasRhsWildCard A boolean value indicating if the pattern has a wildcard
     * @return An unordered set of Statement objects
     * @note Used for `pattern a (_, "x")`
     */
    std::unordered_set<Entity> getAssignStmtsByRhs(Expression &rhs, bool hasRhsWildCard) const override;

    /**
     * Returns an unordered_set of vectors containing Statement and Variable pairs from all the Assignment objects in
     * the store
     * @return An unordered set of vectors containing Statement and Variable pairs
     * @note Used for `pattern a (v, _)`
     */
    std::unordered_set<std::vector<Entity>> getAllAssignStmtVarPair() const override;

    /**
     * Returns an unordered_set of vectors containing Statement and Variable pairs from the Assignment objects in the
     * store with the Expression matching the given pattern
     * @param rhs The pattern to be matched against the Expressions
     * @param hasWildCard A boolean value indicating if the pattern has a wildcard
     * @return An unordered set of vectors containing Statement and Variable pairs
     * @note Used for `pattern a (v, "x")`
     */
    std::unordered_set<std::vector<Entity>> getAssignStmtsVarPairByRhs(Expression &rhs,
                                                                       bool hasWildCard) const override;

    /**
     * Returns an unordered_set of Statement objects from Assignment objects in the store where the Variable that is
     * assigned matches the given Variable.
     * @param lhs The Variable to be matched against
     * @return An unordered set of Statement objects
     * @note Used for `pattern a ("x", _)`
     */
    std::unordered_set<Entity> getAssignStmtsByLhs(Variable &lhs) const override;

    /**
     * Returns an unordered_set of Statement objects from Assignment objects in the store where the Variable that is
     * assigned matches the given Variable and the Expression matches the given pattern.
     * @param lhs The Variable to be matched against
     * @param rhs The pattern to be matched against the Expressions
     * @param hasRhsWildCard A boolean value indicating if the pattern has a wildcard
     * @return An unordered set of Statement objects
     * @note Used for `pattern a ("x", "x")`
     */
    std::unordered_set<Entity> getAssignStmtsByLhsRhs(Variable &lhs, Expression &rhs,
                                                      bool hasRhsWildCard) const override;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement is the DIRECT parent of the
     * second statement. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return An unordered set of Statement, Statement pair stored in a vector
     */
    std::unordered_set<std::vector<Entity>> getParentPair(StatementType formerType,
                                                          StatementType latterType) const override;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement is the DIRECT or INDIRECT parent
     * of the second statement. Retrieves the relationship where the first and second statement are both of the given
     * type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return An unordered set of Statement, Statement pair stored in a vector
     */
    std::unordered_set<std::vector<Entity>> getParentStarPair(StatementType formerType,
                                                              StatementType latterType) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is the DIRECT parent of the given
     * statement
     * @param type The type of the statement to be retrieved
     * @param statement The statement that is the direct child of the statements to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getParentTypeStmt(StatementType type, Statement &statement) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is the DIRECT or INDIRECT parent of the
     * given statement
     * @param type The type of the statement to be retrieved
     * @param statement The statement that is the direct or indirect child of the statements to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getParentStarTypeStmt(StatementType type, Statement &statement) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is the direct parent of any statement
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getParentTypeWildcard(StatementType type) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is the direct or indirect parent of any
     * statement
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getParentStarTypeWildcard(StatementType type) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is the DIRECT child of the given
     * statement
     * @param statement The statement that is the direct parent of the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getParentStmtType(Statement &statement, StatementType type) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is the DIRECT or INDIRECT child of the
     * given statement
     * @param statement The statement that is the direct or indirect parent of the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getParentStarStmtType(Statement &statement, StatementType type) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is the direct child of any statement
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getParentWildcardType(StatementType type) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is the direct or indirect child of any
     * statement
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getParentStarWildcardType(StatementType type) const override;

    /**
     * Returns a boolean value indicating if the first statement is the DIRECT parent of the second statement
     * @param statement1 The parent statement
     * @param statement2 The child statement
     * @return True if the first statement is the direct parent of the second statement, false otherwise
     */
    bool isParent(Statement &statement1, Statement &statement2) const override;

    /**
     * Returns a boolean value indicating if the first statement is the DIRECT or INDIRECT parent of the second
     * statement
     * @param statement1 The parent statement
     * @param statement2 The child statement
     * @return True if the first statement is the direct or indirect parent of the second statement, false otherwise
     */
    bool isParentStar(Statement &statement1, Statement &statement2) const override;

    /**
     * Returns a boolean value indicating if there exists a Parent relationship
     * @return True if there exists a Parent relationship, false otherwise
     */
    bool hasParent() const override;

    /**
     * Returns a boolean value indicating if there exists a Parent Star relationship
     * @return True if there exists a Parent relationship, false otherwise
     */
    bool hasParentStar() const override;

    /**
     * Returns a boolean value indicating if the given statement is the direct child of any statement
     * @param statement The statement to be checked
     * @return True if the given statement is the child of any statement, false otherwise
     */
    bool hasParentStmt(Statement &statement) const override;

    /**
     * Returns a boolean value indicating if the given statement is the direct or indirect child of any statement
     * @param statement The statement to be checked
     * @return True if the given statement is the child of any statement, false otherwise
     */
    bool hasParentStarStmt(Statement &statement) const override;

    /**
     * Returns a boolean value indicating if the given statement is the direct parent of any statement
     * @param statement The statement to be checked
     * @return True if the given statement is the parent of any statement, false otherwise
     */
    bool hasChildStmt(Statement &statement) const override;

    /**
     * Returns a boolean value indicating if the given statement is the direct or indirect parent of any statement
     * @param statement The statement to be checked
     * @return True if the given statement is the parent of any statement, false otherwise
     */
    bool hasChildStarStmt(Statement &statement) const override;

    /**
     * Returns a boolean value indicating if there exists a Calls relationship
     * @return True if there exists a Calls relationship, false otherwise
     */
    bool hasCalls() const override;

    /**
     * Returns a boolean value indicating if there exists a Calls Star relationship
     * @return True if there exists a Calls Star relationship, false otherwise
     */
    bool hasCallsStar() const override;

    /**
     * Returns a boolean value indicating if the given procedure is called directly by any other procedure
     * @param proc The procedure to be checked
     * @return True if the given procedure is called directly by any other procedure, false otherwise
     */
    bool isCallee(Procedure &proc) const override;

    /**
     * Returns a boolean value indicating if the given procedure is called directly or indirectly by any other procedure
     * @param proc The procedure to be checked
     * @return True if the given procedure is called directly or indirectly by any other procedure, false otherwise
     */
    bool isCalleeStar(Procedure &proc) const override;

    /**
     * Returns a boolean value indicating if the given procedure calls any other procedure directly
     * @param proc The procedure to be checked
     * @return True if the given procedure calls any other procedure directly, false otherwise
     */
    bool isCaller(Procedure &proc) const override;

    /**
     * Returns a boolean value indicating if the given procedure calls any other procedure directly or indirectly
     * @param proc The procedure to be checked
     * @return True if the given procedure calls any other procedure directly or indirectly, false otherwise
     */
    bool isCallerStar(Procedure &proc) const override;

    /**
     * Returns a boolean value indicating if the first procedure calls the second procedure directly
     * @param caller The calling procedure
     * @param callee The called procedure
     * @return True if the first procedure calls the second procedure directly, false otherwise
     */
    bool isCalls(Procedure &caller, Procedure &callee) const override;

    /**
     * Returns a boolean value indicating if the first procedure calls the second procedure directly or indirectly
     * @param caller The calling procedure
     * @param callee The called procedure
     * @return True if the first procedure calls the second procedure directly or indirectly, false otherwise
     */
    bool isCallsStar(Procedure &caller, Procedure &callee) const override;

    /**
     * Returns an unordered_set of procedures which is called directly by any other procedure
     * @return An unordered set of procedures
     */
    std::unordered_set<Entity> getCallees() const override;

    /**
     * Returns an unordered_set of procedures which is called directly or indirectly by any other procedure
     * @return An unordered set of procedures
     */
    std::unordered_set<Entity> getCalleesStar() const override;

    /**
     * Returns an unordered_set of procedures which calls any other procedure directly
     * @return An unordered set of procedures
     */
    std::unordered_set<Entity> getCallers() const override;

    /**
     * Returns an unordered_set of procedures which calls any other procedure directly or indirectly
     * @return An unordered set of procedures
     */
    std::unordered_set<Entity> getCallersStar() const override;

    /**
     * Returns an unordered_set of Procedure, Procedure pair where the first procedure calls the second procedure
     * DIRECTLY
     * @return An unordered set of Procedure, Procedure pair stored in a vector
     */
    std::unordered_set<std::vector<Entity>> getCallsPair() const override;

    /**
     * Returns an unordered_set of Procedure, Procedure pair where the first procedure calls the second procedure
     * DIRECTLY or INDIRECTLY
     * @return An unordered set of Procedure, Procedure pair stored in a vector
     */
    std::unordered_set<std::vector<Entity>> getCallsStarPair() const override;

    /**
     * Returns an unordered_set of procedures which calls the given procedure DIRECTLY
     * @param callee The procedure that is called by the procedures to be retrieved
     * @return An unordered set of procedures
     */
    std::unordered_set<Entity> getCallers(Procedure &callee) const override;

    /**
     * Returns an unordered_set of procedures which calls the given procedure DIRECTLY or INDIRECTLY
     * @param callee The procedure that is called by the procedures to be retrieved
     * @return An unordered set of procedures
     */
    std::unordered_set<Entity> getCallersStar(Procedure &callee) const override;

    /**
     * Returns an unordered_set of procedures which is called DIRECTLY by the given procedure
     * @param caller The procedure that calls the procedures to be retrieved
     * @return An unordered set of procedures
     */
    std::unordered_set<Entity> getCallees(Procedure &caller) const override;

    /**
     * Returns an unordered_set of procedures which is called DIRECTLY or INDIRECTLY by the given procedure
     * @param caller The procedure that calls the procedures to be retrieved
     * @return An unordered set of procedures
     */
    std::unordered_set<Entity> getCalleesStar(Procedure &caller) const override;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement is is executed IMMEDIATELY before
     * second statement. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return An unordered set of Statement, Statement pair stored in a vector
     */
    std::unordered_set<std::vector<Entity>> getNextPair(StatementType formerType,
                                                        StatementType latterType) const override;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement is executed before of the second
     * statement, either immediately or after some execution sequence. Retrieves the relationship where the first and
     * second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return An unordered set of Statement, Statement pair stored in a vector
     */
    std::unordered_set<std::vector<Entity>> getNextStarPair(StatementType formerType,
                                                            StatementType latterType) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed again after it has been
     * executed
     * @param stmtType The type of statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getNextStarSameStmt(StatementType stmtType) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed IMMEDIATELY before the given
     * statement
     * @param type The type of the statement to be retrieved
     * @param statement The statement that executed IMMEDIATELY after the statements to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getNextTypeStmt(StatementType type, Statement &statement) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed before the given statement,
     * either immediately or after some execution sequence
     * @param type The type of the statement to be retrieved
     * @param statement The statement that is executed after the statements to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getNextStarTypeStmt(StatementType type, Statement &statement) const override;

    /**
     * Returns an unordered_set of statements of the given statement type that is executed IMMEDIATELY before any
     * statement
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getNextTypeWildcard(StatementType type) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed before any statement, either
     * immediately or after some execution sequence
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getNextStarTypeWildcard(StatementType type) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed IMMEDIATELY after the given
     * statement
     * @param statement The statement that is executed IMMEDIATELY before the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getNextStmtType(Statement &statement, StatementType type) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed after the given statement,
     * either immediately or after some execution sequence
     * @param statement The statement that is executed after the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getNextStarStmtType(Statement &statement, StatementType type) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed IMMEDIATELY after any
     * statement
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getNextWildcardType(StatementType type) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed after any statement, either
     * immediately or after some execution sequence
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getNextStarWildcardType(StatementType type) const override;

    /**
     * Returns a boolean value indicating if the first statement is executed IMMEDIATELY before the second statement
     * @param statement1 The parent statement
     * @param statement2 The child statement
     * @return True if the first statement is executed IMMEDIATELY before the second statement, false otherwise
     */
    bool isNext(Statement &statement1, Statement &statement2) const override;

    /**
     * Returns a boolean value indicating if the first statement is executed before the second statement, either
     * immediately or after some execution sequence
     * @param statement1 The parent statement
     * @param statement2 The child statement
     * @return True if the first statement is executed before the second statement, false otherwise
     */
    bool isNextStar(Statement &statement1, Statement &statement2) const override;

    /**
     * Returns a boolean value indicating if there exists a Next relationship
     * @return True if there exists a Next relationship, false otherwise
     */
    bool hasNext() const override;

    /**
     * Returns a boolean value indicating if there exists a Next Star relationship
     * @return True if there exists a Next Star relationship, false otherwise
     */
    bool hasNextStar() const override;

    /**
     * Returns a boolean value indicating if the given statement is executed IMMEDIATELY after any statement
     * @param statement The statement to be checked
     * @return True if the given statement is executed IMMEDIATELY after any statement, false otherwise
     */
    bool hasBeforeStmt(Statement &statement) const override;

    /**
     * Returns a boolean value indicating if the given statement is executed after any statement, either immediately or
     * after some execution sequence
     * @param statement The statement to be checked
     * @return True if the given statement is executed after any statement, false otherwise
     */
    bool hasBeforeStarStmt(Statement &statement) const override;

    /**
     * Returns a boolean value indicating if the given statement is executed IMMEDIATELY before any statement
     * @param statement The statement to be checked
     * @return True if the given statement is executed IMMEDIATELY before any statement, false otherwise
     */
    bool hasAfterStmt(Statement &statement) const override;

    /**
     * Returns a boolean value indicating if the given statement is executed before any statement, either immediately or
     * after some execution sequence
     * @param statement The statement to be checked
     * @return True if the given statement is executed before any statement, false otherwise
     */
    bool hasAfterStarStmt(Statement &statement) const override;

    /**
     * Returns an unordered_set of If Statements that has variables as control variables
     * @return An unordered set of Statements
     */
    std::unordered_set<Entity> getAllIfPatternStmts() const override;

    /**
     * Returns an unordered_set of If Statements with the given variable as a control variable
     * @param var The variable to be checked
     * @return An unordered set of If Statements
     */
    std::unordered_set<Entity> getIfStmtsByVar(Variable &var) const override;

    /**
     * Returns an unordered_set of vectors containing If Statement and Variable pairs where the variable is the control
     * variable of the If Statement
     * @return An unordered set of vectors containing If Statement and Variable pairs
     */
    std::unordered_set<std::vector<Entity>> getAllIfStmtVarPair() const override;

    /**
     * Returns an unordered_set of While Statements that has variables as control variables
     * @return An unordered set of Statements
     */
    std::unordered_set<Entity> getAllWhilePatternStmts() const override;

    /**
     * Returns an unordered_set of While Statements with the given variable as a control variable
     * @param var The variable to be checked
     * @return An unordered set of While Statements
     */
    std::unordered_set<Entity> getWhileStmtsByVar(Variable &var) const override;

    /**
     * Returns an unordered_set of vectors containing While Statement and Variable pairs where the variable is the
     * control variable of the While Statement
     * @return An unordered set of vectors containing While Statement and Variable pairs
     */

    std::unordered_set<std::vector<Entity>> getAllWhileStmtVarPair() const override;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement affects the second statement
     * DIRECTLY. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return An unordered set of Statement, Statement pair stored in a vector
     */
    std::unordered_set<std::vector<Entity>> getAffectsPair(StatementType formerType,
                                                           StatementType latterType) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which affects itself
     * @param stmtType The type of statement to be retrieved
     * @return An unordered_set of statements
     */
    std::unordered_set<Entity> getAffectsSameStmt(StatementType stmtType) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which affects the given statement DIRECTLY
     * @param type The type of the statement to be retrieved
     * @param statement The statement that succeeds the statements to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getAffectsTypeStmt(StatementType type, Statement &statement) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is affects any statement DIRECTLY
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getAffectsTypeWildcard(StatementType type) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is affected by the given statement
     * DIRECTLY
     * @param statement The statement that precedes the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getAffectsStmtType(Statement &statement, StatementType type) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is affected by any statement DIRECTLY
     * @param type The type of the statement to be retrieved
     * @return An unordered set of statements
     */
    std::unordered_set<Entity> getAffectsWildcardType(StatementType type) const override;

    /**
     * Returns true if statement1 DIRECTLY affects statement2, false otherwise
     * @param statement1 The preceding statement
     * @param statement2 The succeeding statement
     * @return True if statement1 directly affects statement2, false otherwise
     */
    bool isAffects(Statement &statement1, Statement &statement2) const override;

    /**
     * Returns true if there exists a affects relationship in the PKB, false otherwise
     * @return True if there exists a affects relationship in the PKB, false otherwise
     */
    bool hasAffects() const override;

    /**
     * Returns true if there exists a statement that is affected by the given statement, false otherwise i.e. there is a
     * statement in behind of the given statement that is affected by the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that is affected by the given statement, false otherwise
     */
    bool hasAffectedStmt(Statement &statement) const override;

    /**
     * Returns true if there exists a statement that affects the given statement, false otherwise i.e. there is a
     * statement in front of the given statement that affects the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that affects the given statement, false otherwise
     */
    bool hasAffectsStmt(Statement &statement) const override;
};