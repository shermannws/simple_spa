#pragma once

#include <memory>

#include "PKB/Managers/AffectsRelationshipManager.h"
#include "PKB/Managers/AssignPatternManager.h"
#include "PKB/Managers/CallsRelationshipManager.h"
#include "PKB/Managers/EntitiesManager.h"
#include "PKB/Managers/FollowsRelationshipManager.h"
#include "PKB/Managers/IfPatternManager.h"
#include "PKB/Managers/ModifiesProcRelationshipManager.h"
#include "PKB/Managers/ModifiesRelationshipManager.h"
#include "PKB/Managers/NextRelationshipManager.h"
#include "PKB/Managers/ParentRelationshipManager.h"
#include "PKB/Managers/UsesProcRelationshipManager.h"
#include "PKB/Managers/UsesRelationshipManager.h"
#include "PKB/Managers/WhilePatternManager.h"
#include "PKB/PkbTypes.h"

/**
 * @brief This class is responsible for reading data from PKB.
 */
class PkbReaderManager {
private:
    /**
     * @brief The assignment manager.
     */
    std::shared_ptr<AssignPatternManager> assignmentManager;

    /**
     * @brief The entities manager.
     */
    std::shared_ptr<EntitiesManager> entityManager;

    /**
     * @brief The follows relationship manager.
     */
    std::shared_ptr<FollowsRelationshipManager> followsRelationshipManager;

    /**
     * @brief The uses relationship manager.
     */
    std::shared_ptr<UsesRelationshipManager> usesRelationshipManager;

    /**
     * @brief The modifies relationship manager.
     */
    std::shared_ptr<ModifiesRelationshipManager> modifiesRelationshipManager;

    /**
     * @brief The parent relationship manager.
     */
    std::shared_ptr<ParentRelationshipManager> parentRelationshipManager;

    /**
     * @brief The calls relationship manager.
     */
    std::shared_ptr<CallsRelationshipManager> callsRelationshipManager;

    /**
     * @brief The modifies procedure relationship manager.
     */
    std::shared_ptr<ModifiesProcRelationshipManager> modifiesProcRelationshipManager;

    /**
     * @brief The uses procedure relationship manager.
     */
    std::shared_ptr<UsesProcRelationshipManager> usesProcRelationshipManager;

    /**
     * @brief The if pattern manager.
     */
    std::shared_ptr<IfPatternManager> ifPatternManager;

    /**
     * @brief The while pattern manager.
     */
    std::shared_ptr<WhilePatternManager> whilePatternManager;

    /**
     * @brief The next relationship manager.
     */
    std::shared_ptr<NextRelationshipManager> nextRelationshipManager;

    /**
     * @brief The affects relationship manager.
     */
    std::shared_ptr<AffectsRelationshipManager> affectsRelationshipManager;

public:
    /**
     * @brief Constructs a PkbReaderManager object.
     * @param assignmentManager The assignment manager.
     * @param entityManager The entities manager.
     * @param followsRelationshipManager The follows relationship manager.
     * @param usesRelationshipManager The uses relationship manager.
     * @param modifiesRelationshipManager The modifies relationship manager.
     * @param parentRelationshipManager The parent relationship manager.
     * @param callsRelationshipManager The calls relationship manager.
     * @param modifiesProcRelationshipManager The modifies procedure relationship manager.
     * @param usesProcRelationshipManager The uses procedure relationship manager.
     * @param ifPatternManager The if pattern manager.
     * @param whilePatternManager The while pattern manager.
     * @param nextRelationshipManager The next relationship manager.
     * @param affectsRelationshipManager The affects relationship manager.
     * @return The PkbReaderManager object.
     */
    PkbReaderManager(std::shared_ptr<AssignPatternManager> assignmentManager,
                     std::shared_ptr<EntitiesManager> entityManager,
                     std::shared_ptr<FollowsRelationshipManager> followsRelationshipManager,
                     std::shared_ptr<UsesRelationshipManager> usesRelationshipManager,
                     std::shared_ptr<ModifiesRelationshipManager> modifiesRelationshipManager,
                     std::shared_ptr<ParentRelationshipManager> parentRelationshipManager,
                     std::shared_ptr<CallsRelationshipManager> callsRelationshipManager,
                     std::shared_ptr<ModifiesProcRelationshipManager> modifiesProcRelationshipManager,
                     std::shared_ptr<UsesProcRelationshipManager> usesProcRelationshipManager,
                     std::shared_ptr<IfPatternManager> ifPatternManager,
                     std::shared_ptr<WhilePatternManager> whilePatternManager,
                     std::shared_ptr<NextRelationshipManager> nextRelationshipManager,
                     std::shared_ptr<AffectsRelationshipManager> affectsRelationshipManager);

