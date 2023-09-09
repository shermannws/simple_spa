#pragma once

#include <vector>

#include "Entity.h"

class Query {
private:
    std::vector<Entity> declarations;

public:
    Query();

    void addDeclaration();
    void addSuchThatClause();
    void addPatternClause();
};
