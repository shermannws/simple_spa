#include "ModifiesRelationshipManager.h"

ModifiesRelationshipManager::ModifiesRelationshipManager() : StmtToVarRelationshipManager() {
    this->clauseGroup = ClauseGroup::Modifies;
};

std::shared_ptr<Variable> ModifiesRelationshipManager::getModifiedVar(std::shared_ptr<Statement> stmt) {
    return this->relationshipStore->getRightEntitiesOf(std::move(stmt))->first();
}