    /**
     * @brief Returns all the variables in the SIMPLE program.
     * @return An unordered_set of variables.
     */
    EntitySet getAllVariables() const;

    /**
     * @brief Returns all the constants in the SIMPLE program.
     * @return An unordered_set of constants.
     */
    EntitySet getAllConstants() const;

    /**
     * @brief Returns all the procedures in the SIMPLE program.
     * @return An unordered_set of procedures.
     */
    EntitySet getAllProcedures() const;

    /**
     * @brief Returns all the statements in the SIMPLE program.
     * @return An unordered_set of statements.
     */
    EntitySet getAllStatements() const;

    /**
     * @brief Returns all the read statements in the SIMPLE program.
     * @return An unordered_set of read statements.
     */
    EntitySet getAllRead() const;

    /**
     * @brief Returns all the print statements in the SIMPLE program.
     * @return An unordered_set of print statements.
     */
    EntitySet getAllPrint() const;

    /**
     * @brief Returns all the while statements in the SIMPLE program.
     * @return An unordered_set of while statements.
     */
    EntitySet getAllWhile() const;

    /**
     * @brief Returns all the if statements in the SIMPLE program.
     * @return An unordered_set of if statements.
     */
    EntitySet getAllIf() const;

    /**
     * @brief Returns all the call statements in the SIMPLE program.
     * @return An unordered_set of call statements.
     */
    EntitySet getAllCall() const;

    /**
     * Returns an unordered_set of Statement, Variable pair where the statement uses the variable. Retrieves the
     * relationship where the statement is of the given type
     * @param type The type of the statement
     * @return An unordered_set of Statement, Variable pair stored in a vector
     */
    EntityPairSet getUsesStmtPair(StatementType type) const;

    /**
     * Returns an unordered_set of Procedure, Variable pair where the procedure uses the variable.
     * @return An unordered_set of Procedure, Variable pair stored in a vector
     */
    EntityPairSet getUsesProcPair() const;

    /**
     * Returns an unordered_set of statements of StatementType type which uses the given variable
     * @param type The type of the statement to be retrieved
     * @param var The variable that is used by the statements
     * @return An unordered_set of statements
     */
    EntitySet getUsesTypeIdent(StatementType type, Variable &var) const;

    /**
     * Returns an unordered_set of procedures which uses the given variable
     * @param var The variable that is used by the statements
     * @return An unordered_set of procedures
     */
    EntitySet getUsesProcIdent(Variable &var) const;

    /**
     * Returns an unordered_set of statements of the given statement type which uses any variable
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getUsesStmt(StatementType type) const;

    /**
     * Returns an unordered_set of procedures which uses any variable
     * @return An unordered_set of procedures
     */
    EntitySet getUsesProc() const;

    /**
     * Returns an unordered_set of variables which is used by the given statement
     * @param stmt The statement that uses the variables
     * @return An unordered_set of variables
     */
    EntitySet getUsesVar(Statement &stmt) const;

    /**
     * Returns an unordered_set of variables which is used by the given procedure
     * @param proc The procedure that uses the variables
     * @return An unordered_set of variables
     */
    EntitySet getUsesVar(Procedure &proc) const;

    /**
     * Returns a boolean value indicating if the given statement uses the given variable
     * @param stmt The statement that uses the variable
     * @param var The variable that is used by the statement
     * @return True if the statement uses the variable, else false
     */
    bool isStmtUsesVar(Statement &stmt, Variable &var) const;

    /**
     * Returns a boolean value indicating if the given procedure uses the given variable
     * @param proc The procedure that uses the variable
     * @param var The variable that is used by the procedure
     * @return True if the procedure uses the variable, else false
     */
    bool isProcUsesVar(Procedure &proc, Variable &var) const;

