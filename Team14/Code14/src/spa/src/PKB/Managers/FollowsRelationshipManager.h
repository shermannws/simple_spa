#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include "PKB/RelationshipStores/FollowsRelationshipStore.h"
#include "Commons/Entities/Statement.h"
#include "PKB/Relationships/FollowsRelationship.h"
#include "PKB/Managers/StmtToStmtRelationshipManager.h"

/**
 * @class FollowsRelationshipManager is responsible for storing the Follows relationship
 * @brief Manages the Follows relationship
 * @note: A Follows relationship is a relationship between two statements where the first statement is executed before the second statement
 */
class FollowsRelationshipManager : StmtToStmtRelationshipManager<FollowsRelationshipStore, FollowsRelationship> {
public:
    /**
     * @brief Constructs a FollowsRelationshipManager object
     * @return A FollowsRelationshipManager object
     */
    FollowsRelationshipManager();

    /**
     * Stores a new Follows relationship into PKB via the Manager
     * @param statement1 The preceding statement
     * @param statement2 The succeeding statement
     * @param isDirect A boolean value indicating if a direct relationship is required
     */
    void storeFollowsRelationship(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2, bool isDirect);

    /**
     * Returns a vector of Statement, Statement pair where the first statement follows the second statement. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return A vector of Statement, Statement pair stored in a vector
     */
    std::vector<std::vector<Entity>> getFollowsPair(StatementType formerType, StatementType latterType, bool requireDirect) const;

    /**
     * Returns a vector of statements of the given statement type which is followed by the given statement i.e. the given statement is after the statement in the vector
     * @param type The type of the statement to be retrieved
     * @param statement The statement that succeeds the statements to be retrieved
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return A vector of statements
     */
    std::vector<Entity> getFollowsTypeStmt(StatementType type, Statement& statement, bool requireDirect) const;

    /**
     * Returns a vector of statements of the given statement type which is followed by any statement i.e. there exist a statement after the statement in the vector
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getFollowsTypeWildcard(StatementType type) const;

    /**
     * Returns a vector of statements of the given statement type which follows the given statement i.e. the given statement is before the statement in the vector
     * @param statement The statement that precedes the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return A vector of statements
     */
    std::vector<Entity> getFollowsStmtType(Statement& statement, StatementType type, bool requireDirect) const;

    /**
     * Returns a vector of statements of the given statement type which follows any statement i.e. there exist a statement before the statement in the vector
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getFollowsWildcardType(StatementType type) const;

    /**
     * Returns true if statement1 precedes statement2, false otherwise
     * @param statement1 The preceding statement
     * @param statement2 The succeeding statement
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return True if statement1 precedes statement2, false otherwise
     */
    bool isFollows(Statement& statement1, Statement& statement2, bool requireDirect) const;

    /**
     * Returns true if there exists a follows relationship in the PKB, false otherwise
     * @return True if there exists a follows relationship in the PKB, false otherwise
     */
    bool hasFollows() const;

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
};
