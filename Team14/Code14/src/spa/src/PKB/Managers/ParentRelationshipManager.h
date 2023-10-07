#pragma once

#include <memory>
#include <vector>

#include "PKB/RelationshipStores/ParentRelationshipStore.h"
#include "Commons/Entities/Statement.h"
#include "PKB/Managers/StmtToStmtRelationshipManager.h"

/**
 * @class ParentRelationshipManager is responsible for storing and retrieving the Parent relationships
 * between statements.
 * @brief Manages the Parent relationships
 * @note A Parent relationship is a relationship between two statements where the first statement is the parent of the second statement
 */
class ParentRelationshipManager : public StmtToStmtRelationshipManager<ParentRelationshipStore> {
public:
    /**
     * @brief Constructs a ParentRelationshipManager object
     */
    ParentRelationshipManager();

    /**
     * Stores a new Parent relationship into PKB via the Manager
     * @param statement1 The parent statement
     * @param statement2 The child statement
     * @param isDirect A boolean value indicating if a the parent relationship is direct
     */
    void storeParentRelationship(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2, bool isDirect);

    /**
     * Returns a vector of Statement, Statement pair where the first statement is the parent of the second statement. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return A vector of Statement, Statement pair stored in a vector
     */
    std::vector<std::vector<Entity>> getParentPair(StatementType formerType, StatementType latterType, bool requireDirect) const;

    /**
     * Returns a vector of statements of the given statement type which is the parent of the given statement
     * @param type The type of the statement to be retrieved
     * @param statement The statement that is the child of the statements to be retrieved
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return A vector of statements
     */
    std::vector<Entity> getParentTypeStmt(StatementType type, Statement& statement, bool requireDirect) const;

    /**
     * Returns a vector of statements of the given statement type which is the parent of any statement
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getParentTypeWildcard(StatementType type) const;

    /**
     * Returns a vector of statements of the given statement type which is the child of the given statement
     * @param statement The statement that is the parent of the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return A vector of statements
     */
    std::vector<Entity> getParentStmtType(Statement& statement, StatementType type, bool requireDirect) const;

    /**
     * Returns a vector of statements of the given statement type which is the child of any statement
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getParentWildcardType(StatementType type) const;

    /**
     * Returns a boolean value indicating if the first statement is the parent of the second statement
     * @param statement1 The parent statement
     * @param statement2 The child statement
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return True if the first statement is the parent of the second statement, false otherwise
     */
    bool isParent(Statement& statement1, Statement& statement2, bool requireDirect) const;

    /**
     * Returns a boolean value indicating if there exists a Parent relationship
     * @return True if there exists a Parent relationship, false otherwise
     */
    bool hasParent() const;

    /**
     * Returns a boolean value indicating if the given statement is the child of any statement
     * @param statement The statement to be checked
     * @return True if the given statement is the child of any statement, false otherwise
     */
    bool hasParentStmt(Statement& statement) const;

    /**
     * Returns a boolean value indicating if the given statement is the parent of any statement
     * @param statement The statement to be checked
     * @return True if the given statement is the parent of any statement, false otherwise
     */
    bool hasChildStmt(Statement& statement) const;

};
