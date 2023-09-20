#include <string>

#include "Ref.h"

Ref::Ref() : type(RefType::Invalid), rootType(RootType::Invalid), entityType(QueryEntityType::Invalid) {}

void Ref::setRep(StringRep & rrep) {
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

void Ref::setEntityType(QueryEntityType& eentityType) {
    entityType = eentityType;
}

QueryEntityType Ref::getEntityType() {
    return entityType;
}