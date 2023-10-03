#include "QPSUtil.h"
#include "QPS/Evaluators/Strategies/UsesSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ModifiesSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/FollowsSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/FollowsStarSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ParentSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ParentStarSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/AssignPatternStrategy.h"

std::unordered_map<ClauseType, std::function<std::shared_ptr<Strategy>(std::shared_ptr<PkbReader>)>> QPSUtil::strategyCreatorMap = {
    {ClauseType::Uses, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<UsesSuchThatStrategy>(pkbReader);}},
    {ClauseType::Modifies, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<ModifiesSuchThatStrategy>(pkbReader);}},
    {ClauseType::Follows, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<FollowsSuchThatStrategy>(pkbReader);}},
    {ClauseType::FollowsStar, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<FollowsStarSuchThatStrategy>(pkbReader);}},
    {ClauseType::Parent, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<ParentSuchThatStrategy>(pkbReader);}},
    {ClauseType::ParentStar, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<ParentStarSuchThatStrategy>(pkbReader);}},
    {ClauseType::Assign, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<AssignPatternStrategy>(pkbReader);}},
};



