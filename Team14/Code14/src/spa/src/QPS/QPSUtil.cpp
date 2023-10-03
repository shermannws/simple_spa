#include "QPSUtil.h"
#include "QPS/Evaluators/Strategies/UsesSSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/UsesPSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ModifiesSSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ModifiesPSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/FollowsSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/FollowsStarSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ParentSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ParentStarSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/AssignPatternStrategy.h"

std::unordered_map<ClauseType, std::function<std::shared_ptr<Strategy>(std::shared_ptr<PkbReader>, std::shared_ptr<Clause>)>> QPSUtil::strategyCreatorMap = {
    {ClauseType::Uses, [](std::shared_ptr<PkbReader> pkbReader, std::shared_ptr<Clause> clause) -> std::shared_ptr<Strategy> {
        if (clause->getFirstParam().isStmtRef()) {
            return std::make_shared<UsesSSuchThatStrategy>(pkbReader);
        } else {

            return std::make_shared<UsesPSuchThatStrategy>(pkbReader);
        }
    }},
    {ClauseType::Modifies, [](std::shared_ptr<PkbReader> pkbReader, std::shared_ptr<Clause> clause) -> std::shared_ptr<Strategy> {
        if (clause->getFirstParam().isStmtRef()) {
            return std::make_shared<ModifiesSSuchThatStrategy>(pkbReader);
        } else {

            return std::make_shared<ModifiesPSuchThatStrategy>(pkbReader);
        }
    }},
    {ClauseType::Follows, [](std::shared_ptr<PkbReader> pkbReader, std::shared_ptr<Clause> clause) -> std::shared_ptr<Strategy> { return std::make_shared<FollowsSuchThatStrategy>(pkbReader);}},
    {ClauseType::FollowsStar, [](std::shared_ptr<PkbReader> pkbReader, std::shared_ptr<Clause> clause) -> std::shared_ptr<Strategy> { return std::make_shared<FollowsStarSuchThatStrategy>(pkbReader);}},
    {ClauseType::Parent, [](std::shared_ptr<PkbReader> pkbReader, std::shared_ptr<Clause> clause) -> std::shared_ptr<Strategy> { return std::make_shared<ParentSuchThatStrategy>(pkbReader);}},
    {ClauseType::ParentStar, [](std::shared_ptr<PkbReader> pkbReader, std::shared_ptr<Clause> clause) -> std::shared_ptr<Strategy> { return std::make_shared<ParentStarSuchThatStrategy>(pkbReader);}},
    {ClauseType::Assign, [](std::shared_ptr<PkbReader> pkbReader, std::shared_ptr<Clause> clause) -> std::shared_ptr<Strategy> { return std::make_shared<AssignPatternStrategy>(pkbReader);}},
};



