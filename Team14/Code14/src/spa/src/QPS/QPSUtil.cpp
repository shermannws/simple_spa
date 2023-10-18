#include "QPSUtil.h"
#include "QPS/Evaluators/Strategies/AssignPatternStrategy.h"
#include "QPS/Evaluators/Strategies/CallsStarSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/CallsSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/FollowsStarSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/FollowsSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ModifiesSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/NextStarSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/NextSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ParentStarSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ParentSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/UsesSuchThatStrategy.h"

std::unordered_map<StringRep, ClauseType> QPSUtil::repClauseTypeMap = {
        {"Uses", ClauseType::Uses},       {"Modifies", ClauseType::Modifies},
        {"Follows", ClauseType::Follows}, {"Follows*", ClauseType::FollowsStar},
        {"Parent", ClauseType::Parent},   {"Parent*", ClauseType::ParentStar},
        {"Calls", ClauseType::Calls},     {"Calls*", ClauseType::CallsStar},
        {"Next", ClauseType::Next},       {"Next*", ClauseType::NextStar},
};

std::unordered_map<ClauseType, ClauseArgType> QPSUtil::typeToArgTypeMap = {
        {ClauseType::Uses, StmtrefProcVar},    {ClauseType::Modifies, StmtrefProcVar},
        {ClauseType::Follows, StmtrefStmtref}, {ClauseType::FollowsStar, StmtrefStmtref},
        {ClauseType::Parent, StmtrefStmtref},  {ClauseType::ParentStar, StmtrefStmtref},
        {ClauseType::Next, StmtrefStmtref},    {ClauseType::NextStar, StmtrefStmtref},
        {ClauseType::Calls, ProcProc},         {ClauseType::CallsStar, ProcProc},
};

std::unordered_map<QueryEntityType, RefType> QPSUtil::entityRefMap = {
        {QueryEntityType::Stmt, RefType::StmtRef},  {QueryEntityType::Assign, RefType::StmtRef},
        {QueryEntityType::Print, RefType::StmtRef}, {QueryEntityType::If, RefType::StmtRef},
        {QueryEntityType::While, RefType::StmtRef}, {QueryEntityType::Read, RefType::StmtRef},
        {QueryEntityType::Call, RefType::StmtRef},  {QueryEntityType::Procedure, RefType::EntRef},
};

std::unordered_set<QueryEntityType> QPSUtil::stmtRefEntities = {
        QueryEntityType::Stmt,  QueryEntityType::Assign, QueryEntityType::Print, QueryEntityType::If,
        QueryEntityType::While, QueryEntityType::Read,   QueryEntityType::Call};

std::unordered_map<ClauseType, std::function<std::shared_ptr<Strategy>(std::shared_ptr<PkbReader>)>>
        QPSUtil::strategyCreatorMap = {
                {ClauseType::Uses,
                 [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> {
                     return std::make_shared<UsesSuchThatStrategy>(pkbReader);
                 }},
                {ClauseType::Modifies,
                 [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> {
                     return std::make_shared<ModifiesSuchThatStrategy>(pkbReader);
                 }},
                {ClauseType::Follows,
                 [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> {
                     return std::make_shared<FollowsSuchThatStrategy>(pkbReader);
                 }},
                {ClauseType::FollowsStar,
                 [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> {
                     return std::make_shared<FollowsStarSuchThatStrategy>(pkbReader);
                 }},
                {ClauseType::Parent,
                 [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> {
                     return std::make_shared<ParentSuchThatStrategy>(pkbReader);
                 }},
                {ClauseType::ParentStar,
                 [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> {
                     return std::make_shared<ParentStarSuchThatStrategy>(pkbReader);
                 }},
                {ClauseType::Next,
                 [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> {
                     return std::make_shared<NextSuchThatStrategy>(pkbReader);
                 }},
                {ClauseType::NextStar,
                 [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> {
                     return std::make_shared<NextStarSuchThatStrategy>(pkbReader);
                 }},
                {ClauseType::Calls,
                 [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> {
                     return std::make_shared<CallsSuchThatStrategy>(pkbReader);
                 }},
                {ClauseType::CallsStar,
                 [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> {
                     return std::make_shared<CallsStarSuchThatStrategy>(pkbReader);
                 }},
                {ClauseType::Assign,
                 [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> {
                     return std::make_shared<AssignPatternStrategy>(pkbReader);
                 }},
};

std::unordered_map<QueryEntityType, StatementType> QPSUtil::entityToStmtMap = {
        {QueryEntityType::Assign, StatementType::Assign}, {QueryEntityType::Print, StatementType::Print},
        {QueryEntityType::Read, StatementType::Read},     {QueryEntityType::If, StatementType::If},
        {QueryEntityType::While, StatementType::While},   {QueryEntityType::Stmt, StatementType::Stmt},
        {QueryEntityType::Call, StatementType::Call}};

std::unordered_map<AttrName, std::unordered_set<QueryEntityType>> QPSUtil::attrNameToTypeMap = {
        {"stmt#", QPSUtil::stmtRefEntities},
        {"procName", std::unordered_set<QueryEntityType>{QueryEntityType::Procedure, QueryEntityType::Call}},
        {"varName",
         std::unordered_set<QueryEntityType>{QueryEntityType::Variable, QueryEntityType::Read, QueryEntityType::Print}},
        {"value", std::unordered_set<QueryEntityType>{QueryEntityType::Constant}}};

std::unordered_map<AttrName, std::unordered_set<StatementType>> QPSUtil::getAttrValue = {
        {"procName", std::unordered_set<StatementType>{StatementType::Call}},
        {"varName", std::unordered_set<StatementType>{StatementType::Read, StatementType::Print}}};

Synonym QPSUtil::getSyn(std::string elem) {
    std::size_t dotPos = elem.find('.');
    if (dotPos != std::string::npos) {// attrRef
        return elem.substr(0, dotPos);
    }
    return elem;
}

AttrName QPSUtil::getAttrName(std::string elem) {
    std::size_t dotPos = elem.find('.');
    if (dotPos != std::string::npos) {// attrRef
        return elem.substr(dotPos + 1);
    }
    return elem;
}

// bool QPSUtil::isAttrRef(std::string elem, Entity& entity) {
//     auto attrName = getAttrName(elem);
//     auto type = entity.getEntityType();
//     if (type == EntityType::Statement && getAttrValue[attrName].count(entity.getStatementType()) > 0) {
//         return true;
//     }
//     return false;
// }