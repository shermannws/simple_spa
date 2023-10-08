template <typename S>
ProcToVarRelationshipManager<S>::ProcToVarRelationshipManager()
    : relationshipStore(std::make_shared<S>(S())) {};

template <typename S>
void ProcToVarRelationshipManager<S>::storeRelationship(std::shared_ptr<Procedure> procedure, std::shared_ptr<Variable> variable) {
    this->relationshipStore->storeRelationship(procedure, variable);
}

template <typename S>
std::vector<std::vector<Entity>> ProcToVarRelationshipManager<S>::getRelationshipProcPair() const {
    return ManagerUtils::getPairNoMatch<Procedure, Variable>(*relationshipStore);
}

template <typename S>
std::vector<Entity> ProcToVarRelationshipManager<S>::getRelationshipIdent(Variable& var) const {
    return ManagerUtils::getLeftEntitiesFromRightKeyNoMatch<Procedure, Variable>(*relationshipStore, var);
}

template <typename S>
std::vector<Entity> ProcToVarRelationshipManager<S>::getRelationshipProc() const {
    return ManagerUtils::getLeftKeysNoMatch<Procedure, Variable>(*relationshipStore);
}

template <typename S>
std::vector<Entity> ProcToVarRelationshipManager<S>::getRelationshipVar(Procedure& procedure) const {
    return ManagerUtils::getRightEntitiesFromLeftKeyNoMatch<Procedure, Variable>(*relationshipStore, procedure);
}

template <typename S>
bool ProcToVarRelationshipManager<S>::isRelationship(Procedure& procedure, Variable& var) const {
    return ManagerUtils::mapContains<Procedure, Variable>(*relationshipStore, procedure, var);
}

template <typename S>
bool ProcToVarRelationshipManager<S>::hasRelationship(Procedure& procedure) const {
    return relationshipStore->getRightEntitiesOf(std::make_shared<Procedure>(procedure)) != nullptr;
}

template <typename S>
void ProcToVarRelationshipManager<S>::calculateProcVarRelationshipForCallers(std::shared_ptr<CallsRelationshipManager> callManager) {
    for (auto it = relationshipStore->getLeftToRightBeginIterator(); it != relationshipStore->getLeftToRightEndIterator(); ++it) {
        auto proc = it->first;
        auto variableSet = it->second;
        auto callersOfProc = callManager->getRelationshipFormerStarAsProcedure(*proc);
        if (callersOfProc == nullptr) {
            continue;
        }
        for (auto it2 = callersOfProc->getBeginIterator(); it2 != callersOfProc->getEndIterator(); ++it2) {
            for (auto it3 = variableSet->getBeginIterator(); it3 != variableSet->getEndIterator(); ++it3) {
                auto variable = *it3;
                this->storeRelationship(*it2, variable);
            }
        }
    }
}

template <typename S>
std::shared_ptr<EntityStore<Variable>> ProcToVarRelationshipManager<S>::getRhsVarAsVariables(std::shared_ptr<Procedure> left) const {
    return relationshipStore->getRightEntitiesOf(left);
};