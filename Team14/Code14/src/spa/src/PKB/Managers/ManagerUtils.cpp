#include "ManagerUtils.h"

std::unordered_map<ClauseGroup, std::unordered_set<StatementType>> ManagerUtils::allowedStmtTypesMap = {
        {ClauseGroup::Parent, {StatementType::Stmt, StatementType::While, StatementType::If}},
        {ClauseGroup::Uses,
         {StatementType::Stmt, StatementType::Assign, StatementType::While, StatementType::If, StatementType::Call,
          StatementType::Print}},
        {ClauseGroup::Modifies,
         {StatementType::Stmt, StatementType::Assign, StatementType::While, StatementType::If, StatementType::Call,
          StatementType::Read}},
        {ClauseGroup::Affects, {StatementType::Stmt, StatementType::Assign}},
};

bool ManagerUtils::isStmtTypeAllowed(ClauseGroup clauseGroup, StatementType statementType) {
    return (allowedStmtTypesMap.find(clauseGroup) == allowedStmtTypesMap.end()) ||
           (allowedStmtTypesMap[clauseGroup].find(statementType) != allowedStmtTypesMap[clauseGroup].end());
}

template<typename E, typename S, typename R>
std::unordered_set<E> ManagerUtils::getFromSetStore(std::shared_ptr<S> store, std::function<bool(R &)> matcher,
                                                    std::function<E(R &)> getter) {
    auto result = std::unordered_set<E>();
    for (auto it = store->getBeginIterator(); it != store->getEndIterator(); it++) {
        if (matcher(**it)) { result.insert(getter(**it)); }
    }
    return result;
}

template<typename S, typename R>
std::unordered_set<Entity> ManagerUtils::getEntitiesFromStore(std::shared_ptr<S> store,
                                                              std::function<bool(R &)> matcher,
                                                              std::function<Entity(R &)> getter) {
    return getFromSetStore<Entity, S, R>(store, matcher, getter);
}

template<typename E>
std::unordered_set<Entity> ManagerUtils::getEntitiesFromEntityStore(std::shared_ptr<EntityStore<E>> store,
                                                                    std::function<bool(E &)> matcher,
                                                                    std::function<Entity(E &)> getter) {
    return getFromSetStore<Entity, EntityStore<E>, E>(store, matcher, getter);
}

template<typename S, typename R>
std::unordered_set<std::vector<Entity>>
ManagerUtils::getEntityPairsFromStore(std::shared_ptr<S> store, std::function<bool(R &)> matcher,
                                      std::function<std::vector<Entity>(R &)> getter) {
    return getFromSetStore<std::vector<Entity>, S, R>(store, matcher, getter);
}

template<typename E, typename S, typename K, typename V, typename R>
std::unordered_set<R> ManagerUtils::getFromMapStore(S &store, std::function<std::shared_ptr<E>(S &, K &)> getter,
                                                    K &key, std::function<bool(V &)> matcher) {
    auto result = std::unordered_set<R>();
    auto resultSet = getter(store, key);
    if (resultSet == nullptr) { return result; }
    for (auto it = resultSet->getBeginIterator(); it != resultSet->getEndIterator(); it++) {
        if (matcher(**it)) { result.insert(**it); }
    }
    return result;
}

template<typename L, typename R>
std::unordered_set<Entity> ManagerUtils::getRightEntitiesFromLeftKeyNoMatch(RelationshipStore<L, R> &store, L &key) {
    auto getter = [](RelationshipStore<L, R> &store, L &key) {
        return store.getRightEntitiesOf(std::make_shared<L>(key));
    };
    auto matcher = [](R &entity) { return true; };
    return getFromMapStore<EntityStore<R>, RelationshipStore<L, R>, L, R, Entity>(store, getter, key, matcher);
}

template<typename L, typename R>
std::unordered_set<Entity> ManagerUtils::getLeftEntitiesFromRightKeyNoMatch(RelationshipStore<L, R> &store, R &key) {
    auto getter = [](RelationshipStore<L, R> &store, R &key) {
        return store.getLeftEntitiesOf(std::make_shared<R>(key));
    };
    auto matcher = [](L &entity) { return true; };
    return getFromMapStore<EntityStore<L>, RelationshipStore<L, R>, R, L, Entity>(store, getter, key, matcher);
}

std::unordered_set<Entity> ManagerUtils::getLeftEntitiesFromRightKeyNoMatch(ConditionPatternStore &store,
                                                                            Variable &key) {
    auto getter = [](ConditionPatternStore &store, Variable &key) {
        return store.getLeftEntitiesOf(std::make_shared<Variable>(key));
    };
    auto matcher = [](Statement &entity) { return true; };
    return getFromMapStore<EntityStore<Statement>, ConditionPatternStore, Variable, Statement, Entity>(store, getter,
                                                                                                       key, matcher);
}

