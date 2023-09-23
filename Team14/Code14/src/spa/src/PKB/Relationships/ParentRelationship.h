#pragma once

#include "Relationship.h"
#include "RelationshipType.h"
#include "Commons/Entities/Statement.h"

/**
 * @brief A class that represents the Parent relationship between two Statements
 * @details A class that represents the Parent relationship between two Statements
 */
class ParentRelationship : public Relationship<Statement, Statement> {
private:
    /*!
     * A boolean value that indicates if the Parent relationship is direct
     * Two statements are directly Parent if the first statement is the immediate parent of the second statement
     */
    bool direct;
public:
	/**
     * @brief RelationshipType of ParentRelationship
     */
	static RelationshipType relationshipType;

    /**
     * @brief Construct a new ParentRelationship object
     * @param parentEntity The parent statement of the Parent relationship
     * @param childEntity The child statement of the Parent relationship
     * @param isDirect A boolean value that indicates if the Parent relationship is direct
     * @return A new ParentRelationship object
     */
    ParentRelationship(const std::shared_ptr<Statement> parentEntity,
        const std::shared_ptr<Statement> childEntity, bool isDirect);

    bool isDirect() const;
};