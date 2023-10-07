template <typename S>
StmtToStmtRelationshipManager<S>::StmtToStmtRelationshipManager(): relationshipStore(std::make_shared<S>()),
                                                                 starRelationshipStore(std::make_shared<S>()) {};

template <typename S>
void StmtToStmtRelationshipManager<S>::storeRelationship(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2, bool isDirect) {
    starRelationshipStore->storeRelationship(statement1, statement2);
    if (isDirect) {
        relationshipStore->storeRelationship(statement1, statement2);
    }
}

template <typename S>
std::vector<std::vector<Entity>> StmtToStmtRelationshipManager<S>::getRelationshipPair(StatementType formerType, StatementType latterType, bool requireDirect) const {
    std::vector<std::vector<Entity>> result;
    auto store = requireDirect ? relationshipStore : starRelationshipStore;
    for (auto it = store->getLeftToRightBeginIterator(); it != store->getLeftToRightEndIterator(); ++it) {
        auto former = it->first;
        auto latterSet = it->second;
        if (former->isStatementType(formerType)) {
            for (auto it2 = latterSet->getBeginIterator(); it2 != latterSet->getEndIterator(); ++it2) {
                auto latter = *it2;
                if (latter->isStatementType(latterType)) {
                    result.push_back(std::vector<Entity>{*former, *latter});
                }
            }
        }
    }
    return result;
}

template <typename S>
std::vector<Entity> StmtToStmtRelationshipManager<S>::getRelationshipTypeStmt(StatementType type, Statement& statement, bool requireDirect) const {
    auto matcher = [type](Statement& stmt) {
        return stmt.isStatementType(type);
    };

    return ManagerUtils::getLeftEntitiesFromRightKey<Statement, Statement>(
                                                    requireDirect ? *relationshipStore : *starRelationshipStore,
                                                     statement,
                                                     matcher);
}

template <typename S>
std::vector<Entity> StmtToStmtRelationshipManager<S>::getRelationshipTypeWildcard(StatementType type) const { // Same for Follows and Follows* since Follows* is a superset of Follows
    std::vector<Entity> result;
    std::for_each(relationshipStore->getLeftToRightBeginIterator(), relationshipStore->getLeftToRightEndIterator(), [&result, type](const auto pair) {
        if (pair.first->isStatementType(type)) {
            result.push_back(*pair.first);
        }
    });
    return result;
}

template <typename S>
std::vector<Entity> StmtToStmtRelationshipManager<S>::getRelationshipStmtType(Statement& statement, StatementType type, bool requireDirect) const {
    auto matcher = [type](Statement& stmt) {
        return stmt.isStatementType(type);
    };

    return ManagerUtils::getRightEntitiesFromLeftKey<Statement, Statement>(
                                                    requireDirect ? *relationshipStore : *starRelationshipStore,
                                                     statement,
                                                     matcher);
}

template <typename S>
std::vector<Entity> StmtToStmtRelationshipManager<S>::getRelationshipWildcardType(StatementType type) const { // Same for Follows and Follows* since Follows* is a superset of Follows
    std::vector<Entity> result;
    std::for_each(relationshipStore->getRightToLeftBeginIterator(), relationshipStore->getRightToLeftEndIterator(), [&result, type](const auto pair) {
        if (pair.first->isStatementType(type)) {
            result.push_back(*pair.first);
        }
    });
    return result;
}

template <typename S>
bool StmtToStmtRelationshipManager<S>::isRelationship(Statement& statement1, Statement& statement2, bool requireDirect) const {
    auto store = requireDirect ? relationshipStore : starRelationshipStore;
    auto stmtStore = store->getRightEntitiesOf(std::make_shared<Statement>(statement1));
    if (stmtStore == nullptr) {
        return false;
    }
    return stmtStore->getEntity(std::make_shared<Statement>(statement2)) != nullptr;
}

template <typename S>
bool StmtToStmtRelationshipManager<S>::hasRelationship() const {
    return !relationshipStore->isEmpty();
}

template <typename S>
bool StmtToStmtRelationshipManager<S>::isFormer(Statement& statement) const {
    return relationshipStore->getRightEntitiesOf(std::make_shared<Statement>(statement)) != nullptr;
}

template <typename S>
bool StmtToStmtRelationshipManager<S>::isLatter(Statement& statement) const {
    return relationshipStore->getLeftEntitiesOf(std::make_shared<Statement>(statement)) != nullptr;
}
