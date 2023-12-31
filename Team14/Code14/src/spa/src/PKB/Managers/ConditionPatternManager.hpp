template<typename S>
ConditionPatternManager<S>::ConditionPatternManager() : patternStore(std::make_shared<S>()){};

template<typename S>
void ConditionPatternManager<S>::storePattern(std::shared_ptr<Statement> statement,
                                              std::shared_ptr<std::vector<std::shared_ptr<Variable>>> variables) {
    for (auto &variable: *variables) { this->patternStore->store(statement, variable); }
}

template<typename S>
EntitySet ConditionPatternManager<S>::getAllStmts() const {
    return ManagerUtils::getLeftKeysNoMatch(*patternStore);
}

template<typename S>
EntitySet ConditionPatternManager<S>::getStmtsByVar(Variable &var) const {
    return ManagerUtils::getLeftEntitiesFromRightKeyNoMatch(*patternStore, var);
}

template<typename S>
EntityPairSet ConditionPatternManager<S>::getAllStmtVarPair() const {
    return patternStore->getPairs();
}