    /**
     * Returns a boolean value indicating if the given statement uses any variable
     * @param stmt The statement that uses the variable
     * @return True if the statement uses any variable, else false
     */
    bool hasUses(Statement &stmt) const;

    /**
     * Returns a boolean value indicating if the given procedure uses any variable
     * @param proc The procedure to check
     * @return True if the statement uses any variable, else false
     */
    bool hasUses(Procedure &proc) const;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement follows the second statement
     * DIRECTLY. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return An unordered_set of Statement, Statement pair stored in a vector
     */
    EntityPairSet getFollowsPair(StatementType formerType, StatementType latterType) const;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement follows the second statement
     * DIRECTLY or INDIRECTLY. Retrieves the relationship where the first and second statement are both of the given
     * type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return An unordered_set of Statement, Statement pair stored in a vector
     */
    EntityPairSet getFollowsStarPair(StatementType formerType, StatementType latterType) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is followed by the given statement
     * DIRECTLY i.e. the given statement is directly after the statement in the set
     * @param type The type of the statement to be retrieved
     * @param statement The statement that succeeds the statements to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getFollowsTypeStmt(StatementType type, Statement &statement) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is followed by the given statement
     * DIRECTLY or INDIRECTLY i.e. the given statement is directly or indirectly after the statement in the set
     * @param type The type of the statement to be retrieved
     * @param statement The statement that succeeds the statements to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getFollowsStarTypeStmt(StatementType type, Statement &statement) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is followed by any statement i.e. there
     * exist a statement after the statement in the set
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getFollowsTypeWildcard(StatementType type) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is followed by any statement i.e. there
     * exist a statement after the statement in the set
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getFollowsStarTypeWildcard(StatementType type) const;

    /**
     * Returns an unordered_set of statements of the given statement type which follows the given statement DIRECTLY
     * i.e. the given statement is directly before the statement in the set
     * @param statement The statement that precedes the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getFollowsStmtType(Statement &statement, StatementType type) const;

    /**
     * Returns an unordered_set of statements of the given statement type which follows the given statement DIRECTLY or
     * INDIRECTLY i.e. the given statement is directly or indirectly before the statement in the set
     * @param statement The statement that precedes the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getFollowsStarStmtType(Statement &statement, StatementType type) const;

    /**
     * Returns an unordered_set of statements of the given statement type which follows any statement i.e. there exist a
     * statement before the statement in the set
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getFollowsWildcardType(StatementType type) const;

    /**
     * Returns an unordered_set of statements of the given statement type which follows any statement i.e. there exist a
     * statement before the statement in the set
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getFollowsStarWildcardType(StatementType type) const;

    /**
     * Returns true if statement1 DIRECTLY precedes statement2, false otherwise
     * @param statement1 The preceding statement
     * @param statement2 The succeeding statement
     * @return True if statement1 directly precedes statement2, false otherwise
     */
    bool isFollows(Statement &statement1, Statement &statement2) const;

    /**
     * Returns true if statement1 DIRECTLY or INDIRECTLY precedes statement2, false otherwise
     * @param statement1 The preceding statement
     * @param statement2 The succeeding statement
     * @return True if statement1 directly or indirectly precedes statement2, false otherwise
     */
    bool isFollowsStar(Statement &statement1, Statement &statement2) const;

    /**
     * Returns true if there exists a follows relationship in the PKB, false otherwise
     * @return True if there exists a follows relationship in the PKB, false otherwise
     */
    bool hasFollows() const;

    /**
     * Returns true if there exists a follows star relationship in the PKB, false otherwise
     * @return True if there exists a follows star relationship in the PKB, false otherwise
     */
    bool hasFollowsStar() const;

    /**
     * Returns true if there exists a statement that succeeds the given statement, false otherwise i.e. there is a
     * statement behind the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that succeeds the given statement, false otherwise
     */
    bool hasLatterStmt(Statement &statement) const;

    /**
     * Returns true if there exists a statement that precedes the given statement, false otherwise i.e. there is a
     * statement in front of the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that precedes the given statement, false otherwise
     */
    bool hasFormerStmt(Statement &statement) const;

