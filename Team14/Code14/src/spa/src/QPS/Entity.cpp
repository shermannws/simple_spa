#include "Entity.h"

#include <string>

Entity::Entity(EntityType type, const std::string& synonym) {
    this->type = type;
    this->synonym = synonym;
}

std::string Entity::getSynonym() {
    return synonym;
}

EntityType Entity::getType() {
    return type;
}
