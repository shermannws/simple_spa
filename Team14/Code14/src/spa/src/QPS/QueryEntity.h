#pragma once

#include <string>
#include "Token.h"

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
    std::string synonym;
    QueryEntityType type;
public:
    explicit QueryEntity(QueryEntityType type, const std::string &synonym);
    QueryEntity(const std::shared_ptr<Token>& designEntity, const std::string& synonym);
    bool operator==(const QueryEntity& other) const;
    std::string getSynonym();
    QueryEntityType getType();
};
