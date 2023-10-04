#pragma once

#include <memory>

#include "PKB/Managers/EntitiesManager.h"
#include "PKB/Managers/FollowsRelationshipManager.h"
#include "PKB/Managers/UsesRelationshipManager.h"
#include "PKB/Managers/ModifiesRelationshipManager.h"
#include "PKB/Managers/ParentRelationshipManager.h"
#include "PKB/PkbTypes.h"

/**
 * @brief This class is responsible for reading data from PKB.
 */
class PkbReaderManager {
private:
    /**
     * @brief The assignment manager.
     */
    std::shared_ptr<AssignmentManager> assignmentManager;

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
public:
    /**
     * @brief Constructs a PkbReaderManager object.
     * @param assignmentManager The assignment manager.
     * @param entityManager The entities manager.
     * @param followsRelationshipManager The follows relationship manager.
     * @param usesRelationshipManager The uses relationship manager.
     * @param modifiesRelationshipManager The modifies relationship manager.
     * @param parentRelationshipManager The parent relationship manager.
     * @return The PkbReaderManager object.
     */
    PkbReaderManager(
            std::shared_ptr<AssignmentManager> assignmentManager,
            std::shared_ptr<EntitiesManager> entityManager,
            std::shared_ptr<FollowsRelationshipManager> followsRelationshipManager,
            std::shared_ptr<UsesRelationshipManager> usesRelationshipManager,
            std::shared_ptr<ModifiesRelationshipManager> modifiesRelationshipManager,
            std::shared_ptr<ParentRelationshipManager> parentRelationshipManager
    );

    /**
     * @brief Returns all the variables in the SIMPLE program.
     * @return A vector of variables.
     */
    std::vector<Entity> getAllVariables() const;

    /**
     * @brief Returns all the constants in the SIMPLE program.
     * @return A vector of constants.
     */
    std::vector<Entity> getAllConstants() const;

    /**
     * @brief Returns all the procedures in the SIMPLE program.
     * @return A vector of procedures.
     */
    std::vector<Entity> getAllProcedures() const;

    /**
     * @brief Returns all the statements in the SIMPLE program.
     * @return A vector of statements.
     */
    std::vector<Entity> getAllStatements() const;

    /**
     * @brief Returns all the read statements in the SIMPLE program.
     * @return A vector of read statements.
     */
    std::vector<Entity> getAllRead() const;

    /**
     * @brief Returns all the print statements in the SIMPLE program.
     * @return A vector of print statements.
     */
    std::vector<Entity> getAllPrint() const;

    /**
     * @brief Returns all the while statements in the SIMPLE program.
     * @return A vector of while statements.
     */
    std::vector<Entity> getAllWhile() const;

    /**
     * @brief Returns all the if statements in the SIMPLE program.
     * @return A vector of if statements.
     */
    std::vector<Entity> getAllIf() const;

    /**
     * Returns a vector of Statement, Variable pair where the statement uses the variable. Retrieves the relationship where the statement is of the given type
     * @param type The type of the statement
     * @return A vector of Statement, Variable pair stored in a vector
     */
    std::vector<std::vector<Entity>> getUsesStmtPair(StatementType type) const;

    /**
     * Returns a vector of Procedure, Variable pair where the procedure uses the variable.
     * @return A vector of Procedure, Variable pair stored in a vector
     */
    std::vector<std::vector<Entity>> getUsesProcPair() const;

    /**
     * Returns a vector of statements of StatementType type which uses the given variable
     * @param type The type of the statement to be retrieved
     * @param var The variable that is used by the statements
     * @return A vector of statements
    */
    std::vector<Entity> getUsesTypeIdent(StatementType type, Variable& var) const;

    /**
     * Returns a vector of procedures which uses the given variable
     * @param var The variable that is used by the statements
     * @return A vector of procedures
    */
    std::vector<Entity> getUsesProcIdent(Variable& var) const;

    /**
     * Returns a vector of statements of the given statement type which uses any variable
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getUsesStmt(StatementType type) const;

    /**
     * Returns a vector of procedures which uses any variable
     * @return A vector of procedures
     */
    std::vector<Entity> getUsesProc() const;

    /**
     * Returns a vector of variables which is used by the given statement
     * @param stmt The statement that uses the variables
     * @return A vector of variables
     */
    std::vector<Entity> getUsesVar(Statement& stmt) const;

    /**
     * Returns a vector of variables which is used by the given procedure
     * @param proc The procedure that uses the variables
     * @return A vector of variables
     */
    std::vector<Entity> getUsesVar(Procedure& proc) const;

