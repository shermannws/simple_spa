#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "QueryEntity.h"
#include "SuchThatClause.h"
#include "PatternClause.h"
#include "QPSTypes.h"

class Query {
private:
    std::unordered_map<std::string, std::shared_ptr<QueryEntity>> declarations;
    std::vector<std::shared_ptr<QueryEntity>> selects;
    std::vector<std::shared_ptr<SuchThatClause>> suchThatClauses;
    std::vector<std::shared_ptr<PatternClause>> patternClauses;
public:
    Query();
    void addDeclaration(const std::shared_ptr<QueryEntity>& entity);
    void addSelect(const std::shared_ptr<QueryEntity>& entity);
    void addSuchThat(std::shared_ptr<SuchThatClause> clause);
    void addPattern(std::shared_ptr<PatternClause> clause);
    bool hasDeclarations();
    std::shared_ptr<QueryEntity> getEntity(const std::string& syn);
    std::unordered_map<std::string, std::shared_ptr<QueryEntity>> getDeclarations();
    std::vector<std::shared_ptr<QueryEntity>> getSelect();
    std::vector<std::shared_ptr<SuchThatClause>> getSuchThat();
    std::vector<std::shared_ptr<PatternClause>> getPattern();

};