    /**
     * Returns true if there exists a statement that succeeds the given statement, false otherwise i.e. there is a
     * statement behind the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that succeeds the given statement, false otherwise
     */
    bool hasLatterStarStmt(Statement &statement) const;

    /**
     * Returns true if there exists a statement that precedes the given statement, false otherwise i.e. there is a
     * statement in front of the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that precedes the given statement, false otherwise
     */
    bool hasFormerStarStmt(Statement &statement) const;

    /**
     * Returns an unordered_set of Statement, Variable pair where the statement modifies the variable. Retrieves the
     * relationship where the statement is of the given type
     * @param type The type of the statement
     * @return An unordered_set of Statement, Variable pair stored in a vector
     */
    EntityPairSet getModifiesStmtPair(StatementType type) const;

    /**
     * Returns an unordered_set of Procedure, Variable pair where the procedure modifies the variable.
     * @return An unordered_set of Procedure, Variable pair stored in a vector
     */
    EntityPairSet getModifiesProcPair() const;

    /**
     * Returns an unordered_set of statements of StatementType type which modifies the given variable
     * @param type The type of the statement to be retrieved
     * @param var The variable that is modified by the statements
     * @return An unordered_set of statements
     */
    EntitySet getModifiesTypeIdent(StatementType type, Variable &var) const;

    /**
     * Returns an unordered_set of procedures which modifies the given variable
     * @param var The variable that is modified by the procedure
     * @return An unordered_set of procedures
     */
    EntitySet getModifiesProcIdent(Variable &var) const;

    /**
     * Returns an unordered_set of statements of the given statement type which modifies any variable
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getModifiesStmt(StatementType type) const;

    /**
     * Returns an unordered_set of procedures which modifies any variable
     * @return An unordered_set of procedures
     */
    EntitySet getModifiesProc() const;

    /**
     * Returns an unordered_set of variables which is modified by the given statement
     * @param stmt The statement that modifies the variables
     * @return An unordered_set of variables
     */
    EntitySet getModifiesVar(Statement &stmt) const;

    /**
     * Returns an unordered_set of variables which is modified by the given procedure
     * @param proc The procedure that modifies the variables
     * @return An unordered_set of variables
     */
    EntitySet getModifiesVar(Procedure &proc) const;

    /**
     * Returns a boolean value indicating if the given statement modifies the given variable
     * @param stmt The statement that modifies the variable
     * @param var The variable that is modified by the statement
     * @return A boolean value indicating if the statement modifies the variable
     */
    bool isStmtModifiesVar(Statement &stmt, Variable &var) const;

    /**
     * Returns a boolean value indicating if the given procedure modifies the given variable
     * @param proc The procedure that modifies the variable
     * @param var The variable that is modified by the procedure
     * @return A boolean value indicating if the procedure modifies the variable
     */
    bool isProcModifiesVar(Procedure &proc, Variable &var) const;

    /**
     * Returns a boolean value indicating if the given statement modifies any variable
     * @param stmt The statement to be checked
     * @return A boolean value indicating if the statement modifies any variable
     */
    bool hasModifies(Statement &stmt) const;

    /**
     * Returns a boolean value indicating if the given procedure modifies any variable
     * @param stmt The procedure to be checked
     * @return A boolean value indicating if the procedure modifies any variable
     */
    bool hasModifies(Procedure &proc) const;

    /**
     * Returns an unordered_set of Statements from all the Assignment objects in the store. Represents all the
     * Statements that are assignments
     * @return An unordered_set of all the Statement objects
     * @note Used for `pattern a (_,_)`
     */
    EntitySet getAllAssign() const;

    /**
     * Returns an unordered_set of Statement objects from Assignment objects in the store with Expressions that match
     * the given pattern. Represents all the statements that are assignments with Expressions that match the given
     * pattern
     * @param rhs The pattern to be matched against the Expressions
     * @param hasRhsWildCard A boolean value indicating if the pattern has a wildcard
     * @return An unordered_set of Statement objects
     * @note Used for `pattern a (_, "x")`
     */
    EntitySet getAssignStmtsByRhs(Expression &rhs, bool hasRhsWildCard) const;

