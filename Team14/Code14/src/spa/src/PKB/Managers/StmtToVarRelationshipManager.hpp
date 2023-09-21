template <typename S, typename R>
StmtToVarRelationshipManager<S, R>::StmtToVarRelationshipManager()
        : relationshipStore(std::make_shared<S>(S())) {};

template <typename S, typename R>
void StmtToVarRelationshipManager<S, R>::storeRelationship(std::shared_ptr<Statement> statement, std::shared_ptr<Variable> variable) {
    this->relationshipStore->storeRelationship(std::make_shared<R>(R(statement, variable)));
}

template <typename S, typename R>
std::vector<std::vector<Entity>> StmtToVarRelationshipManager<S, R>::getRelationshipStmtPair(StatementType type) const {
    auto matcher = [type](R& relationship) {
        return relationship.getLeftObject()->isStatementType(type);
    };
    return ManagerUtils::getEntityPairsFromStore<S, R>(relationshipStore,
                                                       matcher,
                                                       R::getEntityPairFromRelationship);
}

template <typename S, typename R>
std::vector<Entity> StmtToVarRelationshipManager<S, R>::getRelationshipTypeIdent(StatementType type, Variable& var) const {
    auto matcher = [type, var](R& relationship) {
        return *(relationship.getRightObject()) == var && relationship.getLeftObject()->isStatementType(type);
    };
    return ManagerUtils::getEntitiesFromStore<S, R>(relationshipStore,
                                                    matcher,
                                                    R::getLeftEntityFromRelationship);
}

template <typename S, typename R>
std::vector<Entity> StmtToVarRelationshipManager<S, R>::getRelationshipStmt(StatementType type) const {
    auto set = std::unordered_set<Entity>();

    auto matcher = [type, &set](R& relationship) {
        return relationship.getLeftObject()->isStatementType(type) && set.find(*(relationship.getLeftEntity())) == set.end();
    };

    auto getter = [&set](R& relationship) {
        set.insert(*(relationship.getLeftEntity()));
        return *(relationship.getLeftEntity());
    };
    return ManagerUtils::getEntitiesFromStore<S, R>(relationshipStore,
                                                    matcher,
                                                    getter);
}

template <typename S, typename R>
std::vector<Entity> StmtToVarRelationshipManager<S, R>::getRelationshipVar(Statement& stmt) const {
    auto matcher = [&stmt](R& relationship) {
        return *(relationship.getLeftObject()) == stmt;
    };
    return ManagerUtils::getEntitiesFromStore<S, R>(relationshipStore,
                                                    matcher,
                                                    R::getRightEntityFromRelationship);
}

template <typename S, typename R>
bool StmtToVarRelationshipManager<S, R>::isRelationship(Statement& stmt, Variable& var) const {
    return relationshipStore->getRelationship(std::make_shared<R>(std::make_shared<Statement>(stmt), std::make_shared<Variable>(var))) != nullptr;
}

template <typename S, typename R>
bool StmtToVarRelationshipManager<S, R>::hasRelationship(Statement& stmt) const {
    return std::find_if(relationshipStore->getBeginIterator(), relationshipStore->getEndIterator(), [&stmt](std::shared_ptr<R> relationship) {
        return *relationship->getLeftEntity() == stmt;
    }) != relationshipStore->getEndIterator();
}