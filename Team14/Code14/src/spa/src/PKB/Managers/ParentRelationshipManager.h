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
    void storeParentRelationship(std::shared_ptr<Statement> parentStatement, std::shared_ptr<Statement> childStatement);
};
