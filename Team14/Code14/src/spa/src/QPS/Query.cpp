#include <string>
#include <memory>
#include <stdexcept>

#include "Query.h"

Query::Query() {
    declarations = DeclarationMap();
    selects = std::vector<EntityPtr>();
}

std::shared_ptr<QueryEntity> Query::getEntity(const Synonym& syn) {
    auto it = declarations.find(syn);

    if (it != declarations.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

void Query::addSelect(const EntityPtr& entity){
    selects.push_back(entity);
}

void Query::addDeclaration(const EntityPtr& entity){
    if (declarations.find(entity->getSynonym()) != declarations.end()){
        throw std::runtime_error("Trying to redeclare a synonym");
    }
    declarations.insert({entity->getSynonym(), entity});
}

bool Query::hasDeclarations() {
    return !declarations.empty();
}

DeclarationMap Query::getDeclarations() {
    return declarations;
}

std::vector<EntityPtr> Query::getSelect() {
    return selects;
}

void Query::addSuchThat(std::shared_ptr<SuchThatClause> clause) {
    suchThatClauses.push_back(clause);
}

std::vector<std::shared_ptr<SuchThatClause>> Query::getSuchThat() {
    return suchThatClauses;
}

void Query::addPattern(std::shared_ptr<PatternClause> clause) {
    patternClauses.push_back(clause);
}

std::vector<std::shared_ptr<PatternClause>> Query::getPattern() {
    return patternClauses;
}