#pragma once

#include "../../Commons/HashableKey.h"
#include "../../Commons/Entities/Entity.h"
#include "RelationshipType.h"

/**
 * @brief A class that represents a relationship between two Entities
 * @details This class is a template class that takes in two Entity types and represents a relationship between them.
 * The relationship is represented by a RelationshipType enum value.
 * This class is the super class of all Relationship classes.
 * @tparam T The type of the left Entity in the relationship
 * @tparam U The type of the right Entity in the relationship
 */
template <typename T, typename U>
class Relationship: public HashableKey {
private:
    /**
     * @brief The type of the relationship
     */
	RelationshipType relationshipType;
    /**
     * @brief The left Entity in the relationship
     */
	std::shared_ptr<T> leftEntity;
    /**
     * @brief The right Entity in the relationship
     */
	std::shared_ptr<U> rightEntity;

public:
    /**
     * @brief Construct a new Relationship object
     * @param relationshipType The type of the relationship
     * @param leftEntity The left Entity in the relationship
     * @param rightEntity The right Entity in the relationship
     * @return A new Relationship object
     */
    Relationship(const RelationshipType relationshipType,
        const std::shared_ptr<T> leftEntity,
        const std::shared_ptr<U> rightEntity);

    /**
     * @brief Returns the left Entity in a Relationship
     * @param relationship The relationship to get the left Entity from
     * @return The left Entity in the relationship
     */
    static Entity getLeftEntityFromRelationship(const Relationship<T, U>& relationship);

    /**
     * @brief Returns the right Entity in a Relationship
     * @param relationship The relationship to get the right Entity from
     * @return The right Entity in the relationship
     */
    static Entity getRightEntityFromRelationship(const Relationship<T, U>& relationship);

    /**
     * @brief Returns the entities in a Relationship in a vector
     * @param relationship The relationship to get the entities from
     * @return The entities in the relationship in a vector
     * @note The left Entity is the first element in the vector and the right Entity is the second element in the vector
     */
    static std::vector<Entity> getEntityPairFromRelationship(const Relationship<T, U>& relationship);

	/**
	 * Returns the left Entity in a Relationship as an Entity
	 * @return The left Entity in the relationship
	 */
	std::shared_ptr<Entity> getLeftEntity() const;

	/**
	 * Returns the right Entity in a Relationship as an Entity
	 * @return The right Entity in the relationship
	 */
    std::shared_ptr<Entity> getRightEntity() const;

    /**
     * Returns the left Entity in a Relationship as its original type (which is a subclass of Entity)
     * @tparam T The original type of the left Entity in the relationship
     * @return The left Entity in the relationship
     */
    std::shared_ptr<T> getLeftObject() const;

    /**
     * Returns the right Entity in a Relationship as its original type (which is a subclass of Entity)
     * @tparam U The original type of the right Entity in the relationship
     * @return The right Entity in the relationship
     */
    std::shared_ptr<U> getRightObject() const;

	/**
     * Returns the type of the relationship
     * @return The type of the relationship
     */
	RelationshipType getRelationshipType() const;

	/**
     * Returns a boolean value indicating if the entity is equal to the given entity
     * @param other The entity to be compared with
     * @return True if the entity is equal to the given entity, else false
     */
	bool operator==(const HashableKey& other) const override;
};

#include "Relationship.hpp"