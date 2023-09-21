#include "PKB/Managers/ManagerUtils.cpp"
#include "PKB/Relationships/FollowsRelationship.h"
#include "PKB/RelationshipStores/FollowsRelationshipStore.h"
#include "PKB/Relationships/UsesRelationship.h"
#include "PKB/RelationshipStores/UsesRelationshipStore.h"
#include "PKB/Relationships/ModifiesRelationship.h"
#include "PKB/RelationshipStores/ModifiesRelationshipStore.h"

template std::vector<Entity> ManagerUtils::getEntitiesFromStore<FollowsRelationshipStore, FollowsRelationship>(std::shared_ptr<FollowsRelationshipStore> store, std::function<bool(FollowsRelationship&)> matcher, std::function<Entity(FollowsRelationship&)> getter);

template std::vector<std::vector<Entity>> ManagerUtils::getEntityPairsFromStore<FollowsRelationshipStore, FollowsRelationship>(std::shared_ptr<FollowsRelationshipStore> store, std::function<bool(FollowsRelationship&)> matcher, std::function<std::vector<Entity>(FollowsRelationship&)> getter);

template std::vector<Entity> ManagerUtils::getEntitiesFromStore<UsesRelationshipStore, UsesRelationship>(std::shared_ptr<UsesRelationshipStore> store, std::function<bool(UsesRelationship&)> matcher, std::function<Entity(UsesRelationship&)> getter);

template std::vector<std::vector<Entity>> ManagerUtils::getEntityPairsFromStore<UsesRelationshipStore, UsesRelationship>(std::shared_ptr<UsesRelationshipStore> store, std::function<bool(UsesRelationship&)> matcher, std::function<std::vector<Entity>(UsesRelationship&)> getter);

template std::vector<Entity> ManagerUtils::getEntitiesFromStore<ModifiesRelationshipStore, ModifiesRelationship>(std::shared_ptr<ModifiesRelationshipStore> store, std::function<bool(ModifiesRelationship&)> matcher, std::function<Entity(ModifiesRelationship&)> getter);

template std::vector<std::vector<Entity>> ManagerUtils::getEntityPairsFromStore<ModifiesRelationshipStore, ModifiesRelationship>(std::shared_ptr<ModifiesRelationshipStore> store, std::function<bool(ModifiesRelationship&)> matcher, std::function<std::vector<Entity>(ModifiesRelationship&)> getter);

