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
    return relationshipStore->getRightEntitiesOf(std::make_shared<Procedure>(procedure)) != nullptr;
}

template <typename S>
void ProcToVarRelationshipManager<S>::calculateProcVarRelationshipForCallers(std::shared_ptr<CallsRelationshipManager> callManager) {
    for (auto it = relationshipStore->getLeftToRightBeginIterator(); it != relationshipStore->getLeftToRightEndIterator(); ++it) {
        auto proc = it->first;
        auto variableSet = it->second;
        auto callersOfProc = callManager->getCallsFormerAsProcedure(*proc);
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
};