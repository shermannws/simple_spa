#include "QPSUtil.h"
#include "QPS/Evaluators/Strategies/UsesSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ModifiesSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/FollowsSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/FollowsStarSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ParentSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ParentStarSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/AssignPatternStrategy.h"

std::unordered_map<ClauseType, std::function<std::shared_ptr<Strategy>()>> QPSUtil::strategyCreatorMap = {
    {ClauseType::Uses, []() -> std::shared_ptr<Strategy> { return std::make_shared<UsesSuchThatStrategy>();}},
    {ClauseType::Modifies, []() -> std::shared_ptr<Strategy> { return std::make_shared<ModifiesSuchThatStrategy>();}},
    {ClauseType::Follows, []() -> std::shared_ptr<Strategy> { return std::make_shared<FollowsSuchThatStrategy>();}},
    {ClauseType::FollowsStar, []() -> std::shared_ptr<Strategy> { return std::make_shared<FollowsStarSuchThatStrategy>();}},
    {ClauseType::Parent, []() -> std::shared_ptr<Strategy> { return std::make_shared<ParentSuchThatStrategy>();}},
    {ClauseType::ParentStar, []() -> std::shared_ptr<Strategy> { return std::make_shared<ParentStarSuchThatStrategy>();}},
    {ClauseType::Assign, []() -> std::shared_ptr<Strategy> { return std::make_shared<AssignPatternStrategy>();}},
};

bool QPSUtil::isOfStmtType(QueryEntityType entityType) {
    return entityType == QueryEntityType::Stmt || entityType == QueryEntityType::Assign
           || entityType == QueryEntityType::Print || entityType == QueryEntityType::If
           || entityType == QueryEntityType::While || entityType == QueryEntityType::Read;
}

bool QPSUtil::isRootOfEntref(RootType rootType) {
    return rootType == RootType::Synonym || rootType == RootType::Wildcard
           || rootType == RootType::Ident;
}

bool QPSUtil::isRootOfStmtref(RootType rootType) {
    return rootType == RootType::Synonym || rootType == RootType::Wildcard
           || rootType == RootType::Integer;
}


