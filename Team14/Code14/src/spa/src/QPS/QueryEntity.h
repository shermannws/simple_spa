#pragma once

#include <string>

#include "QPSTypes.h"

enum class QueryEntityType {
    Procedure,
    Stmt,
    Read,
    Print,
    Assign,
    Call,
    While,
    If,
    Variable,
    Constant,
    Invalid
};

class QueryEntity {
private:
    Synonym synonym;
    QueryEntityType type;
public:
    explicit QueryEntity(QueryEntityType type, const Synonym &synonym);
    bool operator==(const QueryEntity& other) const;
    Synonym getSynonym();
    QueryEntityType getType();
};