    /**
     * Returns an unordered_set of vectors containing Statement and Variable pairs from all the Assignment objects in
     * the store
     * @return An unordered_set of vectors containing Statement and Variable pairs
     * @note Used for `pattern a (v, _)`
     */
    EntityPairSet getAllAssignStmtVarPair() const;

    /**
     * Returns an unordered_set of vectors containing Statement and Variable pairs from the Assignment objects in the
     * store with the Expression matching the given pattern
     * @param rhs The pattern to be matched against the Expressions
     * @param hasWildCard A boolean value indicating if the pattern has a wildcard
     * @return An unordered_set of vectors containing Statement and Variable pairs
     * @note Used for `pattern a (v, "x")`
     */
    EntityPairSet getAssignStmtsVarPairByRhs(Expression &rhs, bool hasWildCard) const;

    /**
     * Returns an unordered_set of Statement objects from Assignment objects in the store where the Variable that is
     * assigned matches the given Variable.
     * @param lhs The Variable to be matched against
     * @return An unordered_set of Statement objects
     * @note Used for `pattern a ("x", _)`
     */
    EntitySet getAssignStmtsByLhs(Variable &lhs) const;

    /**
     * Returns an unordered_set of Statement objects from Assignment objects in the store where the Variable that is
     * assigned matches the given Variable and the Expression matches the given pattern.
     * @param lhs The Variable to be matched against
     * @param rhs The pattern to be matched against the Expressions
     * @param hasRhsWildCard A boolean value indicating if the pattern has a wildcard
     * @return An unordered_set of Statement objects
     * @note Used for `pattern a ("x", "x")`
     */
    EntitySet getAssignStmtsByLhsRhs(Variable &lhs, Expression &rhs, bool hasRhsWildCard) const;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement is the DIRECT parent of the
     * second statement. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return An unordered_set of Statement, Statement pair stored in a vector
     */
    EntityPairSet getParentPair(StatementType formerType, StatementType latterType) const;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement is the DIRECT or INDIRECT parent
     * of the second statement. Retrieves the relationship where the first and second statement are both of the given
     * type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return An unordered_set of Statement, Statement pair stored in a vector
     */
    EntityPairSet getParentStarPair(StatementType formerType, StatementType latterType) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is the DIRECT parent of the given
     * statement
     * @param type The type of the statement to be retrieved
     * @param statement The statement that is the direct child of the statements to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getParentTypeStmt(StatementType type, Statement &statement) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is the DIRECT or INDIRECT parent of the
     * given statement
     * @param type The type of the statement to be retrieved
     * @param statement The statement that is the direct or indirect child of the statements to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getParentStarTypeStmt(StatementType type, Statement &statement) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is the direct parent of any statement
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getParentTypeWildcard(StatementType type) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is the direct or indirect parent of any
     * statement
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getParentStarTypeWildcard(StatementType type) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is the DIRECT child of the given
     * statement
     * @param statement The statement that is the direct parent of the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getParentStmtType(Statement &statement, StatementType type) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is the DIRECT or INDIRECT child of the
     * given statement
     * @param statement The statement that is the direct or indirect parent of the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getParentStarStmtType(Statement &statement, StatementType type) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is the direct child of any statement
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getParentWildcardType(StatementType type) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is the direct or indirect child of any
     * statement
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getParentStarWildcardType(StatementType type) const;

    /**
     * Returns a boolean value indicating if the first statement is the DIRECT parent of the second statement
     * @param statement1 The parent statement
     * @param statement2 The child statement
     * @return True if the first statement is the direct parent of the second statement, false otherwise
     */
    bool isParent(Statement &statement1, Statement &statement2) const;

    /**
     * Returns a boolean value indicating if the first statement is the DIRECT or INDIRECT parent of the second
     * statement
     * @param statement1 The parent statement
     * @param statement2 The child statement
     * @return True if the first statement is the direct or indirect parent of the second statement, false otherwise
     */
    bool isParentStar(Statement &statement1, Statement &statement2) const;

    /**
     * Returns a boolean value indicating if there exists a Parent relationship
     * @return True if there exists a Parent relationship, false otherwise
     */
    bool hasParent() const;

    /**
     * Returns a boolean value indicating if there exists a Parent Star relationship
     * @return True if there exists a Parent relationship, false otherwise
     */
    bool hasParentStar() const;