    /**
     * Returns a boolean value indicating if the given statement uses the given variable
     * @param stmt The statement that uses the variable
     * @param var The variable that is used by the statement
     * @return True if the statement uses the variable, else false
     */
    bool isStmtUsesVar(Statement& stmt, Variable& var) const;

    /**
     * Returns a boolean value indicating if the given procedure uses the given variable
     * @param proc The procedure that uses the variable
     * @param var The variable that is used by the procedure
     * @return True if the procedure uses the variable, else false
     */
    bool isProcUsesVar(Procedure& proc, Variable& var) const;

    /**
     * Returns a boolean value indicating if the given statement uses any variable
     * @param stmt The statement that uses the variable
     * @return True if the statement uses any variable, else false
     */
    bool hasUses(Statement& stmt) const;

    /**
     * Returns a boolean value indicating if the given procedure uses any variable
     * @param proc The procedure to check
     * @return True if the statement uses any variable, else false
     */
    bool hasUses(Procedure& proc) const;

    /**
     * Returns a vector of Statement, Statement pair where the first statement follows the second statement DIRECTLY. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return A vector of Statement, Statement pair stored in a vector
     */
    std::vector<std::vector<Entity>> getFollowsPair(StatementType formerType, StatementType latterType) const;

    /**
     * Returns a vector of Statement, Statement pair where the first statement follows the second statement DIRECTLY or INDIRECTLY. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return A vector of Statement, Statement pair stored in a vector
     */
    std::vector<std::vector<Entity>> getFollowsStarPair(StatementType formerType, StatementType latterType) const;

    /**
     * Returns a vector of statements of the given statement type which is followed by the given statement DIRECTLY i.e. the given statement is directly after the statement in the vector
     * @param type The type of the statement to be retrieved
     * @param statement The statement that succeeds the statements to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getFollowsTypeStmt(StatementType type, Statement& statement) const;

    /**
     * Returns a vector of statements of the given statement type which is followed by the given statement DIRECTLY or INDIRECTLY i.e. the given statement is directly or indirectly after the statement in the vector
     * @param type The type of the statement to be retrieved
     * @param statement The statement that succeeds the statements to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getFollowsStarTypeStmt(StatementType type, Statement& statement) const;

    /**
     * Returns a vector of statements of the given statement type which is followed by any statement i.e. there exist a statement after the statement in the vector
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getFollowsTypeWildcard(StatementType type) const;

    /**
     * Returns a vector of statements of the given statement type which is followed by any statement i.e. there exist a statement after the statement in the vector
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getFollowsStarTypeWildcard(StatementType type) const;

    /**
     * Returns a vector of statements of the given statement type which follows the given statement DIRECTLY i.e. the given statement is directly before the statement in the vector
     * @param statement The statement that precedes the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getFollowsStmtType(Statement& statement, StatementType type) const;

    /**
     * Returns a vector of statements of the given statement type which follows the given statement DIRECTLY or INDIRECTLY i.e. the given statement is directly or indirectly before the statement in the vector
     * @param statement The statement that precedes the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getFollowsStarStmtType(Statement& statement, StatementType type) const;

    /**
     * Returns a vector of statements of the given statement type which follows any statement i.e. there exist a statement before the statement in the vector
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getFollowsWildcardType(StatementType type) const;

    /**
     * Returns a vector of statements of the given statement type which follows any statement i.e. there exist a statement before the statement in the vector
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getFollowsStarWildcardType(StatementType type) const;

    /**
     * Returns true if statement1 DIRECTLY precedes statement2, false otherwise
     * @param statement1 The preceding statement
     * @param statement2 The succeeding statement
     * @return True if statement1 directly precedes statement2, false otherwise
     */
    bool isFollows(Statement& statement1, Statement& statement2) const;

    /**
     * Returns true if statement1 DIRECTLY or INDIRECTLY precedes statement2, false otherwise
     * @param statement1 The preceding statement
     * @param statement2 The succeeding statement
     * @return True if statement1 directly or indirectly precedes statement2, false otherwise
     */
    bool isFollowsStar(Statement& statement1, Statement& statement2) const;

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
     * Returns true if there exists a statement that succeeds the given statement, false otherwise i.e. there is a statement behind the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that succeeds the given statement, false otherwise
     */
    bool hasLatterStmt(Statement& statement) const;

    /**
     * Returns true if there exists a statement that precedes the given statement, false otherwise i.e. there is a statement in front of the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that precedes the given statement, false otherwise
     */
    bool hasFormerStmt(Statement& statement) const;

    /**
     * Returns true if there exists a statement that succeeds the given statement, false otherwise i.e. there is a statement behind the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that succeeds the given statement, false otherwise
     */
    bool hasLatterStarStmt(Statement& statement) const;

