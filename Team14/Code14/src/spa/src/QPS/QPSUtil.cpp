#include "QPSUtil.h"
#include "QPS/Evaluators/Strategies/AssignPatternStrategy.h"
#include "QPS/Evaluators/Strategies/CallsStarSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/CallsSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/FollowsStarSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/FollowsSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/IfPatternStrategy.h"
#include "QPS/Evaluators/Strategies/ModifiesSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/NextStarSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/NextSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ParentStarSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/ParentSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/UsesSuchThatStrategy.h"
#include "QPS/Evaluators/Strategies/WhilePatternStrategy.h"
#include "QPS/Evaluators/Strategies/WithStrategy.h"

std::unordered_map<StringRep, QueryEntityType> QPSUtil::designEntities = {
        {AppConstants::STRING_PROCEDURE, QueryEntityType::Procedure},
        {AppConstants::STRING_STATEMENT, QueryEntityType::Stmt},
        {AppConstants::STRING_READ, QueryEntityType::Read},
        {AppConstants::STRING_PRINT, QueryEntityType::Print},
        {AppConstants::STRING_ASSIGN, QueryEntityType::Assign},
        {AppConstants::STRING_CALL, QueryEntityType::Call},
        {AppConstants::STRING_WHILE, QueryEntityType::While},
        {AppConstants::STRING_IF, QueryEntityType::If},
        {AppConstants::STRING_VARIABLE, QueryEntityType::Variable},
        {AppConstants::STRING_CONSTANT, QueryEntityType::Constant},
};

std::unordered_map<std::string, TokenType> QPSUtil::strToTokenTypeMap = {
        {AppConstants::STRING_OPEN_ROUND_PARENTHESIS, TokenType::Lparenthesis},
        {AppConstants::STRING_CLOSE_ROUND_PARENTHESIS, TokenType::Rparenthesis},
        {AppConstants::STRING_PLUS, TokenType::Plus},
        {AppConstants::STRING_MINUS, TokenType::Minus},
        {AppConstants::STRING_TIMES, TokenType::Asterisk},
        {AppConstants::STRING_DIVIDE, TokenType::Slash},
        {AppConstants::STRING_MODULO, TokenType::Percent},
        {AppConstants::STRING_SEMICOLON, TokenType::Semicolon},
        {AppConstants::STRING_COMMA, TokenType::Comma},
        {AppConstants::STRING_QUOTE, TokenType::Quote},
        {AppConstants::STRING_UNDERSCORE, TokenType::Underscore},
        {AppConstants::STRING_DOT, TokenType::Dot},
        {AppConstants::STRING_EQUAL, TokenType::Equal},
        {AppConstants::STRING_LTUPLE, TokenType::Ltuple},
        {AppConstants::STRING_RTUPLE, TokenType::Rtuple},
};

std::unordered_map<std::string, AttrName> QPSUtil::strToAttrNameMap = {
        {AppConstants::STRING_PROCNAME, AttrName::ProcName},
        {AppConstants::STRING_VARNAME, AttrName::VarName},
        {AppConstants::STRING_VALUE, AttrName::Value},
        {AppConstants::STRING_STMTNO, AttrName::StmtNo}};

std::unordered_map<StringRep, ClauseType> QPSUtil::repClauseTypeMap = {
        {AppConstants::STRING_USES, ClauseType::Uses},
        {AppConstants::STRING_MODIFIES, ClauseType::Modifies},
        {AppConstants::STRING_FOLLOWS, ClauseType::Follows},
        {AppConstants::STRING_FOLLOWSSTAR, ClauseType::FollowsStar},
        {AppConstants::STRING_PARENT, ClauseType::Parent},
        {AppConstants::STRING_PARENTSTAR, ClauseType::ParentStar},
        {AppConstants::STRING_CALLS, ClauseType::Calls},
        {AppConstants::STRING_CALLSSTAR, ClauseType::CallsStar},
        {AppConstants::STRING_NEXT, ClauseType::Next},
        {AppConstants::STRING_NEXTSTAR, ClauseType::NextStar},
        {AppConstants::STRING_AFFECTS, ClauseType::Affects}};

std::unordered_map<QueryEntityType, ClauseType> QPSUtil::entityToClauseMap = {
        {QueryEntityType::Assign, ClauseType::Assign},
        {QueryEntityType::While, ClauseType::While},
        {QueryEntityType::If, ClauseType::If},
};

