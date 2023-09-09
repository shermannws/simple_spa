#pragma once

#include <stdexcept>

#include "Entity.h"

Entity::Entity(const std::shared_ptr<std::string> entityValue, bool isInt) {
    this->entityValue = entityValue;
    this->isInt = isInt;
}


std::string* Entity::getEntityValue() const {
    return this->entityValue.get();
}

bool Entity::isEntityOfTypeInt() const {
    return this->isInt;
}

bool Entity::operator==(const HashableKey& other) const {
    if (const Entity* otherKey = dynamic_cast<const Entity*>(&other)) {
        return *this->getEntityValue() == *otherKey->getEntityValue();
    }
    return false;
}

std::size_t std::hash<Entity>::operator()(const Entity& entity) const {
    return std::hash<std::string>()(*(entity.getEntityValue()));
}

std::size_t std::hash<std::shared_ptr<Entity>>::operator()(const std::shared_ptr<Entity> entityPtr) const {
    return std::hash<Entity>()(*entityPtr.get());
}

bool std::equal_to<std::shared_ptr<Entity>>::operator()(
    std::shared_ptr<Entity> const& lhs,
    std::shared_ptr<Entity> const& rhs) const {
        return *lhs == *rhs;
}
