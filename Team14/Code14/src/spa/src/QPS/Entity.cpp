#include "Entity.h"

#include <string>

Entity::Entity(EntityType type, const std::string& synonym) : type(type), synonym(synonym) {}

bool Entity::operator==(const Entity& other) const {
    return (type == other.type) && (synonym == other.synonym);
}

std::string Entity::getSynonym() {
    return synonym;
}

EntityType Entity::getType() {
    return type;
}