template<typename R>
std::unordered_set<Entity> ManagerUtils::getLeftEntitiesFromRightKeyStmtMatch(RelationshipStore<Statement, R> &store,
                                                                              R &key, StatementType type) {
    auto getter = [](RelationshipStore<Statement, R> &store, R &key) {
        return store.getLeftEntitiesOf(std::make_shared<R>(key));
    };
    auto matcher = [type](Statement &stmt) { return stmt.isStatementType(type); };
    return getFromMapStore<EntityStore<Statement>, RelationshipStore<Statement, R>, R, Statement, Entity>(store, getter,
                                                                                                          key, matcher);
}

template<typename L>
std::unordered_set<Entity> ManagerUtils::getRightEntitiesFromLeftKeyStmtMatch(RelationshipStore<L, Statement> &store,
                                                                              L &key, StatementType type) {
    auto getter = [](RelationshipStore<L, Statement> &store, L &key) {
        return store.getRightEntitiesOf(std::make_shared<L>(key));
    };
    auto matcher = [type](Statement &stmt) { return stmt.isStatementType(type); };
    return getFromMapStore<EntityStore<Statement>, RelationshipStore<L, Statement>, L, Statement, Entity>(store, getter,
                                                                                                          key, matcher);
}

template<typename E>
void ManagerUtils::unique(std::vector<E> &v) {
    std::unordered_set<E> s(v.begin(), v.end());
    v.assign(s.begin(), s.end());
}

template<typename S, typename P>
void ManagerUtils::addStmtVarFromProcVar(std::shared_ptr<S> stmtVarManager,
                                         std::shared_ptr<RelationshipStore<Procedure, Statement>> procStmtStore,
                                         std::shared_ptr<P> procVarManager) {
    for (auto it = procStmtStore->getLeftToRightBeginIterator(); it != procStmtStore->getLeftToRightEndIterator();
         it++) {
        auto proc = it->first;
        auto stmtsStore = it->second;
        auto vars = procVarManager->getRhsVarAsVariables(proc);
        if (vars == nullptr) { continue; }
        for (auto it2 = stmtsStore->getBeginIterator(); it2 != stmtsStore->getEndIterator(); it2++) {
            for (auto it3 = vars->getBeginIterator(); it3 != vars->getEndIterator(); it3++) {
                stmtVarManager->storeRelationship(*it2, *it3);
            }
        }
    }
}

template<typename L, typename R>
bool ManagerUtils::mapContains(RelationshipStore<L, R> &store, L &key, R &value) {
    auto valueStore = store.getRightEntitiesOf(std::make_shared<L>(key));
    if (valueStore == nullptr) { return false; }
    return valueStore->getEntity(std::make_shared<R>(value)) != nullptr;
}

template<typename K, typename V, typename R>
std::unordered_set<R> ManagerUtils::getKeys(
        typename std::unordered_map<std::shared_ptr<K>, std::shared_ptr<EntityStore<V>>>::iterator beginItr,
        typename std::unordered_map<std::shared_ptr<K>, std::shared_ptr<EntityStore<V>>>::iterator endItr,
        std::function<bool(K &)> matcher) {
    auto result = std::unordered_set<R>();
    for (auto it = beginItr; it != endItr; it++) {
        if (matcher(*(it->first))) { result.insert(*(it->first)); }
    }
    return result;
}

template<typename K, typename V>
std::unordered_set<Entity> ManagerUtils::getKeysNoMatch(
        typename std::unordered_map<std::shared_ptr<K>, std::shared_ptr<EntityStore<V>>>::iterator beginItr,
        typename std::unordered_map<std::shared_ptr<K>, std::shared_ptr<EntityStore<V>>>::iterator endItr) {
    auto matcher = [](K &entity) { return true; };
    return getKeys<K, V, Entity>(beginItr, endItr, matcher);
}

template<typename K, typename V>
std::unordered_set<Entity> ManagerUtils::getLeftKeysNoMatch(RelationshipStore<K, V> &store) {
    return getKeysNoMatch<K, V>(store.getLeftToRightBeginIterator(), store.getLeftToRightEndIterator());
}

std::unordered_set<Entity> ManagerUtils::getLeftKeysNoMatch(ConditionPatternStore &store) {
    return getKeysNoMatch<Statement, Variable>(store.getLeftToRightBeginIterator(), store.getLeftToRightEndIterator());
}

template<typename K, typename V>
std::unordered_set<Entity> ManagerUtils::getRightKeysNoMatch(RelationshipStore<K, V> &store) {
    return getKeysNoMatch<K, V>(store.getRightToLeftBeginIterator(), store.getRightToLeftEndIterator());
}

