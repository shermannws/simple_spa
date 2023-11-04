template<typename S>
StmtToVarRelationshipManager<S>::StmtToVarRelationshipManager() : relationshipStore(std::make_shared<S>()){};

template<typename S>
void StmtToVarRelationshipManager<S>::storeRelationship(std::shared_ptr<Statement> statement,
                                                        std::shared_ptr<Variable> variable) {
    this->relationshipStore->storeRelationship(statement, variable);
}

template<typename S>
EntityPairSet StmtToVarRelationshipManager<S>::getRelationshipStmtPair(StatementType type) const {
    if (!ManagerUtils::isStmtTypeAllowed(clauseGroup, type)) { return EntityPairSet(); }
    if (type == StatementType::Stmt) { return relationshipStore->getPairs(); }

    auto leftMatcher = [type](std::shared_ptr<Statement> stmt) { return stmt->isStatementType(type); };
    auto rightMatcher = [](std::shared_ptr<Variable> var) { return true; };
    return ManagerUtils::getPairs<Entity, RelationshipStore<Statement, Variable>, Statement, Variable>(
            *relationshipStore, leftMatcher, rightMatcher);
}

template<typename S>

EntitySet StmtToVarRelationshipManager<S>::getRelationshipTypeIdent(StatementType type, Variable &var) const {
    if (!ManagerUtils::isStmtTypeAllowed(clauseGroup, type)) { return EntitySet(); }
    return ManagerUtils::getLeftEntitiesFromRightKeyStmtMatch<Variable>(*relationshipStore, var, type);
}

template<typename S>
EntitySet StmtToVarRelationshipManager<S>::getRelationshipStmt(StatementType type) const {
    if (!ManagerUtils::isStmtTypeAllowed(clauseGroup, type)) { return EntitySet(); }
    return ManagerUtils::getLeftKeysStmtMatch<Variable>(*relationshipStore, type);
}

template<typename S>
EntitySet StmtToVarRelationshipManager<S>::getRelationshipVar(Statement &stmt) const {
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