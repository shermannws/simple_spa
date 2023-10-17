template<typename S>
StmtToStmtRelationshipManager<S>::StmtToStmtRelationshipManager()
    : relationshipStore(std::make_shared<S>()),
      starRelationshipStore(std::make_shared<S>()){};

template<typename S>
void StmtToStmtRelationshipManager<S>::storeRelationship(
        std::shared_ptr<Statement> statement1,
        std::shared_ptr<Statement> statement2, bool isDirect) {
    starRelationshipStore->storeRelationship(statement1, statement2);
    if (isDirect) {
        relationshipStore->storeRelationship(statement1, statement2);
    }
}

template<typename S>
std::vector<std::vector<Entity>>
StmtToStmtRelationshipManager<S>::getRelationshipPair(
        StatementType formerType, StatementType latterType,
        bool requireDirect) const {
    auto leftMatcher = [formerType](Statement &stmt) {
        return stmt.isStatementType(formerType);
    };

    auto rightMatcher = [latterType](Statement &stmt) {
        return stmt.isStatementType(latterType);
    };

    return ManagerUtils::getPairs<Entity,
                                  RelationshipStore<Statement, Statement>,
                                  Statement, Statement>(
            requireDirect ? *relationshipStore : *starRelationshipStore,
            leftMatcher, rightMatcher);
}

template<typename S>
std::vector<Entity> StmtToStmtRelationshipManager<S>::getRelationshipTypeStmt(
        StatementType type, Statement &statement, bool requireDirect) const {
    return ManagerUtils::getLeftEntitiesFromRightKeyStmtMatch<Statement>(
            requireDirect ? *relationshipStore : *starRelationshipStore,
            statement, type);
}

template<typename S>
std::vector<Entity>
StmtToStmtRelationshipManager<S>::getRelationshipTypeWildcard(
        StatementType type) const {
    return ManagerUtils::getLeftKeysStmtMatch<Statement>(*relationshipStore,
                                                         type);
}

template<typename S>
std::vector<Entity>
StmtToStmtRelationshipManager<S>::getRelationshipTypeWildcard(
        StatementType type, bool requireDirect) const {
    return ManagerUtils::getLeftKeysStmtMatch<Statement>(
            requireDirect ? *relationshipStore : *starRelationshipStore, type);
}

template<typename S>
std::vector<Entity> StmtToStmtRelationshipManager<S>::getRelationshipStmtType(
        Statement &statement, StatementType type, bool requireDirect) const {
    return ManagerUtils::getRightEntitiesFromLeftKeyStmtMatch<Statement>(
            requireDirect ? *relationshipStore : *starRelationshipStore,
            statement, type);
}

template<typename S>
std::vector<Entity>
StmtToStmtRelationshipManager<S>::getRelationshipWildcardType(
        StatementType type) const {
    return ManagerUtils::getRightKeysStmtMatch<Statement>(*relationshipStore,
                                                          type);
}

template<typename S>
std::vector<Entity>
StmtToStmtRelationshipManager<S>::getRelationshipWildcardType(
        StatementType type, bool requireDirect) const {
    return ManagerUtils::getRightKeysStmtMatch<Statement>(
            requireDirect ? *relationshipStore : *starRelationshipStore, type);
}

template<typename S>
bool StmtToStmtRelationshipManager<S>::isRelationship(
        Statement &statement1, Statement &statement2,
        bool requireDirect) const {
    return ManagerUtils::mapContains<Statement, Statement>(
            requireDirect ? *relationshipStore : *starRelationshipStore,
            statement1, statement2);
}

template<typename S>
bool StmtToStmtRelationshipManager<S>::hasRelationship() const {
    return !relationshipStore->isEmpty();
}

template<typename S>
bool StmtToStmtRelationshipManager<S>::isFormer(Statement &statement) const {
    return relationshipStore->getRightEntitiesOf(
                   std::make_shared<Statement>(statement)) != nullptr;
}

template<typename S>
bool StmtToStmtRelationshipManager<S>::isLatter(Statement &statement) const {
    return relationshipStore->getLeftEntitiesOf(
                   std::make_shared<Statement>(statement)) != nullptr;
}
