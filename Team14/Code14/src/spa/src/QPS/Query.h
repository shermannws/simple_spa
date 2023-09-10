#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "QueryEntity.h"

class Query {
private:
    std::unordered_map<std::string, std::shared_ptr<QueryEntity>> declarations;
    std::vector<std::shared_ptr<QueryEntity>> selects;

public:
    Query();
    void addDeclaration(const std::shared_ptr<QueryEntity>& entity);
    void addSelect(const std::shared_ptr<QueryEntity>& entity);
    // void addSuchThat();
    // void addPattern();
    bool hasDeclarations();
    std::shared_ptr<QueryEntity> getEntity(const std::string& syn);
    std::unordered_map<std::string, std::shared_ptr<QueryEntity>> getDeclarations();
    std::vector<std::shared_ptr<QueryEntity>> getSelect();
};
