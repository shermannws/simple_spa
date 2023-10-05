#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include "PKB/RelationshipStores/CallsRelationshipStore.h"
#include "Commons/Entities/Procedure.h"
#include "PKB/Managers/ProcToProcRelationshipManager.h"

/**
 * @class CallsRelationshipManager is responsible for storing and retrieving the Calls relationship
 * @brief Manages the Calls relationship
 * @note: A Calls relationship is a relationship between two procedures where the first procedure cakks the second procedure
 */
class CallsRelationshipManager : ProcToProcRelationshipManager<CallsRelationshipStore> {
public:
    /**
     * @brief Constructs a CallsRelationshipManager object
     * @return A CallsRelationshipManager object
     */
    CallsRelationshipManager();

    /**
     * Stores a new Calls relationship into PKB via the Manager
     * @param procedure1 The calling procedure
     * @param procedure2 The procedure that is called
     * @param isDirect A boolean value indicating if a direct relationship is required
     */
    void storeCallsRelationship(std::shared_ptr<Procedure> procedure1, std::shared_ptr<Procedure> procedure2, bool isDirect);

    /**
     * Returns a vector of Procedure, Procedure pair where the first procedure calls the second procedure.
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return A vector of Procedure, Procedure pair stored in a vector
     */
    std::vector<std::vector<Entity>> getCallsPair(bool requireDirect) const;

    /**
     * Returns a vector of procedures which calls the given procedure i.e. the given procedure is called by the procedure in the vector
     * @param latterProcedure The procedure that is called by the procedures to be retrieved
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return A vector of procedures
     */
    std::vector<Entity> getCallsFormer(Procedure& latterProcedure, bool requireDirect) const;

    /**
     * Returns a vector of procedures which calls any procedure
     * @return A vector of procedures
     */
    std::vector<Entity> getCallsFormer() const;

    /**
     * Returns a vector of procedures which is called by the given procedure i.e. the given procedure is the former Procedure
     * @param formerProcedure The procedure that precedes the procedures to be retrieved
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return A vector of procedures
     */
    std::vector<Entity> getCallsLatter(Procedure& formerProcedure, bool requireDirect) const;

    /**
     * Returns a vector of procedures which is called by any procedure i.e. there exist a procedure before the procedure in the vector
     * @return A vector of procedures
     */
    std::vector<Entity> getCallsLatter() const;

    /**
     * Returns true if procedure1 calls procedure2, false otherwise
     * @param procedure1 The former procedure
     * @param procedure2 The latter procedure
     * @param requireDirect A boolean value indicating if a direct relationship is required
     * @return True if procedure1 calls procedure2, false otherwise
     */
    bool isCalls(Procedure& procedure1, Procedure& procedure2, bool requireDirect) const;

    /**
     * Returns true if there exists a calls relationship in the PKB, false otherwise
     * @return True if there exists a calls relationship in the PKB, false otherwise
     */
    bool hasCalls() const;

    /**
     * Returns true if there exists a procedure that is called by the given procedure, false otherwise i.e. there is a procedure called by the given procedure
     * @param formerProcedure The procedure to be checked
     * @return True if there exists a procedure that is called by the given procedure, false otherwise
     */
    bool hasLatterProc(Procedure& formerProcedure) const;

    /**
     * Returns true if there exists a procedure that calls the given procedure, false otherwise i.e. there is a procedure that calls the given procedure
     * @param latterProcedure The procedure to be checked
     * @return True if there exists a procedure that calls the given procedure, false otherwise
     */
    bool hasFormerProc(Procedure& latterProcedure) const;

    /**
     * Calculates the Calls* relationship and stores it in the PKB.
	 */
    void calculateCallsStar();

    /**
     * Returns a set of procedures which calls the given procedure i.e. the given procedure is called by the procedure in the set
     * @param latterProcedure The procedure that is called by the procedures to be retrieved
     * @return A set of procedures
     */
    std::shared_ptr<EntityStore<Procedure>> getCallsFormerAsProcedure(Procedure& latterProcedure) const;
};
