#include "QPSUtil.h"
#include "QPS/Evaluators/Strategies/UsesSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ModifiesSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/FollowsSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/FollowsStarSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ParentSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ParentStarSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/AssignPatternStrategy.h"

std::unordered_set<ClauseType> QPSUtil::stmtrefClauseTypes = {
    ClauseType::Follows, ClauseType::FollowsStar,
    ClauseType::Parent, ClauseType::ParentStar
};

std::unordered_set<ClauseType> QPSUtil::stmtrefProcVarClauseTypes = {ClauseType::Uses, ClauseType::Modifies};

std::unordered_set<ClauseType> QPSUtil::procRefClauseTypes = {ClauseType::Calls, ClauseType::CallsStar};

std::unordered_map<QueryEntityType, RefType> QPSUtil::entityRefMap = {
    {QueryEntityType::Stmt, RefType::StmtRef},
    {QueryEntityType::Assign, RefType::StmtRef},
    {QueryEntityType::Print, RefType::StmtRef},
    {QueryEntityType::If, RefType::StmtRef},
    {QueryEntityType::While, RefType::StmtRef},
    {QueryEntityType::Read, RefType::StmtRef},
    {QueryEntityType::Procedure, RefType::EntRef}
};

std::unordered_set<QueryEntityType> QPSUtil::stmtRefEntities = {
    QueryEntityType::Stmt, QueryEntityType::Assign, QueryEntityType::Print,
    QueryEntityType::If, QueryEntityType::While, QueryEntityType::Read
};

std::unordered_map<ClauseType, std::function<std::shared_ptr<Strategy>(std::shared_ptr<PkbReader>)>> QPSUtil::strategyCreatorMap = {
    {ClauseType::Uses, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<UsesSuchThatStrategy>(pkbReader);}},
    {ClauseType::Modifies, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<ModifiesSuchThatStrategy>(pkbReader);}},
    {ClauseType::Follows, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<FollowsSuchThatStrategy>(pkbReader);}},
    {ClauseType::FollowsStar, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<FollowsStarSuchThatStrategy>(pkbReader);}},
    {ClauseType::Parent, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<ParentSuchThatStrategy>(pkbReader);}},
    {ClauseType::ParentStar, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<ParentStarSuchThatStrategy>(pkbReader);}},
    {ClauseType::Assign, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<AssignPatternStrategy>(pkbReader);}},
};

std::unordered_map<QueryEntityType, StatementType> QPSUtil::entityToStmtMap = {
        {QueryEntityType::Assign, StatementType::Assign},
        {QueryEntityType::Print, StatementType::Print},
        {QueryEntityType::Read, StatementType::Read},
        {QueryEntityType::If, StatementType::If},
        {QueryEntityType::While, StatementType::While},
        {QueryEntityType::Stmt, StatementType::Stmt}
};