    /**
     * Returns a boolean value indicating if the given statement is the direct child of any statement
     * @param statement The statement to be checked
     * @return True if the given statement is the child of any statement, false otherwise
     */
    bool hasParentStmt(Statement &statement) const;

    /**
     * Returns a boolean value indicating if the given statement is the direct or indirect child of any statement
     * @param statement The statement to be checked
     * @return True if the given statement is the child of any statement, false otherwise
     */
    bool hasParentStarStmt(Statement &statement) const;

    /**
     * Returns a boolean value indicating if the given statement is the direct parent of any statement
     * @param statement The statement to be checked
     * @return True if the given statement is the parent of any statement, false otherwise
     */
    bool hasChildStmt(Statement &statement) const;

    /**
     * Returns a boolean value indicating if the given statement is the direct or indirect parent of any statement
     * @param statement The statement to be checked
     * @return True if the given statement is the parent of any statement, false otherwise
     */
    bool hasChildStarStmt(Statement &statement) const;

    /**
     * Returns a boolean value indicating if there exists a Calls relationship
     * @return True if there exists a Calls relationship, false otherwise
     */
    bool hasCalls() const;

    /**
     * Returns a boolean value indicating if there exists a Calls Star relationship
     * @return True if there exists a Calls Star relationship, false otherwise
     */
    bool hasCallsStar() const;

    /**
     * Returns a boolean value indicating if the given procedure is called directly by any other procedure
     * @param proc The procedure to be checked
     * @return True if the given procedure is called directly by any other procedure, false otherwise
     */
    bool isCallee(Procedure &proc) const;

    /**
     * Returns a boolean value indicating if the given procedure is called directly or indirectly by any other procedure
     * @param proc The procedure to be checked
     * @return True if the given procedure is called directly or indirectly by any other procedure, false otherwise
     */
    bool isCalleeStar(Procedure &proc) const;

    /**
     * Returns a boolean value indicating if the given procedure calls any other procedure directly
     * @param proc The procedure to be checked
     * @return True if the given procedure calls any other procedure directly, false otherwise
     */
    bool isCaller(Procedure &proc) const;

    /**
     * Returns a boolean value indicating if the given procedure calls any other procedure directly or indirectly
     * @param proc The procedure to be checked
     * @return True if the given procedure calls any other procedure directly or indirectly, false otherwise
     */
    bool isCallerStar(Procedure &proc) const;

    /**
     * Returns a boolean value indicating if the first procedure calls the second procedure directly
     * @param caller The calling procedure
     * @param callee The called procedure
     * @return True if the first procedure calls the second procedure directly, false otherwise
     */
    bool isCalls(Procedure &caller, Procedure &callee) const;

    /**
     * Returns a boolean value indicating if the first procedure calls the second procedure directly or indirectly
     * @param caller The calling procedure
     * @param callee The called procedure
     * @return True if the first procedure calls the second procedure directly or indirectly, false otherwise
     */
    bool isCallsStar(Procedure &caller, Procedure &callee) const;

    /**
     * Returns an unordered_set of procedures which is called directly by any other procedure
     * @return An unordered_set of procedures
     */
    EntitySet getCallees() const;

    /**
     * Returns an unordered_set of procedures which is called directly or indirectly by any other procedure
     * @return An unordered_set of procedures
     */
    EntitySet getCalleesStar() const;

    /**
     * Returns an unordered_set of procedures which calls any other procedure directly
     * @return An unordered_set of procedures
     */
    EntitySet getCallers() const;

    /**
     * Returns an unordered_set of procedures which calls any other procedure directly or indirectly
     * @return An unordered_set of procedures
     */
    EntitySet getCallersStar() const;

    /**
     * Returns an unordered_set of Procedure, Procedure pair where the first procedure calls the second procedure
     * DIRECTLY
     * @return An unordered_set of Procedure, Procedure pair stored in a vector
     */
    EntityPairSet getCallsPair() const;

    /**
     * Returns an unordered_set of Procedure, Procedure pair where the first procedure calls the second procedure
     * DIRECTLY or INDIRECTLY
     * @return An unordered_set of Procedure, Procedure pair stored in a vector
     */
    EntityPairSet getCallsStarPair() const;

