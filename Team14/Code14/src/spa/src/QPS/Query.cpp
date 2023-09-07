#include <string>
#include <memory>
#include <stdexcept>

#include "Query.h"

Query::Query() {
    declarations = std::unordered_map<std::string, std::shared_ptr<Entity>>();
    selects = std::vector<std::shared_ptr<Entity>>();
}

std::shared_ptr<Entity> Query::getEntity(const std::string& syn) {
    auto it = declarations.find(syn);

    if (it != declarations.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

void Query::addSelect(const std::shared_ptr<Entity>& entity) {
    selects.push_back(entity);
}

void Query::addSuchThatClause(SuchThatClause& clause) {
    such_that_clauses.push_back(clause);
}

std::vector<SuchThatClause> Query::getSuchThat() {
    return such_that_clauses;
}

void Query::addDeclaration(const std::shared_ptr<Entity>& entity){
    if (declarations.find(entity->getSynonym()) != declarations.end()){
        throw std::runtime_error("Trying to redeclare a synonym");
    }
    declarations.insert({entity->getSynonym(), entity});
}

bool Query::hasDeclarations() {
    return !declarations.empty();
}

std::unordered_map<std::string, std::shared_ptr<Entity>> Query::getDeclarations() {
    return declarations;
}

std::vector<std::shared_ptr<Entity>> Query::getSelect() {
    return selects;
}
