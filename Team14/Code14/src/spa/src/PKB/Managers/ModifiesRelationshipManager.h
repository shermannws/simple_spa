#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "PKB/RelationshipStores/ModifiesRelationshipStore.h"
#include "PKB/Managers/AssignmentManager.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "PKB/Relationships/ModifiesRelationship.h"

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
     * Returns true if stmt modifies var, return false otherwise
     */
    bool isStmtModifiesVar(Statement& stmt, Variable& var) const;
};