    /**
     * Returns an unordered_set of procedures which calls the given procedure DIRECTLY
     * @param callee The procedure that is called by the procedures to be retrieved
     * @return An unordered_set of procedures
     */
    EntitySet getCallers(Procedure &callee) const;

    /**
     * Returns an unordered_set of procedures which calls the given procedure DIRECTLY or INDIRECTLY
     * @param callee The procedure that is called by the procedures to be retrieved
     * @return An unordered_set of procedures
     */
    EntitySet getCallersStar(Procedure &callee) const;

    /**
     * Returns an unordered_set of procedures which is called DIRECTLY by the given procedure
     * @param caller The procedure that calls the procedures to be retrieved
     * @return An unordered_set of procedures
     */
    EntitySet getCallees(Procedure &caller) const;

    /**
     * Returns an unordered_set of procedures which is called DIRECTLY or INDIRECTLY by the given procedure
     * @param caller The procedure that calls the procedures to be retrieved
     * @return An unordered_set of procedures
     */
    EntitySet getCalleesStar(Procedure &caller) const;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement is is executed IMMEDIATELY before
     * second statement. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return An unordered_set of Statement, Statement pair stored in a vector
     */
    EntityPairSet getNextPair(StatementType formerType, StatementType latterType) const;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement is executed before of the second
     * statement, either immediately or after some execution sequence. Retrieves the relationship where the first and
     * second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return An unordered_set of Statement, Statement pair stored in a vector
     */
    EntityPairSet getNextStarPair(StatementType formerType, StatementType latterType) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed again after it has been
     * executed
     * @param stmtType The type of statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getNextStarSameStmt(StatementType stmtType) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed IMMEDIATELY before the given
     * statement
     * @param type The type of the statement to be retrieved
     * @param statement The statement that executed IMMEDIATELY after the statements to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getNextTypeStmt(StatementType type, Statement &statement) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed before the given statement,
     * either immediately or after some execution sequence
     * @param type The type of the statement to be retrieved
     * @param statement The statement that is executed after the statements to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getNextStarTypeStmt(StatementType type, Statement &statement) const;

    /**
     * Returns an unordered_set of statements of the given statement type that is executed IMMEDIATELY before any
     * statement
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getNextTypeWildcard(StatementType type) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed before any statement, either
     * immediately or after some execution sequence
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getNextStarTypeWildcard(StatementType type) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed IMMEDIATELY after the given
     * statement
     * @param statement The statement that is executed IMMEDIATELY before the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getNextStmtType(Statement &statement, StatementType type) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed after the given statement,
     * either immediately or after some execution sequence
     * @param statement The statement that is executed after the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getNextStarStmtType(Statement &statement, StatementType type) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed IMMEDIATELY after any
     * statement
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getNextWildcardType(StatementType type) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is executed after any statement, either
     * immediately or after some execution sequence
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getNextStarWildcardType(StatementType type) const;

    /**
     * Returns a boolean value indicating if the first statement is executed IMMEDIATELY before the second statement
     * @param statement1 The parent statement
     * @param statement2 The child statement
     * @return True if the first statement is executed IMMEDIATELY before the second statement, false otherwise
     */
    bool isNext(Statement &statement1, Statement &statement2) const;

    /**
     * Returns a boolean value indicating if the first statement is executed before the second statement, either
     * immediately or after some execution sequence
     * @param statement1 The parent statement
     * @param statement2 The child statement
     * @return True if the first statement is executed before the second statement, false otherwise
     */
    bool isNextStar(Statement &statement1, Statement &statement2) const;

    /**
     * Returns a boolean value indicating if there exists a Next relationship
     * @return True if there exists a Next relationship, false otherwise
     */
    bool hasNext() const;

    /**
     * Returns a boolean value indicating if there exists a Next Star relationship
     * @return True if there exists a Next Star relationship, false otherwise
     */
    bool hasNextStar() const;

    /**
     * Returns a boolean value indicating if the given statement is executed IMMEDIATELY after any statement
     * @param statement The statement to be checked
     * @return True if the given statement is executed IMMEDIATELY after any statement, false otherwise
     */
    bool hasBeforeStmt(Statement &statement) const;

