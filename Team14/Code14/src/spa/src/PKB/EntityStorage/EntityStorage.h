#pragma once

#include <unordered_set>
#include <memory>

#include "../../Commons/Entities/Entity.h"

class EntityStorage {
private:
    std::unordered_set<
        std::shared_ptr<Entity>,
        std::hash<std::shared_ptr<Entity>>,
        std::equal_to<std::shared_ptr<Entity>>
    > entityStore;

public:
    EntityStorage();

    void storeEntity(std::shared_ptr<Entity> entity);

    Entity* getEntity(std::shared_ptr<Entity> entity) const;
};

