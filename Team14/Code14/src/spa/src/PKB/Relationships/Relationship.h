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

template <typename T, typename U>
struct std::hash<Relationship<T, U>> {
	std::size_t operator()(const Relationship<T, U>& relationship) const;
};

template <typename T, typename U>
struct std::hash<std::shared_ptr<Relationship<T, U>>> {
	std::size_t operator()(const std::shared_ptr<Relationship<T, U>> relationshipPtr) const;
};

template <typename T, typename U>
struct std::equal_to<std::shared_ptr<Relationship<T,U>>> {
	bool operator()(
		std::shared_ptr<Relationship<T, U>> const& lhs,
		std::shared_ptr<Relationship<T, U>> const& rhs) const;
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

template <typename T, typename U>
std::size_t std::hash<Relationship<T, U>>::operator()(const Relationship<T, U>& relationship) const {
	return std::hash<std::string>()(
		*(relationship.getLeftEntity()->getEntityValue()) +
		"," +
		*(relationship.getRightEntity()->getEntityValue()));
}

template <typename T, typename U>
std::size_t std::hash<std::shared_ptr<Relationship<T, U>>>::operator()(const std::shared_ptr<Relationship<T, U>> relationshipPtr) const {
	return std::hash<Relationship<T, U>>()(*relationshipPtr.get());
}

template <typename T, typename U>
bool std::equal_to<std::shared_ptr<Relationship<T, U>>>::operator()(
	std::shared_ptr<Relationship<T, U>> const& lhs,
	std::shared_ptr<Relationship<T, U>> const& rhs) const {
	return *lhs == *rhs;
}