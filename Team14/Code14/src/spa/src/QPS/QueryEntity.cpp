#include "QueryEntity.h"

#include <string>

QueryEntity::QueryEntity(EntityType type, const std::string& synonym) : type(type), synonym(synonym) {}

bool QueryEntity::operator==(const QueryEntity& other) const {
    return (type == other.type) && (synonym == other.synonym);
}

std::string QueryEntity::getSynonym() {
    return synonym;
}

EntityType QueryEntity::getType() {
    return type;
}
