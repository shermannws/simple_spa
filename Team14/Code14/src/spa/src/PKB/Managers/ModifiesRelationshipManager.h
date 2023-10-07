#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "PKB/RelationshipStores/ModifiesRelationshipStore.h"
#include "PKB/Managers/AssignmentManager.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "PKB/Managers/StmtToVarRelationshipManager.h"

/**
 * @class ModifiesRelationshipManager is responsible for storing and retrieving the Modifies relationships
 * between statements and variables.
 * @brief Manages the Modifies relationships
 * @note A Modifies relationship is a relationship between a statement and a variable where the statement modifies the variable
 */
class ModifiesRelationshipManager : StmtToVarRelationshipManager<ModifiesRelationshipStore> {
public:
    /**
     * @brief Constructs a ModifiesRelationshipManager object
     * @return A ModifiesRelationshipManager object
     */
    ModifiesRelationshipManager();

    /**
     * Stores a new Modifies relationship into PKB via the Manager
     * @param statement The statement that modifies the variable
     * @param variable The variable that is modified by the statement
     */
    void storeModifiesRelationship(std::shared_ptr<Statement> statement, std::shared_ptr<Variable> variable);

    /**
     * Returns a vector of Statement, Variable pair where the statement modifies the variable. Retrieves the relationship where the statement is of the given type
     * @param type The type of the statement
     * @return A vector of Statement, Variable pair stored in a vector
     */
    std::vector<std::vector<Entity>> getModifiesStmtPair(StatementType type) const;

    /**
     * Returns a vector of statements of StatementType type which modifies the given variable
     * @param type The type of the statement to be retrieved
     * @param var The variable that is modified by the statements
     * @return A vector of statements
     */
    std::vector<Entity> getModifiesTypeIdent(StatementType type, Variable& var) const;

    /**
     * Returns a vector of statements of the given statement type which modifies any variable
     * @param type The type of the statement to be retrieved
     * @return A vector of statements
     */
    std::vector<Entity> getModifiesStmt(StatementType type) const;

    /**
     * Returns a vector of variables which is modified by the given statement
     * @param stmt The statement that modifies the variables
     * @return A vector of variables
     * @note The vector will only contain one variable
     */
    std::vector<Entity> getModifiesVar(Statement& stmt) const;

    /**
     * Returns a boolean value indicating if the given statement modifies the given variable
     * @param stmt The statement that modifies the variable
     * @param var The variable that is modified by the statement
     * @return A boolean value indicating if the statement modifies the variable
     */
    bool isStmtModifiesVar(Statement& stmt, Variable& var) const;

    /**
     * Returns a boolean value indicating if the given statement modifies any variable
     * @param stmt The statement to be checked
     * @return A boolean value indicating if the statement modifies any variable
     */
    bool hasModifies(Statement& stmt) const;
};
