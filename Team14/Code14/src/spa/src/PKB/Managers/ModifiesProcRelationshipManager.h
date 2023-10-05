#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "ProcToVarRelationshipManager.h"
#include "PKB/RelationshipStores/ModifiesProcRelationshipStore.h"
#include "Commons/Entities/Procedure.h"
#include "Commons/Entities/Variable.h"

/**
 * @class ModifiesProcRelationshipManager is responsible for storing and retrieving the Modifies relationships (Procedure)
 * between procedurs and variables.
 * @brief Manages the Modifies (Procedure) relationships
 * @note A Modifies relationship is a relationship between a procedure and a variable where the procedure modifies the variable
 */
class ModifiesProcRelationshipManager : ProcToVarRelationshipManager<ModifiesProcRelationshipStore> {
public:
    /**
     * @brief Constructs a ModifiesProcRelationshipManager object
     * @return A ModifiesProcRelationshipManager object
     */
    ModifiesProcRelationshipManager();

    /**
     * Stores a new Modifies relationship into PKB via the Manager
     * @param procedure The procedure that modifies the variable
     * @param variable The variable that is modified by the procedure
     */
    void storeModifiesProcRelationship(std::shared_ptr<Procedure> procedure, std::shared_ptr<Variable> variable);

    /**
     * Returns a vector of Procedure, Variable pair where the procedure modifies the variable.
     * @return A vector of Procedure, Variable pair stored in a vector
     */
    std::vector<std::vector<Entity>> getModifiesProcPair() const;

    /**
     * Returns a vector of procedures which modifies the given variable
     * @param var The variable that is modified by the procedures
     * @return A vector of procedures
     */
    std::vector<Entity> getModifiesProcIdent(Variable& var) const;

    /**
     * Returns a vector of procedures which modifies any variable
     * @return A vector of procedures
     */
    std::vector<Entity> getModifiesProc() const;

    /**
     * Returns a vector of variables which is modified by the given procedure
     * @param procedure The procedure that modifies the variables
     * @return A vector of variables
     */
    std::vector<Entity> getModifiesProcVar(Procedure& procedure) const;

    /**
     * Returns a boolean value indicating if the given procedure modifies the given variable
     * @param procedure The procedure that modifies the variable
     * @param var The variable that is modified by the procedure
     * @return A boolean value indicating if the procedure modifies the variable
     */
    bool isProcModifiesVar(Procedure& procedure, Variable& var) const;

    /**
     * Returns a boolean value indicating if the given procedure modifies any variable
     * @param procedure The procedure to be checked
     * @return A boolean value indicating if the procedure modifies any variable
     */
    bool hasProcModifies(Procedure& procedure) const;

    /**
     * Calculates and populate the Modifies (Proc-Var) relationship with the given CallsRelationshipManager
     * @param callManager The CallsRelationshipManager to be used to calculate the Modifies (Proc-Var) relationship
     */
    void calculateModifiesRelationshipForCallers(std::shared_ptr<CallsRelationshipManager> callManager);
};
