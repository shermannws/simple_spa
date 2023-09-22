#pragma once

#include "Relationship.h"
#include "RelationshipType.h"
#include "Commons/Entities/Statement.h"

/**
 * @brief A class that represents the Follows relationship between two Statement objects
 * @details A class that represents the Follows relationship between two Statement objects
 */
class FollowsRelationship : public Relationship<Statement, Statement> {
private:
    /**
     * @brief A boolean value that indicates if the Follows relationship is direct
     * @details Two statements are directly Follows if the first statement is the statement immediately before the second statement
     */
    bool direct;
public:
	/**
	 * @brief RelationshipType of FollowsRelationship
	 */
	static RelationshipType relationshipType;

	/**
     * @brief Construct a new FollowsRelationship object
     * @param leftEntity The former statement of the Follows relationship
     * @param rightEntity The latter statement of the Follows relationship
     * @param isDirect A boolean value that indicates if the Follows relationship is direct
     * @return A new FollowsRelationship object
     */
	FollowsRelationship(const std::shared_ptr<Statement> leftEntity,
		const std::shared_ptr<Statement> rightEntity, bool isDirect);

    /**
     * @brief Returns a boolean value that indicates if the Follows relationship is direct
     * @return True if the Follows relationship is direct, else false
     */
    bool isDirect() const;
};