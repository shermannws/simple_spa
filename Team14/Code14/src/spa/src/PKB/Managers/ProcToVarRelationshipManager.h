#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "Commons/Entities/Procedure.h"
#include "Commons/Entities/Variable.h"
#include "PKB/Managers/CallsRelationshipManager.h"
#include "PKB/Managers/EntitiesManager.h"
#include "PKB/Managers/ManagerUtils.h"

/**
 * @class ProcToVarRelationshipManager is responsible for storing and retrieving the relationships
 * between procedure and variables.
 * This class is a template class that is inherited by the Relationship Managers
 * @brief Manages the relationships
 * @note A relationship is a relationship between a procedure and a variable
 * @tparam S The type of the relationship store
 */
template<typename S>
class ProcToVarRelationshipManager {
private:
    /**
     * @brief The relationship store
     */
    std::shared_ptr<S> relationshipStore;

public:
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
     * Returns an unordered_set of Procedure, Variable pair where the procedure is related to the variable.
     * @return An unordered_set of Procedure, Variable pair stored in a vector
     */
    std::unordered_set<std::vector<Entity>> getRelationshipProcPair() const;

    /**
     * Returns an unordered_set of procedure which is related to the given variable
     * @param var The variable that is related to the statements
     * @return An unordered_set of procedure
     */
    std::unordered_set<Entity> getRelationshipIdent(Variable &var) const;

    /**
     * Returns an unordered_set of procedures which is related to any variable
     * @return An unordered_set of procedures
     */
    std::unordered_set<Entity> getRelationshipProc() const;

    /**
     * Returns an unordered_set of variables which is related to the given procedure
     * @param procedure The procedure that is related to the variables
     * @return An unordered_set of variables
     */
    std::unordered_set<Entity> getRelationshipVar(Procedure &procedure) const;

    /**
     * Returns a boolean value indicating if the given procedure is related to the given variable
     * @param procedure The procedure that is related to the variable
     * @param var The variable that is related to the procedure
     * @return True if the procedure is related to the variable, else false
     */
    bool isRelationship(Procedure &procedure, Variable &var) const;

    /**
     * Returns a boolean value indicating if the given procedure is related to any variable
     * @param procedure The procedure that is related to the variable
     * @return True if the procedure is related to any variable, else false
     */
    bool hasRelationship(Procedure &procedure) const;

    /**
     * Calculates and populate the ProcToVarRelationship relationshipStore with the given CallsRelationshipManager
     * @param callManager The CallsRelationshipManager
     */
    void calculateProcVarRelationshipForCallers(std::shared_ptr<CallsRelationshipManager> callManager);

    /**
     * Returns an EntityStore of variables which is related to the given procedure
     * @param left The procedure on the left that is related to the variables
     * @returns An EntityStore of variables that is on the right of the given procedure
     */
    std::shared_ptr<EntityStore<Variable>> getRhsVarAsVariables(std::shared_ptr<Procedure> left) const;
};

#include "ProcToVarRelationshipManager.hpp"