#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "QueryEntity.h"
#include "SuchThatClause.h"
#include "PatternClause.h"

class Query {
private:
    std::unordered_map<std::string, std::shared_ptr<QueryEntity>> declarations;
    std::vector<std::shared_ptr<QueryEntity>> selects;
    std::vector<SuchThatClause> suchThatClauses;
    std::vector<PatternClause> patternClauses;

public:
    Query();
    void addDeclaration(const std::shared_ptr<QueryEntity>& entity);
    void addSelect(const std::shared_ptr<QueryEntity>& entity);
    void addSuchThat(SuchThatClause& clause);
    void addPattern(PatternClause& clause);
    bool hasDeclarations();
    std::shared_ptr<QueryEntity> getEntity(const std::string& syn);
    std::unordered_map<std::string, std::shared_ptr<QueryEntity>> getDeclarations();
    std::vector<std::shared_ptr<QueryEntity>> getSelect();
    std::vector<SuchThatClause> getSuchThat();
    std::vector<PatternClause> getPattern();

};