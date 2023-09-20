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

template <typename S, typename R>
std::vector<std::vector<Entity>> ManagerUtils::getEntityPairsFromStore(std::shared_ptr<S> store, std::function<bool(R&)> matcher, std::function<std::vector<Entity>(R&)> getter) {
    return getFromStore<std::vector<Entity>, S, R>(store, matcher, getter);
}