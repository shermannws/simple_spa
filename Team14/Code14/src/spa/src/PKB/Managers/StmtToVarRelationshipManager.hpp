template <typename S>
StmtToVarRelationshipManager<S>::StmtToVarRelationshipManager()
        : relationshipStore(std::make_shared<S>()) {};

template <typename S>
void StmtToVarRelationshipManager<S>::storeRelationship(std::shared_ptr<Statement> statement, std::shared_ptr<Variable> variable) {
    this->relationshipStore->storeRelationship(statement, variable);
}

template <typename S>
std::vector<std::vector<Entity>> StmtToVarRelationshipManager<S>::getRelationshipStmtPair(StatementType type) const {
    // TODO: Maybe refactor to ManagerUtils
    std::vector<std::vector<Entity>> result;
    for (auto it = relationshipStore->getLeftToRightBeginIterator(); it != relationshipStore->getLeftToRightEndIterator(); ++it) {
        auto stmt = it->first;
        auto variableSet = it->second;
        if (stmt->isStatementType(type)) {
            for (auto it2 = variableSet->getBeginIterator(); it2 != variableSet->getEndIterator(); ++it2) {
                auto variable = *it2;
                result.push_back(std::vector<Entity>{*stmt, *variable});
            }
        }
    }
    return result;
}

template <typename S>
std::vector<Entity> StmtToVarRelationshipManager<S>::getRelationshipTypeIdent(StatementType type, Variable& var) const {
    return ManagerUtils::getLeftEntitiesFromRightKeyStmtMatch<Variable>(*relationshipStore, var, type);
}

template <typename S>
std::vector<Entity> StmtToVarRelationshipManager<S>::getRelationshipStmt(StatementType type) const {
    return ManagerUtils::getLeftKeysStmtMatch<Variable>(*relationshipStore, type);
}

template <typename S>
std::vector<Entity> StmtToVarRelationshipManager<S>::getRelationshipVar(Statement& stmt) const {
    return ManagerUtils::getRightEntitiesFromLeftKeyNoMatch<Statement, Variable>(*relationshipStore, stmt);
}

template <typename S>
bool StmtToVarRelationshipManager<S>::isRelationship(Statement& stmt, Variable& var) const {
    return ManagerUtils::mapContains(*relationshipStore, stmt, var);
}

template <typename S>
bool StmtToVarRelationshipManager<S>::hasRelationship(Statement& stmt) const {
    return relationshipStore->getRightEntitiesOf(std::make_shared<Statement>(stmt)) != nullptr;
}