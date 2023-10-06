template <typename S>
ProcToProcRelationshipManager<S>::ProcToProcRelationshipManager() : relationshipStore(std::make_shared<S>()), starRelationshipStore(std::make_shared<S>()) {}

template <typename S>
void ProcToProcRelationshipManager<S>::storeRelationship(std::shared_ptr<Procedure> procedure1, std::shared_ptr<Procedure> procedure2, bool isDirect) {
    starRelationshipStore->storeRelationship(procedure1, procedure2);
    if (isDirect) {
        relationshipStore->storeRelationship(procedure1, procedure2);
    }
}

template <typename S>
std::vector<std::vector<Entity>> ProcToProcRelationshipManager<S>::getRelationshipPair(bool requireDirect) const {
    std::vector<std::vector<Entity>> result;
    auto store = requireDirect ? relationshipStore : starRelationshipStore;
    for (auto it = store->getLeftToRightBeginIterator(); it != store->getLeftToRightEndIterator(); ++it) {
        auto former = it->first;
        auto latterSet = it->second;
        for (auto it2 = latterSet->getBeginIterator(); it2 != latterSet->getEndIterator(); ++it2) {
            auto latter = *it2;
            result.push_back(std::vector<Entity>{*former, *latter});
        }
    }
    return result;
}

template <typename S>
std::vector<Entity> ProcToProcRelationshipManager<S>::getRelationshipFormer(Procedure& latterProcedure, bool requireDirect) const {
    return ManagerUtils::getLeftEntitiesFromRightKeyNoMatch<Procedure, Procedure>(requireDirect ? *relationshipStore : *starRelationshipStore, latterProcedure);
}

template <typename S>
std::vector<Entity> ProcToProcRelationshipManager<S>::getRelationshipFormer() const { // Same for Calls and Calls* since Calls* is a superset of Follows
    return ManagerUtils::getLeftKeysNoMatch<Procedure, Procedure>(*relationshipStore);
}

template <typename S>
std::vector<Entity> ProcToProcRelationshipManager<S>::getRelationshipLatter(Procedure& formerProcedure, bool requireDirect) const {
    return ManagerUtils::getRightEntitiesFromLeftKeyNoMatch<Procedure, Procedure>(requireDirect ? *relationshipStore : *starRelationshipStore, formerProcedure);
}

template <typename S>
std::vector<Entity> ProcToProcRelationshipManager<S>::getRelationshipLatter() const { // Same for Calls and Calls* since Calls* is a superset of Follows
    return ManagerUtils::getRightKeysNoMatch<Procedure, Procedure>(*relationshipStore);
}

template <typename S>
bool ProcToProcRelationshipManager<S>::isRelationship(Procedure& procedure1, Procedure& procedure2, bool requireDirect) const {
    return ManagerUtils::mapContains<Procedure, Procedure>(requireDirect ? *relationshipStore : *starRelationshipStore, procedure1,
        procedure2);
}

template <typename S>
bool ProcToProcRelationshipManager<S>::hasRelationship() const {
    return !relationshipStore->isEmpty();
}

template <typename S>
bool ProcToProcRelationshipManager<S>::isFormer(Procedure& procedure) const {
    return relationshipStore->getRightEntitiesOf(std::make_shared<Procedure>(procedure)) != nullptr;
}

template <typename S>
bool ProcToProcRelationshipManager<S>::isLatter(Procedure& procedure) const {
    return relationshipStore->getLeftEntitiesOf(std::make_shared<Procedure>(procedure)) != nullptr;
}
