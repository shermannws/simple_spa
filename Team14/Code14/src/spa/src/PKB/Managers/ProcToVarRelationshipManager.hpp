template <typename S>
ProcToVarRelationshipManager<S>::ProcToVarRelationshipManager()
    : relationshipStore(std::make_shared<S>(S())) {};

template <typename S>
void ProcToVarRelationshipManager<S>::storeRelationship(std::shared_ptr<Procedure> procedure, std::shared_ptr<Variable> variable) {
    this->relationshipStore->storeRelationship(procedure, variable);
}

template <typename S>
std::vector<std::vector<Entity>> ProcToVarRelationshipManager<S>::getRelationshipProcPair() const {
    // TODO: Refactor
    std::vector<std::vector<Entity>> result;
    for (auto it = relationshipStore->getLeftToRightBeginIterator(); it != relationshipStore->getLeftToRightEndIterator(); ++it) {
        auto proc = it->first;
        auto variableSet = it->second;
        for (auto it2 = variableSet->getBeginIterator(); it2 != variableSet->getEndIterator(); ++it2) {
            auto variable = *it2;
            result.push_back(std::vector<Entity>{*proc, *variable});
        }
    }
    return result;
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