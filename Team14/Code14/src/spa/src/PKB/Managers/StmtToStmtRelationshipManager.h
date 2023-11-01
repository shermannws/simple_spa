#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "PKB/Commons/ClauseGroup.h"
#include "PKB/Managers/ManagerUtils.h"

/**
 * @class StmtToStmtRelationshipManager is responsible for storing and retrieving the relationships
 * between statements and statements.
 * This class is a template class that is inherited by the Relationship Managers
 */
template<typename S>
class StmtToStmtRelationshipManager {
protected:
    /**
     * @brief The relationship store
     */
    std::shared_ptr<S> relationshipStore;
    std::shared_ptr<S> starRelationshipStore;

public:
    /**
     * @brief The clause group of the relationship
     */
    ClauseGroup clauseGroup;

    /**
     * @brief Constructs a StmtToStmtRelationshipManager object
     * @return A StmtToStmtRelationshipManager object
     */
    StmtToStmtRelationshipManager();

    /**
     * Stores a new relationship into PKB via the Manager
     * @param statement1 The former statement
     * @param statement2 The latter statement
     * @param isDirect A boolean value indicating if the relationship is direct
     */
    void storeRelationship(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2, bool isDirect);

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement is related to the second
     * statement. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return An unordered_set of Statement, Statement pair stored in a vector
     */
    virtual EntityPairSet getRelationshipPair(StatementType formerType, StatementType latterType,
                                              bool requireDirect) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is related to the given statement. The
     * statement given is the latter statement
     * @param type The type of the statement to be retrieved
     * @param statement The statement that is related to the statements to be retrieved
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return An unordered_set of statements
     */
    virtual EntitySet getRelationshipTypeStmt(StatementType type, Statement &statement, bool requireDirect) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is related to any statement. The
     * statements retrieved are the former statements
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getRelationshipTypeWildcard(StatementType type) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is related to any statement. The
     * statements retrieved are the former statements
     * @param type The type of the statement to be retrieved
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return An unordered_set of statements
     */
    virtual EntitySet getRelationshipTypeWildcard(StatementType type, bool requireDirect) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is related to the given statement. The
     * statement given is the former statement
     * @param statement The statement that is related to the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return An unordered_set of statements
     */
    virtual EntitySet getRelationshipStmtType(Statement &statement, StatementType type, bool requireDirect) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is related to any statement. The
     * statements retrieved are the latter statements
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getRelationshipWildcardType(StatementType type) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is related to any statement. The
     * statements retrieved are the latter statements
     * @param type The type of the statement to be retrieved
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return An unordered_set of statements
     */
    virtual EntitySet getRelationshipWildcardType(StatementType type, bool requireDirect) const;

    /**
     * Returns true if statement1 is related to statement2, false otherwise
     * @param statement1 The former statement
     * @param statement2 The latter statement
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return True if statement1 is related to statement2, false otherwise
     */
    virtual bool isRelationship(Statement &statement1, Statement &statement2, bool requireDirect) const;

    /**
     * Returns true if there are any relationships stored, false otherwise
     * @return True if there are any relationships stored, false otherwise
     */
    bool hasRelationship() const;

    /**
     * Returns true if there exists a relationship where the given statement is the former statement, false otherwise
     * @param statement The statement to be checked
     * @return True if there exists a relationship where the given statement is the former statement, false otherwise
     */
    bool isFormer(Statement &statement) const;

    /**
     * Returns true if there exists a relationship where the given statement is the latter statement, false otherwise
     * @param statement The statement to be checked
     * @return True if there exists a relationship where the given statement is the latter statement, false otherwise
     */
    bool isLatter(Statement &statement) const;

    /**
     * @brief Get all the statements of the given stmtType that is related to itself
     * @param stmtType The type of statement to retrieve
     * @return An unordered_set of statements that is related to itself
     */
    EntitySet getSameStmt(StatementType stmtType, bool requireDirect) const;
};

#include "StmtToStmtRelationshipManager.hpp"