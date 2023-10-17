#include <unordered_map>
#include <memory>
#include <functional>

#include "StatementFactory.h"
#include "StatementTypeFactory.h"
#include "SP/AST/Nodes/CallNode.h"
#include "SP/AST/Nodes/PrintNode.h"
#include "SP/AST/Nodes/ReadNode.h"

std::unordered_map<StatementType, std::function<std::shared_ptr<Statement>(std::shared_ptr<StatementNode>)>> StatementFactory::factoryMethodMap = {
        { StatementType::Assign, createAssignStatement },
        { StatementType::Call, createCallStatement },
        { StatementType::Print, createPrintStatement },
        { StatementType::Read, createReadStatement },
        { StatementType::If, createIfStatement },
        { StatementType::While, createWhileStatement }
};

std::shared_ptr<Statement> StatementFactory::createStatementFromStatementNode(const std::shared_ptr<StatementNode>& node) {
    StatementNodeType statementNodeType = node->getStatementType();
    StatementType statementType = StatementTypeFactory::getStatementTypeFrom(statementNodeType);

    return factoryMethodMap.at(statementType)(node);
}

std::shared_ptr<AssignStatement> StatementFactory::createAssignStatement(const std::shared_ptr<StatementNode>& node) {
    return std::make_shared<AssignStatement>(node->getStatementNumber());
}

std::shared_ptr<CallStatement> StatementFactory::createCallStatement(const std::shared_ptr<StatementNode>& node) {
    StatementNumber statementNumber = node->getStatementNumber();
    ProcedureName procName = std::static_pointer_cast<CallNode>(node)->getProcedureName();
    return std::make_shared<CallStatement>(statementNumber, procName);
}

std::shared_ptr<PrintStatement> StatementFactory::createPrintStatement(const std::shared_ptr<StatementNode>& node) {
    StatementNumber statementNumber = node->getStatementNumber();
    std::shared_ptr<PrintNode> printNode = std::static_pointer_cast<PrintNode>(node);
    VariableName varName = printNode->getVar()->getVarName();
    return std::make_shared<PrintStatement>(statementNumber, varName);
}

std::shared_ptr<ReadStatement> StatementFactory::createReadStatement(const std::shared_ptr<StatementNode>& node) {
    StatementNumber statementNumber = node->getStatementNumber();
    std::shared_ptr<ReadNode> readNode = std::static_pointer_cast<ReadNode>(node);
    VariableName varName = readNode->getVar()->getVarName();
    return std::make_shared<ReadStatement>(statementNumber, varName);
}

std::shared_ptr<IfStatement> StatementFactory::createIfStatement(const std::shared_ptr<StatementNode>& node) {
    return std::make_shared<IfStatement>(node->getStatementNumber());
}

std::shared_ptr<WhileStatement> StatementFactory::createWhileStatement(const std::shared_ptr<StatementNode>& node) {
    return std::make_shared<WhileStatement>(node->getStatementNumber());
}