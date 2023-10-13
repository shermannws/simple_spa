#include <string>

#include "Ref.h"
#include "QPSUtil.h"

Ref::Ref() : type(RefType::Invalid), rootType(RootType::Invalid),
entityType(QueryEntityType::Invalid), attrName(AttrName::Invalid) {}

void Ref::setRep(StringRep & rrep) {
    rep = rrep;
}

std::string Ref::getRep() const{
    return rep;
}

void Ref::setAttrName(const std::string& name) {
    attrName = QPSUtil::strToAttrNameMap[name];
}

AttrName Ref::getAttrName() const{
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

bool Ref::isOfName() {
    return rootType == RootType::Ident || attrName == AttrName::ProcName || attrName == AttrName::VarName;
}

bool Ref::isOfInteger() {
    return rootType == RootType::Integer || attrName == AttrName::Value || attrName == AttrName::StmtNo;
}