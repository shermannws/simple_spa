#pragma once

#include "../../Commons/HashableKey.h"
#include "../../Commons/Entities/Entity.h"
#include "RelationshipType.h"

template <typename T, typename U>
class Relationship: public HashableKey {
private:
	RelationshipType relationshipType;
	std::shared_ptr<T> leftEntity;
	std::shared_ptr<U> rightEntity;

public:
	/*!
	 * Constructor for Relationship class
	 */
	Relationship(const RelationshipType relationshipType,
		const std::shared_ptr<T> leftEntity,
		const std::shared_ptr<U> rightEntity);

    static Entity getLeftEntityFromRelationship(const Relationship<T, U>& relationship);

    static Entity getRightEntityFromRelationship(const Relationship<T, U>& relationship);

    static std::vector<Entity> getEntityPairFromRelationship(const Relationship<T, U>& relationship);

	/*!
	 * Returns the left Entity in a Relationship
	 */
	std::shared_ptr<Entity> getLeftEntity() const;

	/*!
	 * Returns the right Entity in a Relationship
	 */
    std::shared_ptr<Entity> getRightEntity() const;

    /*!
 * Returns the left Entity in a Relationship
 */
    std::shared_ptr<T> getLeftObject() const;

    /*!
     * Returns the right Entity in a Relationship
     */
    std::shared_ptr<U> getRightObject() const;

	/*!
	 * Returns the RelationshipType of the object
	 */
	RelationshipType getRelationshipType() const;

	/*!
	 * Overriden == operator for comparison between Relationship
	 */
	bool operator==(const HashableKey& other) const override;
};

#include "Relationship.hpp"