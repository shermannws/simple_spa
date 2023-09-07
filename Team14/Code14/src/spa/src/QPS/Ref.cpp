
#include "Ref.h"
#include <string>

Ref::Ref() : type(RefType::Invalid), root_type(RootType::Invalid) {}

void Ref::setRep(std::string& rrep) {
    this->rep = rrep;
}

std::string Ref::getRep() {
    return this->rep;
}

void Ref::setType(RefType& rref_type) {
    this->type = rref_type;
}

RefType Ref::getType() {
    return this->type;
}

void Ref::setRootType(RootType& rroot_type) {
    this->root_type = rroot_type;
}

RootType Ref::getRootType() {
    return this->root_type;
}