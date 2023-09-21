#include "PKB/Managers/ManagerUtils.cpp"
#include "PKB/Relationships/FollowsRelationship.h"
#include "PKB/RelationshipStores/FollowsRelationshipStore.h"
#include "PKB/Relationships//UsesRelationship.h"
#include "PKB/RelationshipStores/UsesRelationshipStore.h"

template std::vector<Entity> ManagerUtils::getEntitiesFromStore<FollowsRelationshipStore, FollowsRelationship>(std::shared_ptr<FollowsRelationshipStore> store, std::function<bool(FollowsRelationship&)> matcher, std::function<Entity(FollowsRelationship&)> getter);

template std::vector<std::vector<Entity>> ManagerUtils::getEntityPairsFromStore<FollowsRelationshipStore, FollowsRelationship>(std::shared_ptr<FollowsRelationshipStore> store, std::function<bool(FollowsRelationship&)> matcher, std::function<std::vector<Entity>(FollowsRelationship&)> getter);

template std::vector<Entity> ManagerUtils::getEntitiesFromStore<UsesRelationshipStore, UsesRelationship>(std::shared_ptr<UsesRelationshipStore> store, std::function<bool(UsesRelationship&)> matcher, std::function<Entity(UsesRelationship&)> getter);

template std::vector<std::vector<Entity>> ManagerUtils::getEntityPairsFromStore<UsesRelationshipStore, UsesRelationship>(std::shared_ptr<UsesRelationshipStore> store, std::function<bool(UsesRelationship&)> matcher, std::function<std::vector<Entity>(UsesRelationship&)> getter);