template<typename V>
std::unordered_set<Entity> ManagerUtils::getKeysStmtMatch(
        typename std::unordered_map<std::shared_ptr<Statement>, std::shared_ptr<EntityStore<V>>>::iterator beginItr,
        typename std::unordered_map<std::shared_ptr<Statement>, std::shared_ptr<EntityStore<V>>>::iterator endItr,
        StatementType type) {
    auto matcher = [type](Statement &stmt) { return stmt.isStatementType(type); };
    return getKeys<Statement, V, Entity>(beginItr, endItr, matcher);
}

template<typename V>
std::unordered_set<Entity> ManagerUtils::getLeftKeysStmtMatch(RelationshipStore<Statement, V> &store,
                                                              StatementType type) {
    return getKeysStmtMatch<V>(store.getLeftToRightBeginIterator(), store.getLeftToRightEndIterator(), type);
}

template<typename K>
std::unordered_set<Entity> ManagerUtils::getRightKeysStmtMatch(RelationshipStore<K, Statement> &store,
                                                               StatementType type) {
    return getKeysStmtMatch<K>(store.getRightToLeftBeginIterator(), store.getRightToLeftEndIterator(), type);
}

template<typename R, typename S, typename K, typename V>
std::unordered_set<std::vector<R>> ManagerUtils::getPairs(S &store, std::function<bool(K &)> leftMatcher,
                                                          std::function<bool(V &)> rightMatcher) {
    std::unordered_set<std::vector<R>> result;
    for (auto it = store.getLeftToRightBeginIterator(); it != store.getLeftToRightEndIterator(); ++it) {
        auto former = it->first;
        auto latterSet = it->second;
        if (leftMatcher(*former)) {
            for (auto it2 = latterSet->getBeginIterator(); it2 != latterSet->getEndIterator(); ++it2) {
                auto latter = *it2;
                if (rightMatcher(*latter)) { result.insert(std::vector<R>{*former, *latter}); }
            }
        }
    }
    return result;
}

template<typename K, typename V>
std::unordered_set<std::vector<Entity>> ManagerUtils::getPairsNoMatch(RelationshipStore<K, V> &store) {
    auto leftMatcher = [](K &entity) { return true; };
    auto rightMatcher = [](V &entity) { return true; };
    return getPairs<Entity, RelationshipStore<K, V>, K, V>(store, leftMatcher, rightMatcher);
}

std::unordered_set<std::vector<Entity>> ManagerUtils::getPairsNoMatch(ConditionPatternStore &store) {
    auto leftMatcher = [](Statement &entity) { return true; };
    auto rightMatcher = [](Variable &entity) { return true; };
    return getPairs<Entity, ConditionPatternStore, Statement, Variable>(store, leftMatcher, rightMatcher);
}

template<typename K>
std::unordered_set<Entity> ManagerUtils::getLeftKeysMatchRight(RelationshipStore<K, K> &store,
                                                               std::function<bool(K &)> leftMatcher) {
    std::unordered_set<Entity> result;
    for (auto it = store.getLeftToRightBeginIterator(); it != store.getLeftToRightEndIterator(); ++it) {
        auto former = it->first;
        auto latterSet = it->second;
        if (leftMatcher(*former)) {
            if (latterSet->getEntity(former) != nullptr) { result.insert(*former); }
        }
    }
    return result;
}

template<typename S, typename T>
void calculateTransitivityHelper(std::shared_ptr<S> relationshipStore, std::shared_ptr<S> starRelationshipStore,
                                 std::shared_ptr<T> former, std::shared_ptr<T> latter) {
    auto latterChildren = relationshipStore->getRightEntitiesOf(latter);
    if (latterChildren == nullptr) { return; }
    for (auto it = latterChildren->getBeginIterator(); it != latterChildren->getEndIterator(); ++it) {
        auto newLatter = *it;
        auto rightOfFormer = starRelationshipStore->getRightEntitiesOf(former);
        if (rightOfFormer != nullptr && rightOfFormer->get(newLatter) != nullptr) { continue; }
        starRelationshipStore->storeRelationship(former, newLatter);
        calculateTransitivityHelper<S, T>(relationshipStore, starRelationshipStore, former, newLatter);
    }
}

template<typename S, typename T>
void ManagerUtils::calculateTransitivity(std::shared_ptr<S> relationshipStore,
                                         std::shared_ptr<S> starRelationshipStore) {
    for (auto it = relationshipStore->getLeftToRightBeginIterator();
         it != relationshipStore->getLeftToRightEndIterator(); ++it) {
        auto former = it->first;
        auto latterSet = it->second;
        for (auto it2 = latterSet->getBeginIterator(); it2 != latterSet->getEndIterator(); ++it2) {
            auto latter = *it2;
            starRelationshipStore->storeRelationship(former, latter);
            calculateTransitivityHelper<S, T>(relationshipStore, starRelationshipStore, former, latter);
        }
    }
}