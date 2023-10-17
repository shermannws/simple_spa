#include <stdexcept>

#include "Entity.h"

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

bool Entity::operator==(const HashableKey &other) const {
    if (const Entity *otherKey = dynamic_cast<const Entity *>(&other)) {
        return this->getEntityValue() == otherKey->getEntityValue() && this->getAttrValue() == otherKey->getAttrValue();
    }
    return false;
}

std::size_t std::hash<Entity>::operator()(const Entity &entity) const {
    std::size_t entityValueHash = std::hash<std::string>()(entity.getEntityValue());
    std::size_t attrValueHash = std::hash<std::string>()(entity.getAttrValue());
    return entityValueHash ^ attrValueHash;
}

std::size_t std::hash<std::shared_ptr<Entity>>::operator()(const std::shared_ptr<Entity> entityPtr) const {
    return std::hash<Entity>()(*entityPtr.get());
}

bool std::equal_to<std::shared_ptr<Entity>>::operator()(std::shared_ptr<Entity> const &lhs,
                                                        std::shared_ptr<Entity> const &rhs) const {
    return *lhs == *rhs;
}
