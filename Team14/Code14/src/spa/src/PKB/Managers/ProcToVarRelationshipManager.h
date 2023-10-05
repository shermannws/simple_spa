#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include "PKB/Managers/ManagerUtils.h"
#include "PKB/Managers/EntitiesManager.h"
#include "Commons/Entities/Procedure.h"
#include "Commons/Entities/Variable.h"

/**
 * @class ProcToVarRelationshipManager is responsible for storing and retrieving the relationships
 * between procedure and variables.
 * This class is a template class that is inherited by the Relationship Managers
 * @brief Manages the relationships
 * @note A relationship is a relationship between a procedure and a variable
 * @tparam S The type of the relationship store
 */
template <typename S>
class ProcToVarRelationshipManager {
private:
    /**
     * @brief The relationship store
     */
    std::shared_ptr<S> relationshipStore;
protected:
    /**
     * @brief Constructs a ProcToVarRelationshipManager object
     * @return A StmtToVarRelationshipManager object
     */
    ProcToVarRelationshipManager();

    /**
     * Stores a new relationship into PKB via the Manager
     * @param procedure The procedure that is related to the variable
     * @param variable The variable that is related to the procedure
     */
    void storeRelationship(std::shared_ptr<Procedure> procedure, std::shared_ptr<Variable> variable);

    /**
     * Returns a vector of Procedure, Variable pair where the procedure is related to the variable.
     * @return A vector of Procedure, Variable pair stored in a vector
     */
    std::vector<std::vector<Entity>> getRelationshipProcPair() const;

    /**
     * Returns a vector of procedure which is related to the given variable
     * @param var The variable that is related to the statements
     * @return A vector of procedure
     */
    std::vector<Entity> getRelationshipIdent(Variable& var) const;

    /**
     * Returns a vector of procedures which is related to any variable
     * @return A vector of procedures
     */
    std::vector<Entity> getRelationshipProc() const;

    /**
     * Returns a vector of variables which is related to the given procedure
     * @param procedure The procedure that is related to the variables
     * @return A vector of variables
     */
    std::vector<Entity> getRelationshipVar(Procedure& procedure) const;

    /**
     * Returns a boolean value indicating if the given procedure is related to the given variable
     * @param procedure The procedure that is related to the variable
     * @param var The variable that is related to the procedure
     * @return True if the procedure is related to the variable, else false
     */
    bool isRelationship(Procedure& procedure, Variable& var) const;

    /**
     * Returns a boolean value indicating if the given procedure is related to any variable
     * @param procedure The procedure that is related to the variable
     * @return True if the procedure is related to any variable, else false
     */
    bool hasRelationship(Procedure& procedure) const;
};

#include "ProcToVarRelationshipManager.hpp"