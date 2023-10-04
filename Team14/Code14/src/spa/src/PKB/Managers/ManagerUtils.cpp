#include "ManagerUtils.h"

template <typename E, typename S, typename R>
std::vector<E> ManagerUtils::getFromStore(std::shared_ptr<S> store, std::function<bool(R&)> matcher, std::function<E(R&)> getter) {
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
    return getFromStore<Entity, S, R>(store, matcher, getter);
}

template <typename R>
std::vector<Entity> ManagerUtils::getEntitiesFromRelationshipStore(std::shared_ptr<RelationshipStore<R>> store, std::function<bool(R&)> matcher, std::function<Entity(R&)> getter) {
    return getFromStore<Entity, RelationshipStore<R>, R>(store, matcher, getter);
}

template <typename E>
std::vector<Entity> ManagerUtils::getEntitiesFromEntityStore(std::shared_ptr<EntityStore<E>> store, std::function<bool(E&)> matcher, std::function<Entity(E&)> getter) {
    return getFromStore<Entity, EntityStore<E>, E>(store, matcher, getter);
}

template <typename S, typename R>
std::vector<std::vector<Entity>> ManagerUtils::getEntityPairsFromStore(std::shared_ptr<S> store, std::function<bool(R&)> matcher, std::function<std::vector<Entity>(R&)> getter) {
    return getFromStore<std::vector<Entity>, S, R>(store, matcher, getter);
}

template <typename R>
std::vector<std::vector<Entity>> ManagerUtils::getEntityPairsFromRelationshipStore(std::shared_ptr<RelationshipStore<R>> store, std::function<bool(R&)> matcher, std::function<std::vector<Entity>(R&)> getter) {
    return getFromStore<std::vector<Entity>, RelationshipStore<R>, R>(store, matcher, getter);
}

void ManagerUtils::unique(std::vector<Entity>& v) {
    std::unordered_set<Entity> s(v.begin(), v.end());
    v.assign(s.begin(), s.end());
}