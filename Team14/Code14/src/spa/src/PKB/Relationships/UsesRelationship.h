#pragma once

#include "Relationship.h"
#include "RelationshipType.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"

/**
 * @brief A class that represents the Uses relationship between a Statement and a Variable
 * @details A class that represents the Uses relationship between a Statement and a Variable
 */
class UsesRelationship : public Relationship<Statement, Variable> {
public:
	/**
     * @brief RelationshipType of UsesRelationship
     */
	static RelationshipType relationshipType;

    /**
     * @brief Construct a new UsesRelationship object
     * @param leftEntity The statement that uses the variable
     * @param rightEntity The variable that is used by the statement
     * @return A new UsesRelationship object
     */
    UsesRelationship(const std::shared_ptr<Statement> leftEntity,
        const std::shared_ptr<Variable> rightEntity);
};