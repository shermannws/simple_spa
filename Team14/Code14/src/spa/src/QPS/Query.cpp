#include <string>
#include <memory>

#include "Query.h"

Query::Query() {
    declarations = DeclarationMap();
    selects = std::vector<Synonym>();
}

std::shared_ptr<QueryEntity> Query::getEntity(const Synonym& syn) const {
    auto it = declarations.find(syn);

    if (it != declarations.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

void Query::addSelect(const Synonym synonym){
    selects.push_back(synonym);
}

void Query::setBooleanResult() {
    selects = std::vector<Synonym>();
}

void Query::addDeclaration(const EntityPtr& entity){
    declarations.insert({entity->getSynonym(), entity});
}

bool Query::hasDeclarations() const {
    return !declarations.empty();
}

DeclarationMap Query::getDeclarations() const {
    return declarations;
}

std::vector<Synonym> Query::getSelect() const {
    return selects;
}

void Query::addClause(std::shared_ptr<SuchThatClause> clause) {
    suchThatClauses.push_back(clause);
}

void Query::addClause(std::shared_ptr<PatternClause> clause) {
    patternClauses.push_back(clause);
}

std::vector<std::shared_ptr<SuchThatClause>> Query::getSuchThat() const {
    return suchThatClauses;
}

std::vector<std::shared_ptr<PatternClause>> Query::getPattern() const {
    return patternClauses;
}