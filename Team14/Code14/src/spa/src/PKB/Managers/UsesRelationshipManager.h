#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "PKB/RelationshipStores/UsesRelationshipStore.h"
#include "PKB/Managers/AssignmentManager.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "PKB/Relationships/UsesRelationship.h"
#include "PKB/Managers/StmtToVarRelationshipManager.h"

/**
 * @class UsesRelationshipManager is responsible for storing and retrieving the Uses relationships
 * between statements and variables.
 * @brief Manages the Uses relationships
 * @note A Uses relationship is a relationship between a statement and a variable where the statement uses the variable
 */
class UsesRelationshipManager : StmtToVarRelationshipManager<UsesRelationshipStore, UsesRelationship> {
public:
    /**
     * @brief Constructs a UsesRelationshipManager object
     * @return A UsesRelationshipManager object
     */
    UsesRelationshipManager();

    /**
     * Stores a new Uses relationship into PKB via the Manager
     * @param statement The statement that uses the variable
     * @param variable The variable that is used by the statement
     */
    void storeUsesRelationship(std::shared_ptr<Statement> statement, std::shared_ptr<Variable> variable);

    /**
     * Returns a vector of Statement, Variable pair where the statement uses the variable. Retrieves the relationship where the statement is of the given type
     * @param type The type of the statement
     * @return A vector of Statement, Variable pair stored in a vector
     */
    std::vector<std::vector<Entity>> getUsesStmtPair(StatementType type) const;

    /**
     * Returns a vector of statements of StatementType type which uses the given variable
     * @param type The type of the statement to be retrieved
     * @param var The variable that is used by the statements
     * @return A vector of statements
     */
    std::vector<Entity> getUsesTypeIdent(StatementType type, Variable& var) const;

    /**
     * Returns a vector of statements of the given statement type which uses any variable
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getUsesStmt(StatementType type) const;

    /**
     * Returns a vector of variables which is used by the given statement
     * @param stmt The statement that uses the variables
     * @return A vector of variables
     */
    std::vector<Entity> getUsesVar(Statement& stmt) const;

    /**
     * Returns a boolean value indicating if the given statement uses the given variable
     * @param stmt The statement that uses the variable
     * @param var The variable that is used by the statement
     * @return True if the statement uses the variable, else false
     */
    bool isStmtUsesVar(Statement& stmt, Variable& var) const;

    /**
     * Returns a boolean value indicating if the given statement uses any variable
     * @param stmt The statement that uses the variable
     * @return True if the statement uses any variable, else false
     */
    bool hasUses(Statement& stmt) const;
};
