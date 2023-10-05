#include "ManagerUtils.h"

template <typename E, typename S, typename R>
std::vector<E> ManagerUtils::getFromSetStore(std::shared_ptr<S> store, std::function<bool(R&)> matcher, std::function<E(R&)> getter) {
    auto result = std::vector<E>();
    for (auto it = store->getBeginIterator(); it != store->getEndIterator(); it++) {
        if (matcher(**it)) {
            result.push_back(getter(**it));
        }
    }
    return result;
}

template <typename S, typename R>
std::vector<Entity> ManagerUtils::getEntitiesFromStore(std::shared_ptr<S> store, std::function<bool(R&)> matcher, std::function<Entity(R&)> getter) {
    return getFromSetStore<Entity, S, R>(store, matcher, getter);
}

template <typename E>
std::vector<Entity> ManagerUtils::getEntitiesFromEntityStore(std::shared_ptr<EntityStore<E>> store, std::function<bool(E&)> matcher, std::function<Entity(E&)> getter) {
    return getFromSetStore<Entity, EntityStore<E>, E>(store, matcher, getter);
}

template <typename S, typename R>
std::vector<std::vector<Entity>> ManagerUtils::getEntityPairsFromStore(std::shared_ptr<S> store, std::function<bool(R&)> matcher, std::function<std::vector<Entity>(R&)> getter) {
    return getFromSetStore<std::vector<Entity>, S, R>(store, matcher, getter);
}

template <typename E, typename S, typename K, typename V, typename R>
std::vector<R> ManagerUtils::getFromMapStore(S& store, std::function<std::shared_ptr<E>(S&, K&)> getter, K& key, std::function<bool(V&)> matcher) {
    auto result = std::vector<R>();
    auto resultSet = getter(store, key);
    if (resultSet == nullptr) {
        return result;
    }
    for (auto it = resultSet->getBeginIterator(); it != resultSet->getEndIterator(); it++) {
        if (matcher(**it)) {
            result.push_back(**it);
        }
    }
    return result;
}

template <typename L, typename R>
std::vector<Entity> ManagerUtils::getRightEntitiesFromLeftKey(RelationshipStore<L, R>& store, L& key, std::function<bool(R&)> matcher) {
    auto getter = [](RelationshipStore<L, R>& store, L& key) {
        return store.getRightEntitiesOf(std::make_shared<L>(key));
    };
    return getFromMapStore<EntityStore<R>, RelationshipStore<L, R>, L, R, Entity>(store, getter, key, matcher);
}

template <typename L, typename R>
std::vector<Entity> ManagerUtils::getLeftEntitiesFromRightKey(RelationshipStore<L, R>& store, R& key, std::function<bool(L&)> matcher) {
    auto getter = [](RelationshipStore<L, R>& store, R& key) {
        return store.getLeftEntitiesOf(std::make_shared<R>(key));
    };
    return getFromMapStore<EntityStore<L>, RelationshipStore<L, R>, R, L, Entity>(store, getter, key, matcher);
}

//template <typename K, typename V>
//std::vector<std::vector<Entity>> ManagerUtils::getEntityPairsFromKey(RelationshipStore<K, V>& store, std::shared_ptr<K> key, std::function<bool(V&)> matcher) {
//    auto getter = [](RelationshipStore<K, V>& store, std::shared_ptr<K> key) {
//        return store->getLeftRightEntityPairsFromLeftKey(key);
//    };
//    return getFromStore<std::vector<Entity>, RelationshipStore<K, V>, K, V>(store, getter, key, matcher);
//}

template <typename E>
void ManagerUtils::unique(std::vector<E>& v) {
    std::unordered_set<E> s(v.begin(), v.end());
    v.assign(s.begin(), s.end());
}