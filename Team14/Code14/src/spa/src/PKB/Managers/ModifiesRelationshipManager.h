#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "PKB/RelationshipStores/ModifiesRelationshipStore.h"
#include "PKB/Managers/AssignmentManager.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "PKB/Relationships/ModifiesRelationship.h"
#include "PKB/Managers/ManagerUtils.h"

class ModifiesRelationshipManager {
private:
    std::shared_ptr<ModifiesRelationshipStore> modifiesRelationshipStore;
public:
    /*!
     * Constructor for ModifiesRelationshipManager
     */
    ModifiesRelationshipManager();

    /*!
     * Stores a new modifies relationship into PKB via the Manager
     */
    void storeModifiesRelationship(std::shared_ptr<Statement> statement, std::shared_ptr<Variable> variable);

    /*!
     * Returns a vector of Statement, Variable pair where the statement modifies the variable
     */
    std::vector<std::vector<Entity>> getModifiesStmtPair(StatementType type) const;

    /*!
     * Returns a vector of statements of the given statement type which modifies the given variable
     */
    std::vector<Entity> getModifiesTypeIdent(StatementType type, Variable& var) const;

    /*!
     * Returns a vector of statements of the given statement type which modifies any variable
     */
    std::vector<Entity> getModifiesStmt(StatementType type) const;

    /*!
     * Returns a vector of variables which are modified by the given statement
     */
    std::vector<Entity> getModifiesVar(Statement& stmt) const;

    /*!
     * Returns a boolean value indicating if the given statement modifies the given variable
     */
    bool isStmtModifiesVar(Statement& stmt, Variable& var) const;

    /*!
     * Returns a boolean value indicating if there are any modifies relationships for the statement
     */
    bool hasModifies(Statement& stmt) const;
};
