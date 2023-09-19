#pragma once

#include <string>

#include "QueryEntity.h"
#include "QPSTypes.h"

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
    StringRep rep;
    RefType type;
    RootType rootType;
    QueryEntityType entityType;
public:
    explicit Ref();
    StringRep getRep();
    RefType getType();
    RootType getRootType();
    QueryEntityType getEntityType();
    void setRep(StringRep& rrep);
    void setType(RefType& rrefType);
    void setRootType(RootType& rrootType);
    void setEntityType(QueryEntityType& eentityType);

};
