#pragma once

#include <string>

enum class RefType {
    StmtRef,
    EntRef,
    Invalid,
};

enum class RootType {
    Integer,
    Wildcard,
    Synonym,
    Ident,
    Invalid
};


class Ref {
private:
    std::string rep;
    RefType type;
    RootType root_type;
public:
    explicit Ref();
    std::string getRep();
    RefType getType();
    RootType getRootType();
    void setRep(std::string& rrep);
    void setType(RefType& rref_type);
    void setRootType(RootType& rroot_type);

};
