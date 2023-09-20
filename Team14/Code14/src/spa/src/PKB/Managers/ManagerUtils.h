#pragma once

#include <string>
#include <memory>
#include <vector>

#include "Commons/Entities/Entity.h"

class ManagerUtils {
public:
    template<typename E, typename S, typename R>
    static std::vector<E>
    getFromStore(std::shared_ptr<S> store, std::function<bool(R&)> matcher, std::function<E(R&)> getter);

    template<typename S, typename R>
    static std::vector<Entity>
    getEntitiesFromStore(std::shared_ptr<S> store, std::function<bool(R&)> matcher, std::function<Entity(R&)> getter);

    template<typename S, typename R>
    static std::vector<std::vector<Entity>>
    getEntityPairsFromStore(std::shared_ptr<S> store, std::function<bool(R&)> matcher, std::function<std::vector<Entity>(R&)> getter);
};
