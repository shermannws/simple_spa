#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "ProcToVarRelationshipManager.h"
#include "PKB/RelationshipStores/MapStores/UsesProcRelationshipStore.h"
#include "Commons/Entities/Procedure.h"
#include "Commons/Entities/Variable.h"

/**
 * @class UsesProcRelationshipManager is responsible for storing and retrieving the Uses relationships (Procedure)
 * between procedurs and variables.
 * @brief Manages the Uses (Procedure) relationships
 * @note A Uses relationship is a relationship between a procedure and a variable where the procedure uses the variable
 */
class UsesProcRelationshipManager : ProcToVarRelationshipManager<UsesProcRelationshipStore> {
public:
    /**
     * @brief Constructs a UsesProcRelationshipManager object
     * @return A UsesProcRelationshipManager object
     */
    UsesProcRelationshipManager();

    /**
     * Stores a new Uses relationship into PKB via the Manager
     * @param procedure The procedure that uses the variable
     * @param variable The variable that is modified by the procedure
     */
    void storeUsesProcRelationship(std::shared_ptr<Procedure> procedure, std::shared_ptr<Variable> variable);

    /**
     * Returns a vector of Procedure, Variable pair where the procedure uses the variable.
     * @return A vector of Procedure, Variable pair stored in a vector
     */
    std::vector<std::vector<Entity>> getUsesProcPair() const;

    /**
     * Returns a vector of procedures which uses the given variable
     * @param var The variable that is modified by the procedures
     * @return A vector of procedures
     */
    std::vector<Entity> getUsesProcIdent(Variable& var) const;

    /**
     * Returns a vector of procedures which uses any variable
     * @return A vector of procedures
     */
    std::vector<Entity> getUsesProc() const;

    /**
     * Returns a vector of variables which is modified by the given procedure
     * @param procedure The procedure that uses the variables
     * @return A vector of variables
     */
    std::vector<Entity> getUsesProcVar(Procedure& procedure) const;

    /**
     * Returns a boolean value indicating if the given procedure uses the given variable
     * @param procedure The procedure that uses the variable
     * @param var The variable that is modified by the procedure
     * @return A boolean value indicating if the procedure uses the variable
     */
    bool isProcUsesVar(Procedure& procedure, Variable& var) const;

    /**
     * Returns a boolean value indicating if the given procedure uses any variable
     * @param procedure The procedure to be checked
     * @return A boolean value indicating if the procedure uses any variable
     */
    bool hasProcUses(Procedure& procedure) const;
};
