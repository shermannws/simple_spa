#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include "PKB/RelationshipStores/NextRelationshipStore.h"
#include "Commons/Entities/Statement.h"
#include "PKB/Managers/StmtToStmtRelationshipManager.h"

/**
 * @class NextRelationshipManager is responsible for storing the Next relationship
 * @brief Manages the Next relationship
 * @note: A Next relationship is a relationship between two statements where the second statement is executed after the first statement in some execution sequence
 */
class NextRelationshipManager : public StmtToStmtRelationshipManager<NextRelationshipStore> {
public:
    /**
     * @brief Constructs a NextRelationshipManager object
     * @return A NextRelationshipManager object
     */
    NextRelationshipManager();
};