    /**
     * Returns true if there exists a statement that precedes the given statement, false otherwise i.e. there is a statement in front of the given statement
     * @param statement The statement to be checked
     * @return True if there exists a statement that precedes the given statement, false otherwise
     */
    bool hasFormerStarStmt(Statement& statement) const;

    /**
     * Returns a vector of Statement, Variable pair where the statement modifies the variable. Retrieves the relationship where the statement is of the given type
     * @param type The type of the statement
     * @return A vector of Statement, Variable pair stored in a vector
     */
    std::vector<std::vector<Entity>> getModifiesStmtPair(StatementType type) const;

    /**
    * Returns a vector of Procedure, Variable pair where the procedure modifies the variable.
    * @return A vector of Procedure, Variable pair stored in a vector
    */
    std::vector<std::vector<Entity>> getModifiesProcPair() const;

    /**
     * Returns a vector of statements of StatementType type which modifies the given variable
     * @param type The type of the statement to be retrieved
     * @param var The variable that is modified by the statements
     * @return A vector of statements
     */
    std::vector<Entity> getModifiesTypeIdent(StatementType type, Variable& var) const;

    /**
     * Returns a vector of procedures which modifies the given variable
     * @param var The variable that is modified by the procedure
     * @return A vector of procedures
     */
    std::vector<Entity> getModifiesProcIdent(Variable& var) const;

    /**
     * Returns a vector of statements of the given statement type which modifies any variable
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getModifiesStmt(StatementType type) const;

    /**
     * Returns a vector of procedures which modifies any variable
     * @return A vector of procedures
     */
    std::vector<Entity> getModifiesProc() const;

    /**
     * Returns a vector of variables which is modified by the given statement
     * @param stmt The statement that modifies the variables
     * @return A vector of variables
     * @note The vector will only contain one variable
     */
    std::vector<Entity> getModifiesVar(Statement& stmt) const;

    /**
     * Returns a vector of variables which is modified by the given procedure
     * @param proc The procedure that modifies the variables
     * @return A vector of variables
     */
    std::vector<Entity> getModifiesVar(Procedure& proc) const;

    /**
     * Returns a boolean value indicating if the given statement modifies the given variable
     * @param stmt The statement that modifies the variable
     * @param var The variable that is modified by the statement
     * @return A boolean value indicating if the statement modifies the variable
     */
    bool isStmtModifiesVar(Statement& stmt, Variable& var) const;

    /**
     * Returns a boolean value indicating if the given procedure modifies the given variable
     * @param proc The procedure that modifies the variable
     * @param var The variable that is modified by the procedure
     * @return A boolean value indicating if the procedure modifies the variable
     */
    bool isProcModifiesVar(Procedure& proc, Variable& var) const;

    /**
     * Returns a boolean value indicating if the given statement modifies any variable
     * @param stmt The statement to be checked
     * @return A boolean value indicating if the statement modifies any variable
     */
    bool hasModifies(Statement& stmt) const;

    /**
     * Returns a boolean value indicating if the given procedure modifies any variable
     * @param stmt The procedure to be checked
     * @return A boolean value indicating if the procedure modifies any variable
     */
    bool hasModifies(Procedure& proc) const;

    /**
     * Returns a vector of Statements from all the Assignment objects in the store. Represents all the Statements that are assignments
     * @return A vector of all the Statement objects
     * @note Used for `pattern a (_,_)`
     */
    std::vector<Entity> getAllAssign() const;

    /**
     * Returns a vector of Statement objects from Assignment objects in the store with Expressions that match the given pattern. Represents all the statements that are assignments with Expressions that match the given pattern
     * @param rhs The pattern to be matched against the Expressions
     * @param hasRhsWildCard A boolean value indicating if the pattern has a wildcard
     * @return A vector of Statement objects
     * @note Used for `pattern a (_, "x")`
     */
    std::vector<Entity> getAssignStmtsByRhs(Expression& rhs, bool hasRhsWildCard) const;

    /**
     * Returns a vector of vectors containing Statement and Variable pairs from all the Assignment objects in the store
     * @return A vector of vectors containing Statement and Variable pairs
     * @note Used for `pattern a (v, _)`
     */
    std::vector<std::vector<Entity>> getAllAssignStmtVarPair() const;

    /**
     * Returns a vector of vectors containing Statement and Variable pairs from the Assignment objects in the store with the Expression matching the given pattern
     * @param rhs The pattern to be matched against the Expressions
     * @param hasWildCard A boolean value indicating if the pattern has a wildcard
     * @return A vector of vectors containing Statement and Variable pairs
     * @note Used for `pattern a (v, "x")`
     */
    std::vector<std::vector<Entity>> getAssignStmtsVarPairByRhs(Expression& rhs, bool hasWildCard) const;

