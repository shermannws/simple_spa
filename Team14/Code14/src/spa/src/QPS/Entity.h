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

class Entity {
private:
    std::string synonym;
    EntityType type;
public:
    explicit Entity(EntityType type, const std::string &synonym);
    bool operator==(const Entity& other) const;
    std::string getSynonym();
    EntityType getType();
};
