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

	/*!
	 * Returns the left Entity in a Relationship
	 */
	std::shared_ptr<Entity> getLeftEntity() const;

	/*!
	 * Returns the right Entity in a Relationship
	 */
    std::shared_ptr<Entity> getRightEntity() const;

	/*!
	 * Overriden == operator for comparison between Relationship
	 */
	bool operator==(const HashableKey& other) const override;
};


//Including definitions in this file due to Generics in use

template <typename T, typename U>
Relationship<T, U>::Relationship(const RelationshipType relationshipType,
	const std::shared_ptr<T> leftEntity,
	const std::shared_ptr<U> rightEntity)
	: relationshipType(relationshipType), leftEntity(leftEntity), rightEntity(rightEntity) {}

template <typename T, typename U>
std::shared_ptr<Entity> Relationship<T, U>::getLeftEntity() const {
	return this->leftEntity;
}

template <typename T, typename U>
std::shared_ptr<Entity> Relationship<T, U>::getRightEntity() const {
	return this->rightEntity;
}

template <typename T, typename U>
bool Relationship<T, U>::operator==(const HashableKey& other) const {
	if (const Relationship* otherKey = dynamic_cast<const Relationship*>(&other)) {
		return *(this->getLeftEntity()->getEntityValue()) == *(otherKey->getLeftEntity()->getEntityValue())
			&& *(this->getRightEntity()->getEntityValue()) == *(otherKey->getRightEntity()->getEntityValue());
	}
	return false;
}
