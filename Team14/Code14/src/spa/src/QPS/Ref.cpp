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

bool Ref::isWildcard() {
    return rootType == RootType::Wildcard;
}

bool Ref::isSynonym() {
    return rootType == RootType::Synonym;
}

bool Ref::isIdent() {
    return rootType == RootType::Ident;
}

bool Ref::isInteger() {
    return rootType == RootType::Integer;
}

bool Ref::operator==(const Ref& other) const {
    return (rep == other.rep) && (type == other.type)
        && (rootType == other.rootType) && (entityType == other.entityType);
}