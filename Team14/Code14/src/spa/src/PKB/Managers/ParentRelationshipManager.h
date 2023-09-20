#pragma once

#include <memory>
#include <vector>

#include "PKB/RelationshipStores/ParentRelationshipStore.h"
#include "Commons/Entities/Statement.h"
#include "PKB/Relationships/ParentRelationship.h"

class ParentRelationshipManager {
private:
    std::shared_ptr<ParentRelationshipStore> parentRelationshipStore;
public:
    /*!
     * Constructor for ParentRelationshipManager
     */
    ParentRelationshipManager();

    /*!
     * Stores ParentRelationship into PKB via the Manager
     */
    void storeParentRelationship(std::shared_ptr<Statement> parentStatement, std::shared_ptr<Statement> childStatement, bool isDirect);

    /*!
     * Returns true if statement1 is direct parent of statement2 when requireDirect is true, return false otherwise
     * Returns true if statement1 is indirect parent of statement2 when requireDirect is false, return false otherwise
     */
    bool isParent(Statement& statement1, Statement& statement2, bool requireDirect) const;
};
