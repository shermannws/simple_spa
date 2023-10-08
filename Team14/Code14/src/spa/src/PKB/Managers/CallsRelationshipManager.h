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
class CallsRelationshipManager : public ProcToProcRelationshipManager<CallsRelationshipStore> {
public:
    /**
     * @brief Constructs a CallsRelationshipManager object
     * @return A CallsRelationshipManager object
     */
    CallsRelationshipManager();

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
