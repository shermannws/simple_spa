#pragma once

#include <stdexcept>

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
std::shared_ptr<T> Relationship<T, U>::getLeftObject() const {
    return this->leftEntity;
}

template <typename T, typename U>
std::shared_ptr<U> Relationship<T, U>::getRightObject() const {
    return this->rightEntity;
}

template <typename T, typename U>
RelationshipType Relationship<T, U>::getRelationshipType() const {
	return this->relationshipType;
}

template <typename T, typename U>
bool Relationship<T, U>::operator==(const HashableKey& other) const {
	if (const Relationship* otherKey = dynamic_cast<const Relationship*>(&other)) {
		return *(this->getLeftEntity()->getEntityValue()) == *(otherKey->getLeftEntity()->getEntityValue())
			&& *(this->getRightEntity()->getEntityValue()) == *(otherKey->getRightEntity()->getEntityValue())
			&& this->getRelationshipType() == otherKey->getRelationshipType();
	}
	return false;
}

template <typename T, typename U>
Entity Relationship<T, U>::getLeftEntityFromRelationship(const Relationship<T, U>& relationship) {
    return *relationship.getLeftEntity();
}

template <typename T, typename U>
Entity Relationship<T, U>::getRightEntityFromRelationship(const Relationship<T, U>& relationship) {
    return *relationship.getRightEntity();
}

template <typename T, typename U>
std::vector<Entity> Relationship<T, U>::getEntityPairFromRelationship(const Relationship<T, U>& relationship) {
    return { *relationship.getLeftEntity(), *relationship.getRightEntity() };
}
