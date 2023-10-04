template <typename S>
ProcToVarRelationshipManager<S>::ProcToVarRelationshipManager()
    : relationshipStore(std::make_shared<S>(S())) {};

template <typename S>
void ProcToVarRelationshipManager<S>::storeRelationship(std::shared_ptr<Procedure> procedure, std::shared_ptr<Variable> variable) {
    this->relationshipStore->storeRelationship(procedure, variable);
}

template <typename S>
std::vector<std::vector<Entity>> ProcToVarRelationshipManager<S>::getRelationshipProcPair() const {
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
    auto matcher = [](Procedure& proc) {
        return true;
    };
    return ManagerUtils::getLeftEntitiesFromRightKey<Procedure, Variable>(*relationshipStore,
                                                    var,
                                                    matcher);
}

template <typename S>
std::vector<Entity> ProcToVarRelationshipManager<S>::getRelationshipProc() const {
    std::vector<Entity> result;
    for (auto it = relationshipStore->getLeftToRightBeginIterator(); it != relationshipStore->getLeftToRightEndIterator(); ++it) {
		result.push_back(*(it->first));
	}
    return result;
}

template <typename S>
std::vector<Entity> ProcToVarRelationshipManager<S>::getRelationshipVar(Procedure& procedure) const {
    auto matcher = [](Variable& var) {
        return true;
    };
    return ManagerUtils::getRightEntitiesFromLeftKey<Procedure, Variable>(*relationshipStore,
                                                    procedure,
                                                    matcher);
}

template <typename S>
bool ProcToVarRelationshipManager<S>::isRelationship(Procedure& procedure, Variable& var) const {
    auto varStore = relationshipStore->getRightEntitiesOf(std::make_shared<Procedure>(procedure));
    if (varStore == nullptr) {
        return false;
    }

    return varStore->getEntity(std::make_shared<Variable>(var)) != nullptr;
}

template <typename S>
bool ProcToVarRelationshipManager<S>::hasRelationship(Procedure& procedure) const {
    auto got = relationshipStore->getRightEntitiesOf(std::make_shared<Procedure>(procedure));
    return got != nullptr;
}