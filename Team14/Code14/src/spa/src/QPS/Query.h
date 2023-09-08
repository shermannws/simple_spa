#pragma once

#include <vector>

#include "Entity.h"

class Query {
public:
    Query();

    void addDeclaration(const std::shared_ptr<Entity>& entity);
    void addSelect(const std::shared_ptr<Entity>& entity);
    // void addSuchThat();
    // void addPattern();
    bool hasDeclarations();
    std::shared_ptr<Entity> getEntity(const std::string& syn);
    std::unordered_map<std::string, std::shared_ptr<Entity>> getDeclarations();
    std::vector<std::shared_ptr<Entity>> getSelect();

private:
    std::unordered_map<std::string, std::shared_ptr<Entity>> declarations;
    std::vector<std::shared_ptr<Entity>> select;
};


