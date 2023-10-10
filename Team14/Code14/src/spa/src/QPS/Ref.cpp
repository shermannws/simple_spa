#include <string>

#include "Ref.h"

Ref::Ref() : type(RefType::Invalid), rootType(RootType::Invalid), entityType(QueryEntityType::Invalid) {}

void Ref::setRep(StringRep & rrep) {
    rep = rrep;
}

std::string Ref::getRep() const{
    return rep;
}

std::string Ref::getAttrName() const{
    return attrName;
}

void Ref::setType(RefType& rrefType) {
    type = rrefType;
}

RefType Ref::getType() const{
    return type;
}

void Ref::setRootType(RootType& rrootType) {
    rootType = rrootType;
}

RootType Ref::getRootType() const {
    return rootType;
}

void Ref::setEntityType(QueryEntityType& eentityType) {
    entityType = eentityType;
}

QueryEntityType Ref::getEntityType() const{
    return entityType;
}

bool Ref::isRootType(RootType rrootType) {
    return rootType == rrootType;
}

bool Ref::operator==(const Ref& other) const {
    return (rep == other.rep) && (type == other.type)
        && (rootType == other.rootType) && (entityType == other.entityType);
}

bool Ref::isOfStmtRef() {
    return isRootType(RootType::Synonym) || isRootType(RootType::Wildcard) || isRootType(RootType::Integer);
}

bool Ref::isOfEntRef() {
    return isRootType(RootType::Synonym) || isRootType(RootType::Wildcard) || isRootType(RootType::Ident);
}

bool Ref::isOfWithRef() {
    return isRootType(RootType::Ident) || isRootType(RootType::Integer) || isRootType(RootType::AttrRef);
}

void Ref::setAttrName(std::string name) {
    attrName = name;
}
