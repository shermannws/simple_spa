template <typename S, typename R>
ProcToProcRelationshipManager<S, R>::ProcToProcRelationshipManager() : relationshipStore(std::make_shared<S>(S())) {};

template <typename S, typename R>
void ProcToProcRelationshipManager<S, R>::storeRelationship(std::shared_ptr<Procedure> procedure1, std::shared_ptr<Procedure> procedure2, bool isDirect) {
    relationshipStore->storeRelationship(std::make_shared<R>(procedure1, procedure2, isDirect));
}

template <typename S, typename R>
std::vector<std::vector<Entity>> ProcToProcRelationshipManager<S, R>::getRelationshipPair(bool requireDirect) const {
    auto matcher = [requireDirect](R& relationship) {
        return relationship.isDirect() >= requireDirect;
        };
    return ManagerUtils::getEntityPairsFromRelationshipStore<R>(relationshipStore,
        matcher,
        R::getEntityPairFromRelationship);
}

template <typename S, typename R>
std::vector<Entity> ProcToProcRelationshipManager<S, R>::getRelationshipFormer(Procedure& latterProcedure, bool requireDirect) const {
    auto matcher = [latterProcedure, requireDirect](R& relationship) {
        return relationship.isDirect() >= requireDirect && *(relationship.getRightObject()) == latterProcedure;
        };

    return ManagerUtils::getEntitiesFromRelationshipStore<R>(relationshipStore,
        matcher,
        R::getLeftEntityFromRelationship);
}

template <typename S, typename R>
std::vector<Entity> ProcToProcRelationshipManager<S, R>::getRelationshipFormer() const { // Same for Calls and Calls* since Calls* is a superset of Follows
    auto matcher = [](R& relationship) {
        return relationship.isDirect();
        };
    auto result = ManagerUtils::getEntitiesFromRelationshipStore<R>(relationshipStore,
        matcher,
        R::getLeftEntityFromRelationship);
    ManagerUtils::unique(result);
    return result;
}

template <typename S, typename R>
std::vector<Entity> ProcToProcRelationshipManager<S, R>::getRelationshipLatter(Procedure& formerProcedure, bool requireDirect) const {
    auto matcher = [formerProcedure, requireDirect](R& relationship) {
        return relationship.isDirect() >= requireDirect && *(relationship.getLeftObject()) == formerProcedure;
        };
    return ManagerUtils::getEntitiesFromRelationshipStore<R>(relationshipStore,
        matcher,
        R::getRightEntityFromRelationship);
}

template <typename S, typename R>
std::vector<Entity> ProcToProcRelationshipManager<S, R>::getRelationshipLatter() const { // Same for Calls and Calls* since Calls* is a superset of Follows
    auto matcher = [](R& relationship) {
        return relationship.isDirect();
        };
    auto result = ManagerUtils::getEntitiesFromRelationshipStore<R>(relationshipStore,
        matcher,
        R::getRightEntityFromRelationship);
    ManagerUtils::unique(result);
    return result;
}

template <typename S, typename R>
bool ProcToProcRelationshipManager<S, R>::isRelationship(Procedure& procedure1, Procedure& procedure2, bool requireDirect) const {
    std::shared_ptr<R> tempRelationship = std::make_shared<R>(std::make_shared<Procedure>(procedure1), std::make_shared<Procedure>(procedure2), requireDirect);
    std::shared_ptr<R> relationship = relationshipStore->getRelationship(tempRelationship);
    return relationship != nullptr && relationship->isDirect() >= requireDirect;
}

template <typename S, typename R>
bool ProcToProcRelationshipManager<S, R>::hasRelationship() const {
    return !relationshipStore->isEmpty();
}

template <typename S, typename R>
bool ProcToProcRelationshipManager<S, R>::isFormer(Procedure& procedure) const {
    return std::find_if(relationshipStore->getBeginIterator(), relationshipStore->getEndIterator(), [&procedure](std::shared_ptr<R> relationship) {
        return *relationship->getLeftObject() == procedure;
        }) != relationshipStore->getEndIterator();
}

template <typename S, typename R>
bool ProcToProcRelationshipManager<S, R>::isLatter(Procedure& procedure) const {
    return std::find_if(relationshipStore->getBeginIterator(), relationshipStore->getEndIterator(), [&procedure](std::shared_ptr<R> relationship) {
        return *relationship->getRightObject() == procedure;
        }) != relationshipStore->getEndIterator();
}
