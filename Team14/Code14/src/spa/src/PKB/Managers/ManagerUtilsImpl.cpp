#include "PKB/Managers/ManagerUtils.cpp"
#include "PKB/Relationships/FollowsRelationship.h"
#include "PKB/RelationshipStores/FollowsRelationshipStore.h"

template std::vector<Entity> ManagerUtils::getFromStore<FollowsRelationshipStore, FollowsRelationship>(std::shared_ptr<FollowsRelationshipStore> store, std::function<bool(FollowsRelationship&)> matcher, std::function<Entity(FollowsRelationship&)> getter);