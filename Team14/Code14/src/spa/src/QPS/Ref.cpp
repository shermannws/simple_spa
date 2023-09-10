
#include "Ref.h"
#include <string>

Ref::Ref() : type(RefType::Invalid), rootType(RootType::Invalid), entityType(EntityType::Invalid) {}

void Ref::setRep(std::string& rrep) {
    rep = rrep;
}

std::string Ref::getRep() {
    return rep;
}

void Ref::setType(RefType& rrefType) {
    type = rrefType;
}

RefType Ref::getType() {
    return type;
}

void Ref::setRootType(RootType& rrootType) {
    rootType = rrootType;
}

RootType Ref::getRootType() {
    return rootType;
}

void Ref::setEntityType(EntityType& eentityType) {
    entityType = eentityType;
}

EntityType Ref::getEntityType() {
    return entityType;
}