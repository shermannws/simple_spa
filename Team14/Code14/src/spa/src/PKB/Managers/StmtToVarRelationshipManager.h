#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "PKB/Commons/ClauseGroup.h"
#include "PKB/Managers/ManagerUtils.h"

/**
 * @class StmtToVarRelationshipManager is responsible for storing and retrieving the relationships
 * between statements and variables.
 * This class is a template class that is inherited by the Relationship Managers
 * @brief Manages the relationships
 * @note A relationship is a relationship between a statement and a variable
 */
template<typename S>
class StmtToVarRelationshipManager {
protected:
    /**
     * @brief The relationship store
     */
    std::shared_ptr<S> relationshipStore;

    /**
     * @brief The clause group of the relationship
     */
    ClauseGroup clauseGroup;

public:
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
     * Returns an unordered_set of Statement, Variable pair where the statement is related to the variable. Retrieves
     * the relationship where the statement is of the given type
     * @param type The type of the statement
     * @return An unordered_set of Statement, Variable pair stored in a vector
     */
    EntityPairSet getRelationshipStmtPair(StatementType type) const;

    /**
     * Returns an unordered_set of statements of StatementType type which is related to the given variable
     * @param type The type of the statement to be retrieved
     * @param var The variable that is related to the statements
     * @return An unordered_set of statements
     */
    EntitySet getRelationshipTypeIdent(StatementType type, Variable &var) const;

    /**
     * Returns an unordered_set of statements of the given statement type which is related to any variable
     * @param type The type of the statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getRelationshipStmt(StatementType type) const;

    /**
     * Returns an unordered_set of variables which is related to the given statement
     * @param stmt The statement that is related to the variables
     * @return An unordered_set of variables
     */
    EntitySet getRelationshipVar(Statement &stmt) const;

    /**
     * Returns a boolean value indicating if the given statement is related to the given variable
     * @param stmt The statement that is related to the variable
     * @param var The variable that is related to the statement
     * @return True if the statement is related to the variable, else false
     */
    bool isRelationship(Statement &stmt, Variable &var) const;

    /**
     * Returns a boolean value indicating if the given statement is related to any variable
     * @param stmt The statement that is related to the variable
     * @return True if the statement is related to any variable, else false
     */
    bool hasRelationship(Statement &stmt) const;
};

#include "StmtToVarRelationshipManager.hpp"