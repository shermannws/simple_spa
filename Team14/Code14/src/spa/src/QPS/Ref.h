#pragma once

#include <string>

#include "Entity.h"

enum class RefType {
    StmtRef,
    EntRef,
    Invalid,
};

enum class RootType {
    Integer, // StmtRef
    Wildcard, // StmtRef & EntRef
    Synonym, // StmtRef & EntRef
    Ident, // EntRef
    Invalid
};


class Ref {
private:
    std::string rep;
    RefType type;
    RootType rootType;
    EntityType entityType;
public:
    explicit Ref();
    std::string getRep();
    RefType getType();
    RootType getRootType();
    EntityType getEntityType();
    void setRep(std::string& rrep);
    void setType(RefType& rrefType);
    void setRootType(RootType& rrootType);
    void setEntityType(EntityType& eentityType);

};