    /**
     * Returns a vector of Statement objects from Assignment objects in the store where the Variable that is assigned matches the given Variable.
     * @param lhs The Variable to be matched against
     * @return A vector of Statement objects
     * @note Used for `pattern a ("x", _)`
     */
    std::vector<Entity> getAssignStmtsByLhs(Variable& lhs) const;

    /**
     * Returns a vector of Statement objects from Assignment objects in the store where the Variable that is assigned matches the given Variable and the Expression matches the given pattern.
     * @param lhs The Variable to be matched against
     * @param rhs The pattern to be matched against the Expressions
     * @param hasRhsWildCard A boolean value indicating if the pattern has a wildcard
     * @return A vector of Statement objects
     * @note Used for `pattern a ("x", "x")`
     */
    std::vector<Entity> getAssignStmtsByLhsRhs(Variable& lhs, Expression& rhs, bool hasRhsWildCard) const;

    /**
     * Returns a vector of Statement, Statement pair where the first statement is the DIRECT parent of the second statement. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return A vector of Statement, Statement pair stored in a vector
     */
    std::vector<std::vector<Entity>> getParentPair(StatementType formerType, StatementType latterType) const;

    /**
     * Returns a vector of Statement, Statement pair where the first statement is the DIRECT or INDIRECT parent of the second statement. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @return A vector of Statement, Statement pair stored in a vector
     */
    std::vector<std::vector<Entity>> getParentStarPair(StatementType formerType, StatementType latterType) const;

    /**
     * Returns a vector of statements of the given statement type which is the DIRECT parent of the given statement
     * @param type The type of the statement to be retrieved
     * @param statement The statement that is the direct child of the statements to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getParentTypeStmt(StatementType type, Statement& statement) const;

    /**
     * Returns a vector of statements of the given statement type which is the DIRECT or INDIRECT parent of the given statement
     * @param type The type of the statement to be retrieved
     * @param statement The statement that is the direct or indirect child of the statements to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getParentStarTypeStmt(StatementType type, Statement& statement) const;

    /**
     * Returns a vector of statements of the given statement type which is the direct parent of any statement
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getParentTypeWildcard(StatementType type) const;

    /**
     * Returns a vector of statements of the given statement type which is the direct or indirect parent of any statement
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getParentStarTypeWildcard(StatementType type) const;

    /**
     * Returns a vector of statements of the given statement type which is the DIRECT child of the given statement
     * @param statement The statement that is the direct parent of the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getParentStmtType(Statement& statement, StatementType type) const;

    /**
     * Returns a vector of statements of the given statement type which is the DIRECT or INDIRECT child of the given statement
     * @param statement The statement that is the direct or indirect parent of the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getParentStarStmtType(Statement& statement, StatementType type) const;

    /**
     * Returns a vector of statements of the given statement type which is the direct child of any statement
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getParentWildcardType(StatementType type) const;

    /**
     * Returns a vector of statements of the given statement type which is the direct or indirect child of any statement
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getParentStarWildcardType(StatementType type) const;

    /**
     * Returns a boolean value indicating if the first statement is the DIRECT parent of the second statement
     * @param statement1 The parent statement
     * @param statement2 The child statement
     * @return True if the first statement is the direct parent of the second statement, false otherwise
     */
    bool isParent(Statement& statement1, Statement& statement2) const;

    /**
     * Returns a boolean value indicating if the first statement is the DIRECT or INDIRECT parent of the second statement
     * @param statement1 The parent statement
     * @param statement2 The child statement
     * @return True if the first statement is the direct or indirect parent of the second statement, false otherwise
     */
    bool isParentStar(Statement& statement1, Statement& statement2) const;

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
    bool hasParentStmt(Statement& statement) const;

    /**
     * Returns a boolean value indicating if the given statement is the direct or indirect child of any statement
     * @param statement The statement to be checked
     * @return True if the given statement is the child of any statement, false otherwise
     */
    bool hasParentStarStmt(Statement& statement) const;

    /**
     * Returns a boolean value indicating if the given statement is the direct parent of any statement
     * @param statement The statement to be checked
     * @return True if the given statement is the parent of any statement, false otherwise
     */
    bool hasChildStmt(Statement& statement) const;

    /**
     * Returns a boolean value indicating if the given statement is the direct or indirect parent of any statement
     * @param statement The statement to be checked
     * @return True if the given statement is the parent of any statement, false otherwise
     */
    bool hasChildStarStmt(Statement& statement) const;

};