    /**
     * Returns a boolean value indicating if the given statement is executed after any statement, either immediately or
     * after some execution sequence
     * @param statement The statement to be checked
     * @return True if the given statement is executed after any statement, false otherwise
     */
    bool hasBeforeStarStmt(Statement &statement) const;

    /**
     * Returns a boolean value indicating if the given statement is executed IMMEDIATELY before any statement
     * @param statement The statement to be checked
     * @return True if the given statement is executed IMMEDIATELY before any statement, false otherwise
     */
    bool hasAfterStmt(Statement &statement) const;

    /**
     * Returns a boolean value indicating if the given statement is executed before any statement, either immediately or
     * after some execution sequence
     * @param statement The statement to be checked
     * @return True if the given statement is executed before any statement, false otherwise
     */
    bool hasAfterStarStmt(Statement &statement) const;

    /**
     * Returns an unordered_set of If Statements that has variables as control variables
     * @return An unordered_set of Statements
     */
    EntitySet getAllIfPatternStmts() const;

    /**
     * Returns an unordered_set of If Statements with the given variable as a control variable
     * @param var The variable to be checked
     * @return An unordered_set of If Statements
     */
    EntitySet getIfStmtsByVar(Variable &var) const;

    /**
     * Returns an unordered_set of vectors containing If Statement and Variable pairs where the variable is the control
     * variable of the If Statement
     * @return An unordered_set of vectors containing If Statement and Variable pairs
     */
    EntityPairSet getAllIfStmtVarPair() const;

    /**
     * Returns an unordered_set of While Statements that has variables as control variables
     * @return An unordered_set of Statements
     */
    EntitySet getAllWhilePatternStmts() const;

    /**
     * Returns an unordered_set of While Statements with the given variable as a control variable
     * @param var The variable to be checked
     * @return An unordered_set of While Statements
     */
    EntitySet getWhileStmtsByVar(Variable &var) const;

    /**
     * Returns an unordered_set of vectors containing While Statement and Variable pairs where the variable is the
     * control variable of the While Statement
     * @return An unordered_set of vectors containing While Statement and Variable pairs
     */
    EntityPairSet getAllWhileStmtVarPair() const;

    /**
     * Triggers the calculation of the affects relationship
     */
    void triggerAffectsCalculation() const;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement affects the second statement
     * DIRECTLY. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return An unordered_set of Statement, Statement pair stored in a vector
     */
    EntityPairSet getAffectsPair(StatementType formerType, StatementType latterType) const;

    /**
     * Returns an unordered_set of statements of the given statement type which affects itself
     * @param stmtType The type of statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getAffectsSameStmt(StatementType stmtType) const;

    /**
     * Returns an unordered_set of statements of the given statement type which affects the given statement DIRECTLY
     * @param type The type of the statement to be retrieved
     * @param statement The statement that succeeds the statements to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getAffectsTypeStmt(StatementType type, Statement &statement) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is affects any statement DIRECTLY
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getAffectsTypeWildcard(StatementType type) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is affected by the given statement
     * DIRECTLY
     * @param statement The statement that precedes the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getAffectsStmtType(Statement &statement, StatementType type) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is affected by any statement DIRECTLY
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getAffectsWildcardType(StatementType type) const;

    /**
     * Returns true if statement1 DIRECTLY affects statement2, false otherwise
     * @param statement1 The preceding statement
     * @param statement2 The succeeding statement
     * @return True if statement1 directly affects statement2, false otherwise
     */
    bool isAffects(Statement &statement1, Statement &statement2) const;

    /**
     * Returns true if there exists a affects relationship in the PKB, false otherwise
     * @return True if there exists a affects relationship in the PKB, false otherwise
     */
    bool hasAffects() const;

    /**
     * Returns true if there exists a statement that is affected by the given statement, false otherwise i.e. there is a
     * statement in behind of the given statement that is affected by the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that is affected by the given statement, false otherwise
     */
    bool hasAffectedStmt(Statement &statement) const;

    /**
     * Returns true if there exists a statement that affects the given statement, false otherwise i.e. there is a
     * statement in front of the given statement that affects the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that affects the given statement, false otherwise
     */
    bool hasAffectsStmt(Statement &statement) const;
};