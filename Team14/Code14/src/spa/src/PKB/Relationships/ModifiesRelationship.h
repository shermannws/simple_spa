#pragma once

#include "Relationship.h"
#include "RelationshipType.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"

/**
 * @brief A class that represents the Modifies relationship between a Statement and a Variable
 * @details A class that represents the Modifies relationship between a Statement and a Variable
 */
class ModifiesRelationship : public Relationship<Statement, Variable> {
public:
	/**
     * @brief RelationshipType of ModifiesRelationship
     */
	static RelationshipType relationshipType;

    /**
     * @brief Construct a new ModifiesRelationship object
     * @param leftEntity The statement that modifies the variable
     * @param rightEntity The variable that is modified by the statement
     * @return A new ModifiesRelationship object
     */
    ModifiesRelationship(const std::shared_ptr<Statement> leftEntity,
        const std::shared_ptr<Variable> rightEntity);
};