#ifndef SPA_ENTITY_H
#define SPA_ENTITY_H

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
    std::string getSynonym();
    EntityType getType();
    //TODO toString() and eq(),neq() operator?
};


#endif //SPA_ENTITY_H
