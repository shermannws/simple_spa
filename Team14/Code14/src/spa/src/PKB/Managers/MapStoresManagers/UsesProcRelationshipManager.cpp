#include "UsesProcRelationshipManager.h"

UsesProcRelationshipManager::UsesProcRelationshipManager() : ProcToVarRelationshipManager<UsesProcRelationshipStore>() {}

void UsesProcRelationshipManager::storeUsesProcRelationship(std::shared_ptr<Procedure> procedure, std::shared_ptr<Variable> variable) {
	this->storeRelationship(procedure, variable);
}

std::vector<std::vector<Entity>> UsesProcRelationshipManager::getUsesProcPair() const {
	return this->getRelationshipProcPair();
}

std::vector<Entity> UsesProcRelationshipManager::getUsesProcIdent(Variable& var) const {
	return this->getRelationshipIdent(var);
}

std::vector<Entity> UsesProcRelationshipManager::getUsesProc() const {
	return this->getRelationshipProc();
}

std::vector<Entity> UsesProcRelationshipManager::getUsesProcVar(Procedure& procedure) const {
	return this->getRelationshipVar(procedure);
}

bool UsesProcRelationshipManager::isProcUsesVar(Procedure& procedure, Variable& var) const {
	return this->isRelationship(procedure, var);
}

bool UsesProcRelationshipManager::hasProcUses(Procedure& procedure) const {
	return this->hasRelationship(procedure);
}
