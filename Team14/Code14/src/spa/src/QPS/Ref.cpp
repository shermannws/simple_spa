
#include "Ref.h"
#include <string>

Ref::Ref() : type(RefType::Invalid), refType(RootType::Invalid) {}

void Ref::setRep(std::string& rrep) {
    this->rep = rrep;
}

std::string Ref::getRep() {
    return this->rep;
}

void Ref::setType(RefType& rrefType) {
    this->type = rrefType;
}

RefType Ref::getType() {
    return this->type;
}

void Ref::setRootType(RootType& rrootType) {
    this->refType = rrootType;
}

RootType Ref::getRootType() {
    return this->refType;
}