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
    Expression rep;
    RefType type;
    RootType rootType;
    QueryEntityType entityType;
public:
    explicit Ref();
    Expression getRep();
    RefType getType();
    RootType getRootType();
    QueryEntityType getEntityType();
    void setRep(Expression& rrep);
    void setType(RefType& rrefType);
    void setRootType(RootType& rrootType);
    void setEntityType(QueryEntityType& eentityType);

};
