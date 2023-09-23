#pragma once

#include <string>
#include <memory>
#include <vector>

#include "Commons/Entities/Entity.h"
#include "PKB/RelationshipStores/RelationshipStore.h"
#include "PKB/EntityStores/EntityStore.h"

class ManagerUtils {
public:
    template<typename E, typename S, typename R>
    static std::vector<E>
    getFromStore(std::shared_ptr<S> store, std::function<bool(R&)> matcher, std::function<E(R&)> getter);

    template<typename S, typename R>
    static std::vector<Entity>
    getEntitiesFromStore(std::shared_ptr<S> store, std::function<bool(R&)> matcher, std::function<Entity(R&)> getter);

    template<typename R>
    static std::vector<Entity>
    getEntitiesFromRelationshipStore(std::shared_ptr<RelationshipStore<R>> store, std::function<bool(R&)> matcher, std::function<Entity(R&)> getter);

    template<typename E>
    static std::vector<Entity>
    getEntitiesFromEntityStore(std::shared_ptr<EntityStore<E>> store, std::function<bool(E&)> matcher, std::function<Entity(E&)> getter);

    template<typename S, typename R>
    static std::vector<std::vector<Entity>>
    getEntityPairsFromStore(std::shared_ptr<S> store, std::function<bool(R&)> matcher, std::function<std::vector<Entity>(R&)> getter);

    template<typename R>
    static std::vector<std::vector<Entity>>
    getEntityPairsFromRelationshipStore(std::shared_ptr<RelationshipStore<R>> store, std::function<bool(R&)> matcher, std::function<std::vector<Entity>(R&)> getter);
};
