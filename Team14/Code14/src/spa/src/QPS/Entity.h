#pragma once

#include <string>

enum class EntityType {
    PROCEDURE,
    STMT,
    READ,
    PRINT,
    ASSIGN,
    CALL,
    WHILE,
    IF,
    VARIABLE,
    CONSTANT,
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
