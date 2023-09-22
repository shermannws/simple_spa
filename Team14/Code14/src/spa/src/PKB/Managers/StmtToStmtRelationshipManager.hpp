template <typename S, typename R>
StmtToStmtRelationshipManager<S, R>::StmtToStmtRelationshipManager(): relationshipStore(std::make_shared<S>(S())) {};

template <typename S, typename R>
void StmtToStmtRelationshipManager<S, R>::storeRelationship(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2, bool isDirect) {
    relationshipStore->storeRelationship(std::make_shared<R>(statement1, statement2, isDirect));
}

template <typename S, typename R>
std::vector<std::vector<Entity>> StmtToStmtRelationshipManager<S, R>::getRelationshipPair(StatementType formerType, StatementType latterType, bool requireDirect) const {
    auto matcher = [formerType, latterType, requireDirect](R& relationship) {
        return relationship.isDirect() >= requireDirect && relationship.getLeftObject()->isStatementType(formerType) && relationship.getRightObject()->isStatementType(latterType);
    };
    return ManagerUtils::getEntityPairsFromStore<S, R>(relationshipStore,
                                                       matcher,
                                                       R::getEntityPairFromRelationship);
}

template <typename S, typename R>
std::vector<Entity> StmtToStmtRelationshipManager<S, R>::getRelationshipTypeStmt(StatementType type, Statement& statement, bool requireDirect) const {
    auto matcher = [type, statement, requireDirect](R& relationship) {
        return relationship.isDirect() >= requireDirect && *(relationship.getRightObject()) == statement && relationship.getLeftObject()->isStatementType(type);
    };

    return ManagerUtils::getEntitiesFromStore<S, R>(relationshipStore,
                                                    matcher,
                                                    R::getLeftEntityFromRelationship);
}

template <typename S, typename R>
std::vector<Entity> StmtToStmtRelationshipManager<S, R>::getRelationshipTypeWildcard(StatementType type) const { // Same for Follows and Follows* since Follows* is a superset of Follows
    auto matcher = [type](R& relationship) {
        return relationship.isDirect() && relationship.getLeftObject()->isStatementType(type);
    };
    return ManagerUtils::getEntitiesFromStore<S, R>(relationshipStore,
                                                    matcher,
                                                    R::getLeftEntityFromRelationship);
}

template <typename S, typename R>
std::vector<Entity> StmtToStmtRelationshipManager<S, R>::getRelationshipStmtType(Statement& statement, StatementType type, bool requireDirect) const {
    auto matcher = [statement, type, requireDirect](R& relationship) {
        return relationship.isDirect() >= requireDirect && *(relationship.getLeftObject()) == statement && relationship.getRightObject()->isStatementType(type);
    };
    return ManagerUtils::getEntitiesFromStore<S, R>(relationshipStore,
                                                    matcher,
                                                    R::getRightEntityFromRelationship);
}

template <typename S, typename R>
std::vector<Entity> StmtToStmtRelationshipManager<S, R>::getRelationshipWildcardType(StatementType type) const { // Same for Follows and Follows* since Follows* is a superset of Follows
    auto matcher = [type](R& relationship) {
        return relationship.isDirect() && relationship.getRightObject()->isStatementType(type);
    };
    return ManagerUtils::getEntitiesFromStore<S, R>(relationshipStore,
                                                    matcher,
                                                    R::getRightEntityFromRelationship);
}

template <typename S, typename R>
bool StmtToStmtRelationshipManager<S, R>::isRelationship(Statement& statement1, Statement& statement2, bool requireDirect) const {
    std::shared_ptr<R> tempRelationship = std::make_shared<R>(std::make_shared<Statement>(statement1), std::make_shared<Statement>(statement2), requireDirect);
    std::shared_ptr<R> relationship = relationshipStore->getRelationship(tempRelationship);
    return relationship != nullptr && relationship->isDirect() >= requireDirect;
}

template <typename S, typename R>
bool StmtToStmtRelationshipManager<S, R>::hasRelationship() const {
    return !relationshipStore->isEmpty();
}

template <typename S, typename R>
bool StmtToStmtRelationshipManager<S, R>::isFormer(Statement& statement) const {
    return std::find_if(relationshipStore->getBeginIterator(), relationshipStore->getEndIterator(), [&statement](std::shared_ptr<R> relationship) {
        return *relationship->getLeftObject() == statement;
    }) != relationshipStore->getEndIterator();
}

template <typename S, typename R>
bool StmtToStmtRelationshipManager<S, R>::isLatter(Statement& statement) const {
    return std::find_if(relationshipStore->getBeginIterator(), relationshipStore->getEndIterator(), [&statement](std::shared_ptr<R> relationship) {
        return *relationship->getRightObject() == statement;
    }) != relationshipStore->getEndIterator();
}
