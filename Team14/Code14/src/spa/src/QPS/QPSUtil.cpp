#include "QPSUtil.h"
#include "QPS/Evaluators/Strategies/UsesSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ModifiesSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/FollowsSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/FollowsStarSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ParentSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ParentStarSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/CallsSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/CallsStarSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/AssignPatternStrategy.h"

std::unordered_map<std::string, TokenType> QPSUtil::strToTokenTypeMap = {
        {"(", TokenType::Lparenthesis},
        {")", TokenType::Rparenthesis},
        {"+", TokenType::Plus},
        {"-", TokenType::Minus},
        {"*", TokenType::Asterisk},
        {"/", TokenType::Slash},
        {"%", TokenType::Percent},
        {";", TokenType::Semicolon},
        {",", TokenType::Comma},
        {"\"", TokenType::Quote},
        {"_", TokenType::Underscore},
        {".", TokenType::Dot},
        {"=", TokenType::Equal},
};

std::unordered_map<std::string, AttrName> QPSUtil::strToAttrNameMap = {
        {"procName", AttrName::ProcName},
        {"varName", AttrName::VarName},
        {"value", AttrName::Value},
        {"stmt#", AttrName::StmtNo}
};

std::unordered_set<ClauseType> QPSUtil::stmtrefClauseTypes = {
    ClauseType::Follows, ClauseType::FollowsStar,
    ClauseType::Parent, ClauseType::ParentStar
};

std::unordered_set<ClauseType> QPSUtil::stmtrefProcVarClauseTypes = {ClauseType::Uses, ClauseType::Modifies};

std::unordered_set<ClauseType> QPSUtil::procRefClauseTypes = {ClauseType::Calls, ClauseType::CallsStar};

std::unordered_map<QueryEntityType, std::unordered_set<AttrName>> QPSUtil::entityToAttrNamesMap = {
        {QueryEntityType::Call, std::unordered_set{AttrName::ProcName, AttrName::StmtNo}},
        {QueryEntityType::Procedure, std::unordered_set{AttrName::ProcName}},
        {QueryEntityType::Read, std::unordered_set{AttrName::VarName, AttrName::StmtNo}},
        {QueryEntityType::Print, std::unordered_set{AttrName::VarName, AttrName::StmtNo}},
        {QueryEntityType::Variable, std::unordered_set{AttrName::VarName}},
        {QueryEntityType::Stmt, std::unordered_set{AttrName::StmtNo}},
        {QueryEntityType::Call, std::unordered_set{AttrName::StmtNo}},
        {QueryEntityType::While, std::unordered_set{AttrName::StmtNo}},
        {QueryEntityType::If, std::unordered_set{AttrName::StmtNo}},
        {QueryEntityType::Assign, std::unordered_set{AttrName::StmtNo}},
        {QueryEntityType::Constant, std::unordered_set{AttrName::Value}},
};

std::unordered_map<QueryEntityType, RefType> QPSUtil::entityRefMap = {
    {QueryEntityType::Stmt, RefType::StmtRef},
    {QueryEntityType::Assign, RefType::StmtRef},
    {QueryEntityType::Print, RefType::StmtRef},
    {QueryEntityType::If, RefType::StmtRef},
    {QueryEntityType::While, RefType::StmtRef},
    {QueryEntityType::Read, RefType::StmtRef},
    {QueryEntityType::Call, RefType::StmtRef},
    {QueryEntityType::Procedure, RefType::EntRef},
};

std::unordered_set<QueryEntityType> QPSUtil::stmtRefEntities = {
    QueryEntityType::Stmt, QueryEntityType::Assign, QueryEntityType::Print,
    QueryEntityType::If, QueryEntityType::While, QueryEntityType::Read, QueryEntityType::Call
};

std::unordered_map<ClauseType, std::function<std::shared_ptr<Strategy>(std::shared_ptr<PkbReader>)>> QPSUtil::strategyCreatorMap = {
    {ClauseType::Uses, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<UsesSuchThatStrategy>(pkbReader);}},
    {ClauseType::Modifies, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<ModifiesSuchThatStrategy>(pkbReader);}},
    {ClauseType::Follows, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<FollowsSuchThatStrategy>(pkbReader);}},
    {ClauseType::FollowsStar, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<FollowsStarSuchThatStrategy>(pkbReader);}},
    {ClauseType::Parent, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<ParentSuchThatStrategy>(pkbReader);}},
    {ClauseType::ParentStar, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<ParentStarSuchThatStrategy>(pkbReader);}},
    {ClauseType::Calls, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<CallsSuchThatStrategy>(pkbReader);}},
    {ClauseType::CallsStar, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<CallsStarSuchThatStrategy>(pkbReader);}},
    {ClauseType::Assign, [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> { return std::make_shared<AssignPatternStrategy>(pkbReader);}},
};

std::unordered_map<QueryEntityType, StatementType> QPSUtil::entityToStmtMap = {
        {QueryEntityType::Assign, StatementType::Assign},
        {QueryEntityType::Print, StatementType::Print},
        {QueryEntityType::Read, StatementType::Read},
        {QueryEntityType::If, StatementType::If},
        {QueryEntityType::While, StatementType::While},
        {QueryEntityType::Stmt, StatementType::Stmt},
        {QueryEntityType::Call, StatementType::Call}
};

