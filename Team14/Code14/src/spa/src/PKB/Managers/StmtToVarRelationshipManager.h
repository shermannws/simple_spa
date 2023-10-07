#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include "PKB/Managers/ManagerUtils.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"

/**
 * @class StmtToVarRelationshipManager is responsible for storing and retrieving the relationships
 * between statements and variables.
 * This class is a template class that is inherited by the Relationship Managers
 * @brief Manages the relationships
 * @note A relationship is a relationship between a statement and a variable
 */
template <typename S>
class StmtToVarRelationshipManager {
private:
    /**
     * @brief The relationship store
     */
    std::shared_ptr<S> relationshipStore;
protected:
    /**
     * @brief Constructs a StmtToVarRelationshipManager object
     * @return A StmtToVarRelationshipManager object
     */
    StmtToVarRelationshipManager();

    /**
     * Stores a new relationship into PKB via the Manager
     * @param statement The statement that is related to the variable
     * @param variable The variable that is related to the statement
     */
    void storeRelationship(std::shared_ptr<Statement> statement, std::shared_ptr<Variable> variable);

    /**
     * Returns a vector of Statement, Variable pair where the statement is related to the variable. Retrieves the relationship where the statement is of the given type
     * @param type The type of the statement
     * @return A vector of Statement, Variable pair stored in a vector
     */
    std::vector<std::vector<Entity>> getRelationshipStmtPair(StatementType type) const;

    /**
     * Returns a vector of statements of StatementType type which is related to the given variable
     * @param type The type of the statement to be retrieved
     * @param var The variable that is related to the statements
     * @return A vector of statements
     */
    std::vector<Entity> getRelationshipTypeIdent(StatementType type, Variable& var) const;

    /**
     * Returns a vector of statements of the given statement type which is related to any variable
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getRelationshipStmt(StatementType type) const;

    /**
     * Returns a vector of variables which is related to the given statement
     * @param stmt The statement that is related to the variables
     * @return A vector of variables
     */
    std::vector<Entity> getRelationshipVar(Statement& stmt) const;

    /**
     * Returns a boolean value indicating if the given statement is related to the given variable
     * @param stmt The statement that is related to the variable
     * @param var The variable that is related to the statement
     * @return True if the statement is related to the variable, else false
     */
    bool isRelationship(Statement& stmt, Variable& var) const;

    /**
     * Returns a boolean value indicating if the given statement is related to any variable
     * @param stmt The statement that is related to the variable
     * @return True if the statement is related to any variable, else false
     */
    bool hasRelationship(Statement& stmt) const;
};

#include "StmtToVarRelationshipManager.hpp"