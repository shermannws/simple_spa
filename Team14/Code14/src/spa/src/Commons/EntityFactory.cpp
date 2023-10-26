#include <functional>
#include <memory>
#include <unordered_map>
#include <utility>

#include "EntityFactory.h"
#include "SP/AST/Nodes/CallNode.h"
#include "SP/AST/Nodes/PrintNode.h"
#include "SP/AST/Nodes/ReadNode.h"
#include "StatementTypeFactory.h"

std::unordered_map<StatementNumber, std::shared_ptr<Statement>> EntityFactory::statementCache;

std::unordered_map<VariableName, std::shared_ptr<Variable>> EntityFactory::variableCache;

std::unordered_map<ProcedureName, std::shared_ptr<Procedure>> EntityFactory::procedureCache;

std::unordered_map<StatementType, std::function<std::shared_ptr<Statement>(std::shared_ptr<StatementNode>)>>
        EntityFactory::nodeFactoryMethodMap = {{StatementType::Assign, createAssignStatementFromNode},
                                               {StatementType::Call, createCallStatementFromNode},
                                                  {StatementType::Print, createPrintStatementFromNode},
                                                  {StatementType::Read, createReadStatementFromNode},
                                                  {StatementType::If, createIfStatementFromNode},
                                                  {StatementType::While, createWhileStatementFromNode}};

std::unordered_map<StatementType, std::function<std::shared_ptr<Statement>(StatementNumber, const AttrValue &)>>
        EntityFactory::factoryMethodMap = {
                {StatementType::Assign, createAssignStatement}, {StatementType::Call, createCallStatement},
                {StatementType::Print, createPrintStatement},   {StatementType::Read, createReadStatement},
                {StatementType::If, createIfStatement},         {StatementType::While, createWhileStatement}};

std::shared_ptr<AssignStatement>
EntityFactory::createAssignStatementFromNode(const std::shared_ptr<StatementNode> &node) {
    return std::make_shared<AssignStatement>(node->getStatementNumber());
}

std::shared_ptr<CallStatement> EntityFactory::createCallStatementFromNode(const std::shared_ptr<StatementNode> &node) {
    StatementNumber statementNumber = node->getStatementNumber();
    ProcedureName procName = std::static_pointer_cast<CallNode>(node)->getProcedureName();
    return std::make_shared<CallStatement>(statementNumber, procName);
}

std::shared_ptr<PrintStatement>
EntityFactory::createPrintStatementFromNode(const std::shared_ptr<StatementNode> &node) {
    StatementNumber statementNumber = node->getStatementNumber();
    std::shared_ptr<PrintNode> printNode = std::static_pointer_cast<PrintNode>(node);
    VariableName varName = printNode->getVar()->getVarName();
    return std::make_shared<PrintStatement>(statementNumber, varName);
}

std::shared_ptr<ReadStatement> EntityFactory::createReadStatementFromNode(const std::shared_ptr<StatementNode> &node) {
    StatementNumber statementNumber = node->getStatementNumber();
    std::shared_ptr<ReadNode> readNode = std::static_pointer_cast<ReadNode>(node);
    VariableName varName = readNode->getVar()->getVarName();
    return std::make_shared<ReadStatement>(statementNumber, varName);
}

std::shared_ptr<IfStatement> EntityFactory::createIfStatementFromNode(const std::shared_ptr<StatementNode> &node) {
    return std::make_shared<IfStatement>(node->getStatementNumber());
}

std::shared_ptr<WhileStatement>
EntityFactory::createWhileStatementFromNode(const std::shared_ptr<StatementNode> &node) {
    return std::make_shared<WhileStatement>(node->getStatementNumber());
}

std::shared_ptr<AssignStatement> EntityFactory::createAssignStatement(StatementNumber statementNumber,
                                                                      const AttrValue &attrValue) {
    return std::make_shared<AssignStatement>(statementNumber);
}

std::shared_ptr<PrintStatement> EntityFactory::createPrintStatement(StatementNumber statementNumber,
                                                                    const AttrValue &varName) {
    return std::make_shared<PrintStatement>(statementNumber, varName);
}

std::shared_ptr<ReadStatement> EntityFactory::createReadStatement(StatementNumber statementNumber,
                                                                  const AttrValue &varName) {
    return std::make_shared<ReadStatement>(statementNumber, varName);
}

std::shared_ptr<IfStatement> EntityFactory::createIfStatement(StatementNumber statementNumber,
                                                              const AttrValue &attrValue) {
    return std::make_shared<IfStatement>(statementNumber);
}

std::shared_ptr<WhileStatement> EntityFactory::createWhileStatement(StatementNumber statementNumber,
                                                                    const AttrValue &attrValue) {
    return std::make_shared<WhileStatement>(statementNumber);
}

std::shared_ptr<CallStatement> EntityFactory::createCallStatement(StatementNumber statementNumber,
                                                                  const AttrValue &procName) {
    return std::make_shared<CallStatement>(statementNumber, procName);
}

void EntityFactory::clearCaches() {
    statementCache.clear();
    variableCache.clear();
    procedureCache.clear();
}

std::shared_ptr<Statement> EntityFactory::createStatementFromStatementNode(const std::shared_ptr<StatementNode> &node) {
    StatementNodeType statementNodeType = node->getStatementType();
    StatementType statementType = StatementTypeFactory::getStatementTypeFrom(statementNodeType);
    StatementNumber statementNumber = node->getStatementNumber();
    if (statementCache.find(statementNumber) != statementCache.end()) {
        auto cachedStatement = statementCache[statementNumber];
        assert(cachedStatement->getStatementType() == statementType);
        return cachedStatement;
    }

    return statementCache[statementNumber] = nodeFactoryMethodMap.at(statementType)(node);
}

std::shared_ptr<Statement> EntityFactory::createStatement(StatementNumber statementNumber, StatementType statementType,
                                                          AttrValue attrValue) {
    if (statementCache.find(statementNumber) != statementCache.end()) {
        auto cachedStatement = statementCache[statementNumber];
        assert(cachedStatement->getStatementType() == statementType);
        assert(cachedStatement->getAttrValue() == attrValue);
        return cachedStatement;
    }

    return statementCache[statementNumber] = factoryMethodMap.at(statementType)(statementNumber, attrValue);
}

std::shared_ptr<Variable> EntityFactory::createVariable(VariableName varName) {
    if (variableCache.find(varName) != variableCache.end()) { return variableCache[varName]; }

    return variableCache[varName] = std::make_shared<Variable>(varName);
}

std::shared_ptr<Procedure> EntityFactory::createProcedure(ProcedureName procName) {
    if (procedureCache.find(procName) != procedureCache.end()) { return procedureCache[procName]; }

    return procedureCache[procName] = std::make_shared<Procedure>(procName);
}