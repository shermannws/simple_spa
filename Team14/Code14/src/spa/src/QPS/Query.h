#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "QueryEntity.h"
#include "SuchThatClause.h"
#include "PatternClause.h"
#include "QPSTypes.h"

typedef std::unordered_map<std::string, std::shared_ptr<QueryEntity>> DeclarationMap;
typedef std::shared_ptr<QueryEntity> EntityPtr;

class Query {
private:
    DeclarationMap declarations;
    std::vector<EntityPtr> selects;
    std::vector<SuchThatClause> suchThatClauses;
    std::vector<PatternClause> patternClauses;

public:
    Query();
    void addDeclaration(const EntityPtr& entity);
    void addSelect(const EntityPtr& entity);
    void addSuchThat(SuchThatClause& clause);
    void addPattern(PatternClause& clause);
    bool hasDeclarations();
    EntityPtr getEntity(const Synonym& syn);
    DeclarationMap getDeclarations();
    std::vector<EntityPtr> getSelect();
    std::vector<SuchThatClause> getSuchThat();
    std::vector<PatternClause> getPattern();

};