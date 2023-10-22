#include <functional>
#include <memory>
#include <unordered_map>
#include <utility>

#include "SP/AST/Nodes/CallNode.h"
#include "SP/AST/Nodes/PrintNode.h"
#include "SP/AST/Nodes/ReadNode.h"
#include "StatementFactory.h"
#include "StatementTypeFactory.h"

std::unordered_map<StatementType, std::function<std::shared_ptr<Statement>(std::shared_ptr<StatementNode>)>>
        StatementFactory::nodeFactoryMethodMap = {{StatementType::Assign, createAssignStatementFromNode},
                                                  {StatementType::Call, createCallStatementFromNode},
                                                  {StatementType::Print, createPrintStatementFromNode},
                                                  {StatementType::Read, createReadStatementFromNode},
                                                  {StatementType::If, createIfStatementFromNode},
                                                  {StatementType::While, createWhileStatementFromNode}};

std::unordered_map<StatementType, std::function<std::shared_ptr<Statement>(StatementNumber, const AttrValue &)>>
        StatementFactory::factoryMethodMap = {
                {StatementType::Assign, createAssignStatement}, {StatementType::Call, createCallStatement},
                {StatementType::Print, createPrintStatement},   {StatementType::Read, createReadStatement},
                {StatementType::If, createIfStatement},         {StatementType::While, createWhileStatement}};

std::shared_ptr<Statement>
StatementFactory::createStatementFromStatementNode(const std::shared_ptr<StatementNode> &node) {
    StatementNodeType statementNodeType = node->getStatementType();
    StatementType statementType = StatementTypeFactory::getStatementTypeFrom(statementNodeType);

    return nodeFactoryMethodMap.at(statementType)(node);
}

std::shared_ptr<AssignStatement>
StatementFactory::createAssignStatementFromNode(const std::shared_ptr<StatementNode> &node) {
    return std::make_shared<AssignStatement>(node->getStatementNumber());
}

std::shared_ptr<CallStatement>
StatementFactory::createCallStatementFromNode(const std::shared_ptr<StatementNode> &node) {
    StatementNumber statementNumber = node->getStatementNumber();
    ProcedureName procName = std::static_pointer_cast<CallNode>(node)->getProcedureName();
    return std::make_shared<CallStatement>(statementNumber, procName);
}

std::shared_ptr<PrintStatement>
StatementFactory::createPrintStatementFromNode(const std::shared_ptr<StatementNode> &node) {
    StatementNumber statementNumber = node->getStatementNumber();
    std::shared_ptr<PrintNode> printNode = std::static_pointer_cast<PrintNode>(node);
    VariableName varName = printNode->getVar()->getVarName();
    return std::make_shared<PrintStatement>(statementNumber, varName);
}

std::shared_ptr<ReadStatement>
StatementFactory::createReadStatementFromNode(const std::shared_ptr<StatementNode> &node) {
    StatementNumber statementNumber = node->getStatementNumber();
    std::shared_ptr<ReadNode> readNode = std::static_pointer_cast<ReadNode>(node);
    VariableName varName = readNode->getVar()->getVarName();
    return std::make_shared<ReadStatement>(statementNumber, varName);
}

std::shared_ptr<IfStatement> StatementFactory::createIfStatementFromNode(const std::shared_ptr<StatementNode> &node) {
    return std::make_shared<IfStatement>(node->getStatementNumber());
}

std::shared_ptr<WhileStatement>
StatementFactory::createWhileStatementFromNode(const std::shared_ptr<StatementNode> &node) {
    return std::make_shared<WhileStatement>(node->getStatementNumber());
}

std::shared_ptr<Statement> StatementFactory::createStatement(StatementNumber statementNumber,
                                                             StatementType statementType, AttrValue attrValue) {
    return factoryMethodMap.at(statementType)(statementNumber, attrValue);
}

std::shared_ptr<AssignStatement> StatementFactory::createAssignStatement(StatementNumber statementNumber,
                                                                         const AttrValue &attrValue) {
    return std::make_shared<AssignStatement>(statementNumber);
}

std::shared_ptr<PrintStatement> StatementFactory::createPrintStatement(StatementNumber statementNumber,
                                                                       const AttrValue &varName) {
    return std::make_shared<PrintStatement>(statementNumber, varName);
}

std::shared_ptr<ReadStatement> StatementFactory::createReadStatement(StatementNumber statementNumber,
                                                                     const AttrValue &varName) {
    return std::make_shared<ReadStatement>(statementNumber, varName);
}

std::shared_ptr<IfStatement> StatementFactory::createIfStatement(StatementNumber statementNumber,
                                                                 const AttrValue &attrValue) {
    return std::make_shared<IfStatement>(statementNumber);
}

std::shared_ptr<WhileStatement> StatementFactory::createWhileStatement(StatementNumber statementNumber,
                                                                       const AttrValue &attrValue) {
    return std::make_shared<WhileStatement>(statementNumber);
}

std::shared_ptr<CallStatement> StatementFactory::createCallStatement(StatementNumber statementNumber,
                                                                     const AttrValue &procName) {
    return std::make_shared<CallStatement>(statementNumber, procName);
}