template<typename S>
StmtToVarRelationshipManager<S>::StmtToVarRelationshipManager() : relationshipStore(std::make_shared<S>()){};

template<typename S>
void StmtToVarRelationshipManager<S>::storeRelationship(std::shared_ptr<Statement> statement,
                                                        std::shared_ptr<Variable> variable) {
    this->relationshipStore->storeRelationship(statement, variable);
}

template<typename S>
std::unordered_set<std::vector<Entity>>
StmtToVarRelationshipManager<S>::getRelationshipStmtPair(StatementType type) const {
    auto leftMatcher = [type](Statement &stmt) { return stmt.isStatementType(type); };

    auto rightMatcher = [](Variable &var) { return true; };

    return ManagerUtils::getPairs<Entity, RelationshipStore<Statement, Variable>, Statement, Variable>(
            *relationshipStore, leftMatcher, rightMatcher);
}

template<typename S>
std::unordered_set<Entity> StmtToVarRelationshipManager<S>::getRelationshipTypeIdent(StatementType type,
                                                                                     Variable &var) const {
    return ManagerUtils::getLeftEntitiesFromRightKeyStmtMatch<Variable>(*relationshipStore, var, type);
}

template<typename S>
std::unordered_set<Entity> StmtToVarRelationshipManager<S>::getRelationshipStmt(StatementType type) const {
    return ManagerUtils::getLeftKeysStmtMatch<Variable>(*relationshipStore, type);
}

template<typename S>
std::unordered_set<Entity> StmtToVarRelationshipManager<S>::getRelationshipVar(Statement &stmt) const {
    return ManagerUtils::getRightEntitiesFromLeftKeyNoMatch<Statement, Variable>(*relationshipStore, stmt);
}

template<typename S>
bool StmtToVarRelationshipManager<S>::isRelationship(Statement &stmt, Variable &var) const {
    return ManagerUtils::mapContains(*relationshipStore, stmt, var);
}

template<typename S>
bool StmtToVarRelationshipManager<S>::hasRelationship(Statement &stmt) const {
    return relationshipStore->getRightEntitiesOf(std::make_shared<Statement>(stmt)) != nullptr;
}