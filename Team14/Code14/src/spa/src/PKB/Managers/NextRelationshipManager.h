#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "Commons/Entities/Statement.h"
#include "PKB/Managers/StmtToStmtRelationshipManager.h"
#include "PKB/RelationshipStores/NextRelationshipStore.h"

/**
 * @class NextRelationshipManager is responsible for storing the Next relationship
 * @brief Manages the Next relationship
 * @note: A Next relationship is a relationship between two statements where the second statement is executed after the
 * first statement in some execution sequence
 */
class NextRelationshipManager : public StmtToStmtRelationshipManager<NextRelationshipStore> {
private:
    /**
     * Boolean flag to indicate if Next* relationship has been calculated
     */
    bool mutable isNextStarCalculated;

    /**
     * @brief Calculates the Next* relationship
     */
    void calculateNextStar() const;

public:
    /**
     * @brief Constructs a NextRelationshipManager object
     * @return A NextRelationshipManager object
     */
    NextRelationshipManager();

    /**
     * @brief Get all the statements of the given stmtType that executes after itself in some execution sequence
     * @param stmtType The type of statement to retrieve
     * @return An unordered_set of statements that executes after itself in some execution sequence
     */
    std::unordered_set<Entity> getNextStarSameStmt(StatementType stmtType) const;

    /**
     * Returns an unordered_set of Statement, Statement pair where the first statement is related to the second
     * statement. Retrieves the relationship where the first and second statement are both of the given type
     * @param formerType The type of the former statement
     * @param latterType The type of the latter statement
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return An unordered_set of Statement, Statement pair stored in a vector
     */
    std::unordered_set<std::vector<Entity>> getRelationshipPair(StatementType formerType, StatementType latterType,
                                                                bool requireDirect) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is related to the given statement. The
     * statement given is the latter statement
     * @param type The type of the statement to be retrieved
     * @param statement The statement that is related to the statements to be retrieved
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return An unordered_set of statements
     */
    std::unordered_set<Entity> getRelationshipTypeStmt(StatementType type, Statement &statement,
                                                       bool requireDirect) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is related to any statement. The
     * statements retrieved are the former statements
     * @param type The type of the statement to be retrieved
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return An unordered_set of statements
     */
    std::unordered_set<Entity> getRelationshipTypeWildcard(StatementType type, bool requireDirect) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is related to the given statement. The
     * statement given is the former statement
     * @param statement The statement that is related to the statements to be retrieved
     * @param type The type of the statement to be retrieved
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return An unordered_set of statements
     */
    std::unordered_set<Entity> getRelationshipStmtType(Statement &statement, StatementType type,
                                                       bool requireDirect) const override;

    /**
     * Returns an unordered_set of statements of the given statement type which is related to any statement. The
     * statements retrieved are the latter statements
     * @param type The type of the statement to be retrieved
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return An unordered_set of statements
     */
    std::unordered_set<Entity> getRelationshipWildcardType(StatementType type, bool requireDirect) const override;

    /**
     * Returns true if statement1 is related to statement2, false otherwise
     * @param statement1 The former statement
     * @param statement2 The latter statement
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return True if statement1 is related to statement2, false otherwise
     */
    bool isRelationship(Statement &statement1, Statement &statement2, bool requireDirect) const override;

    /**
     * @brief Clears the Next* relationship store
     */
    void clearNextStarStore();
};