std::unordered_map<ClauseType, ClauseArgType> QPSUtil::typeToArgTypeMap = {
        {ClauseType::Uses, StmtrefProcVar},    {ClauseType::Modifies, StmtrefProcVar},
        {ClauseType::Follows, StmtrefStmtref}, {ClauseType::FollowsStar, StmtrefStmtref},
        {ClauseType::Parent, StmtrefStmtref},  {ClauseType::ParentStar, StmtrefStmtref},
        {ClauseType::Next, StmtrefStmtref},    {ClauseType::NextStar, StmtrefStmtref},
        {ClauseType::Affects, StmtrefStmtref}, {ClauseType::Calls, ProcProc},
        {ClauseType::CallsStar, ProcProc},
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
                //                {ClauseType::Affects,
                //                 [](std::shared_ptr<PkbReader> pkbreader) -> std::shared_ptr<Strategy> {
                //                     // TODO: return std::make_shared<AffectsSuchThatStrategy>(pkbReader);
                //                 }},
                {ClauseType::Assign,
                 [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> {
                     return std::make_shared<AssignPatternStrategy>(pkbReader);
                 }},
                {ClauseType::If,
                 [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> {
                     return std::make_shared<IfPatternStrategy>(pkbReader);
                 }},
                {ClauseType::While,
                 [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> {
                     return std::make_shared<WhilePatternStrategy>(pkbReader);
                 }},
                {ClauseType::With,
                 [](std::shared_ptr<PkbReader> pkbReader) -> std::shared_ptr<Strategy> {
                     return std::make_shared<WithStrategy>(pkbReader);
                 }},
};

std::unordered_map<QueryEntityType, std::function<std::vector<Entity>(std::shared_ptr<PkbReader>)>>
        QPSUtil::entityGetterMap = {
                {QueryEntityType::Procedure,
                 [](std::shared_ptr<PkbReader> pkb) -> std::vector<Entity> { return pkb->getAllProcedures(); }},
                {QueryEntityType::Stmt,
                 [](std::shared_ptr<PkbReader> pkb) -> std::vector<Entity> { return pkb->getAllStatements(); }},
                {QueryEntityType::Assign,
                 [](std::shared_ptr<PkbReader> pkb) -> std::vector<Entity> { return pkb->getAllAssign(); }},
                {QueryEntityType::Variable,
                 [](std::shared_ptr<PkbReader> pkb) -> std::vector<Entity> { return pkb->getAllVariables(); }},
                {QueryEntityType::Constant,
                 [](std::shared_ptr<PkbReader> pkb) -> std::vector<Entity> { return pkb->getAllConstants(); }},
                {QueryEntityType::While,
                 [](std::shared_ptr<PkbReader> pkb) -> std::vector<Entity> { return pkb->getAllWhile(); }},
                {QueryEntityType::If,
                 [](std::shared_ptr<PkbReader> pkb) -> std::vector<Entity> { return pkb->getAllIf(); }},
                {QueryEntityType::Read,
                 [](std::shared_ptr<PkbReader> pkb) -> std::vector<Entity> { return pkb->getAllRead(); }},
                {QueryEntityType::Print,
                 [](std::shared_ptr<PkbReader> pkb) -> std::vector<Entity> { return pkb->getAllPrint(); }},
                {QueryEntityType::Call,
                 [](std::shared_ptr<PkbReader> pkb) -> std::vector<Entity> { return pkb->getAllCall(); }}};

std::unordered_map<QueryEntityType, StatementType> QPSUtil::entityToStmtMap = {
        {QueryEntityType::Assign, StatementType::Assign}, {QueryEntityType::Print, StatementType::Print},
        {QueryEntityType::Read, StatementType::Read},     {QueryEntityType::If, StatementType::If},
        {QueryEntityType::While, StatementType::While},   {QueryEntityType::Stmt, StatementType::Stmt},
        {QueryEntityType::Call, StatementType::Call}};


std::unordered_map<AttrName, std::unordered_set<QueryEntityType>> QPSUtil::attrNameToTypeMap = {
        {AttrName::StmtNo, QPSUtil::stmtRefEntities},
        {AttrName::ProcName, std::unordered_set<QueryEntityType>{QueryEntityType::Procedure, QueryEntityType::Call}},
        {AttrName::VarName,
         std::unordered_set<QueryEntityType>{QueryEntityType::Variable, QueryEntityType::Read, QueryEntityType::Print}},
        {AttrName::Value, std::unordered_set<QueryEntityType>{QueryEntityType::Constant}}};

Synonym QPSUtil::getSyn(std::string elem) {
    std::size_t dotPos = elem.find('.');
    if (dotPos != std::string::npos) {// attrRef
        return elem.substr(0, dotPos);
    }
    return elem;
}

std::string QPSUtil::getAttrName(std::string elem) {
    std::size_t dotPos = elem.find('.');
    if (dotPos != std::string::npos) {// attrRef
        return elem.substr(dotPos + 1);
    }
    return "";
}

std::unordered_map<AttrName, std::function<std::string(Entity)>> QPSUtil::getValueFunc = {
        {AttrName::ProcName,
         [](const Entity &e) -> std::string {
             if (e.getEntityType() == EntityType::Procedure) {
                 return e.getEntityValue();
             } else {// call.procName
                 return e.getAttrValue();
             }
         }},
        {AttrName::VarName,
         [](const Entity &e) -> std::string {
             if (e.getEntityType() == EntityType::Variable) {
                 return e.getEntityValue();
             } else {// read.varName & printVarName
                 return e.getAttrValue();
             }
         }},
        {AttrName::Value, [](const Entity &e) -> std::string { return e.getEntityValue(); }},
        {AttrName::StmtNo, [](const Entity &e) -> std::string { return e.getEntityValue(); }}};
