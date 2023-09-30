#include "ModifiesProcRelationshipManager.h"

ModifiesProcRelationshipManager::ModifiesProcRelationshipManager() : ProcToVarRelationshipManager<ModifiesProcRelationshipStore>() {}

void ModifiesProcRelationshipManager::storeModifiesProcRelationship(std::shared_ptr<Procedure> procedure, std::shared_ptr<Variable> variable) {
	this->storeRelationship(procedure, variable);
}

std::vector<std::vector<Entity>> ModifiesProcRelationshipManager::getModifiesProcPair() const {
	return this->getRelationshipProcPair();
}

std::vector<Entity> ModifiesProcRelationshipManager::getModifiesProcIdent(Variable& var) const {
	return this->getRelationshipIdent(var);
}

std::vector<Entity> ModifiesProcRelationshipManager::getModifiesProc() const {
	return this->getRelationshipProc();
}

std::vector<Entity> ModifiesProcRelationshipManager::getModifiesProcVar(Procedure& procedure) const {
	return this->getRelationshipVar(procedure);
}

bool ModifiesProcRelationshipManager::isProcModifiesVar(Procedure& procedure, Variable& var) const {
	return this->isRelationship(procedure, var);
}

bool ModifiesProcRelationshipManager::hasProcModifies(Procedure& procedure) const {
	return this->hasRelationship(procedure);
}
