#include "UsesRelationshipManager.h"

UsesRelationshipManager::UsesRelationshipManager() : StmtToVarRelationshipManager() {
    this->clauseGroup = ClauseGroup::Uses;
};