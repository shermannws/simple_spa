#pragma once

#include <string>

enum class EntityType {
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
};

class QueryEntity {
private:
    std::string synonym;
    EntityType type;
public:
    explicit QueryEntity(EntityType type, const std::string &synonym);
    bool operator==(const QueryEntity& other) const;
    std::string getSynonym();
    EntityType getType();
};
