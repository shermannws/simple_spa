#pragma once

#include "Commons/Entities/Statement.h"
#include "RelationshipStore.h"

/**
 * @brief A class that stores NextRelationships
 * @details A class that stores NextRelationships
 */
class NextRelationshipStore : public RelationshipStore<Statement, Statement> {
public:
    /**
     * @brief Construct a new NextRelationshipStore object
     * @return A new NextRelationshipStore object
     */
    NextRelationshipStore();
};