#pragma once

#include <stdexcept>

#include "Relationship.h"

Relationship::Relationship(const RelationshipType relationshipType,
    const std::shared_ptr<Entity> leftEntity,
    const std::shared_ptr<Entity> rightEntity) {
    this->relationshipType = relationshipType;
    this->leftEntity = leftEntity;
    this->rightEntity = rightEntity;
}

Entity* Relationship::getLeftEntity() const {
    return this->leftEntity.get();
}

Entity* Relationship::getRightEntity() const {
    return this->rightEntity.get();
}


bool Relationship::operator==(const HashableKey& other) const {
    if (const Relationship* otherKey = dynamic_cast<const Relationship*>(&other)) {
        return *(this->getLeftEntity()->getEntityValue()) == *(otherKey->getLeftEntity()->getEntityValue())
            && *(this->getRightEntity()->getEntityValue()) == *(otherKey->getRightEntity()->getEntityValue());
    }
    return false;
}

std::size_t std::hash<Relationship>::operator()(const Relationship& relationship) const {
    return std::hash<std::string>()(
        *(relationship.getLeftEntity()->getEntityValue()) +
        "," +
        *(relationship.getRightEntity()->getEntityValue()));
}

std::size_t std::hash<std::shared_ptr<Relationship>>::operator()(const std::shared_ptr<Relationship> relationshipPtr) const {
    return std::hash<Relationship>()(*relationshipPtr);
}

bool std::equal_to<std::shared_ptr<Relationship>>::operator()(
    std::shared_ptr<Relationship> const& lhs,
    std::shared_ptr<Relationship> const& rhs) const {
    return *lhs == *rhs;
}