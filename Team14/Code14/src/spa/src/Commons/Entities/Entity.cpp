#include <stdexcept>

#include "Entity.h"

Entity::Entity() {}

Entity::Entity(const std::shared_ptr<EntityValue> entityValue, EntityType entityType)
    : entityValue(entityValue), entityType(entityType) {}

Entity::Entity(const std::shared_ptr<EntityValue> entityValue, EntityType entityType,
               const std::shared_ptr<AttrValue> attrValue)
    : entityValue(entityValue), entityType(entityType), attrValue(attrValue) {}

EntityType Entity::getEntityType() const { return this->entityType; }

EntityValue Entity::getEntityValue() const { return *this->entityValue; }

AttrValue Entity::getAttrValue() const {
    return this->attrValue == nullptr ? AppConstants::STRING_EMPTY : *(this->attrValue);
}

bool Entity::operator==(const Entity &other) const { return this->getEntityValue() == other.getEntityValue(); }

std::size_t std::hash<std::shared_ptr<Entity>>::operator()(const std::shared_ptr<Entity> entityPtr) const {
    return std::hash<std::string>()(entityPtr->getEntityValue());
}

bool std::equal_to<std::shared_ptr<Entity>>::operator()(std::shared_ptr<Entity> const &lhs,
                                                        std::shared_ptr<Entity> const &rhs) const {
    return *lhs == *rhs;
}

std::size_t std::hash<std::vector<std::shared_ptr<Entity>>>::operator()(
        const std::vector<std::shared_ptr<Entity>> &entities) const {
    std::hash<std::shared_ptr<Entity>> hasher;

    std::size_t seed = entities.size();
    for (auto &i: entities) { seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2); }
    return seed;
};

bool std::equal_to<std::vector<std::shared_ptr<Entity>>>::operator()(
        std::vector<std::shared_ptr<Entity>> const &lhs, std::vector<std::shared_ptr<Entity>> const &rhs) const {
    if (lhs.size() != rhs.size()) { return false; }
    for (size_t i = 0; i < lhs.size(); ++i) {
        if (lhs[i]->getEntityValue() != rhs[i]->getEntityValue()) { return false; }
    }
    return true;
};
