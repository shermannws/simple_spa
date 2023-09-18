#include <memory>

#include "catch.hpp"
#include "SP/AST/Nodes/ASTNode.h"
#include "SP/AST/Nodes/ProgramNode.h"
#include "SP/AST/Nodes/ProcedureNode.h"
#include "SP/AST/Nodes/StatementListNode.h"
#include "SP/AST/Nodes/StatementNode.h"
#include "SP/AST/Nodes/AssignNode.h"
#include "SP/AST/Nodes/PrintNode.h"
#include "SP/AST/Nodes/ReadNode.h"
#include "SP/AST/Nodes/ExpressionNode.h"
#include "SP/AST/Nodes/ArithmeticExpressionNode.h"
#include "SP/AST/Nodes/ArithmeticOperatorType.h"
#include "SP/AST/Nodes/VariableNode.h"
#include "SP/AST/Nodes/ConstantNode.h"

TEST_CASE("Test constructors for nodes") {
    int statementNumber = 1;
    auto varNode = std::make_shared<VariableNode>("variable");
    auto constNode = std::make_shared<ConstantNode>(100);
    auto arithmeticExpressionNode =
            std::make_shared<ArithmeticExpressionNode>(ArithmeticOperatorType::Times, varNode, constNode);
    std::shared_ptr<ExpressionNode> expressionNode = arithmeticExpressionNode;
    REQUIRE(expressionNode == arithmeticExpressionNode);

    auto readNode = std::make_shared<ReadNode>(statementNumber++, varNode);
    auto printNode = std::make_shared<PrintNode>(statementNumber++, varNode);
    auto assignNode1 = std::make_shared<AssignNode>(statementNumber++, varNode, expressionNode);
    auto assignNode2 = std::make_shared<AssignNode>(statementNumber++, varNode, arithmeticExpressionNode);
    auto assignNode3 = std::make_shared<AssignNode>(statementNumber++, varNode, constNode);
    auto assignNode4 = std::make_shared<AssignNode>(statementNumber++, varNode, varNode);
    std::shared_ptr<StatementNode> statementNode1 = assignNode1;
    std::shared_ptr<StatementNode> statementNode2 = readNode;
    std::shared_ptr<StatementNode> statementNode3 = printNode;

    REQUIRE(assignNode1 == statementNode1);
    REQUIRE(readNode == statementNode2);
    REQUIRE(printNode == statementNode3);

    std::vector<std::shared_ptr<StatementNode>> statements1 = {
            readNode, printNode, assignNode1
    };
    std::vector<std::shared_ptr<StatementNode>> statements2 = {
            assignNode2, assignNode3, assignNode4
    };
    auto statementListNode1 = std::make_shared<StatementListNode>(statements1);
    auto statementListNode2 = std::make_shared<StatementListNode>(statements2);
    auto statementListNode1Copy = statementListNode1;
    REQUIRE(statementListNode1 != statementListNode2);
    REQUIRE(statementListNode1 == statementListNode1Copy);

    auto procedureNode1 = std::make_shared<ProcedureNode>("Procedure1", statementListNode1);
    auto procedureNode2 = std::make_shared<ProcedureNode>("Procedure2", statementListNode2);
    auto procedureNode1Copy = procedureNode1;
    REQUIRE(procedureNode1 != procedureNode2);
    REQUIRE(procedureNode1 == procedureNode1Copy);

    std::vector<std::shared_ptr<ProcedureNode>> procedures = {
            procedureNode1, procedureNode2
    };
    auto programNode = std::make_shared<ProgramNode>(procedures);


    SECTION("Test that all nodes are subtypes of ASTNode") {
        std::vector<std::shared_ptr<ASTNode>> astNodes = {
                varNode,
                constNode,
                arithmeticExpressionNode,
                expressionNode,
                readNode,
                printNode,
                assignNode2,
                statementNode1,
                statementListNode1,
                procedureNode1,
                programNode
        };
    }
}

TEST_CASE("Test AST node getters") {
    int statementNumber = 1;

    std::string varName = "variable";
    auto varNode = std::make_shared<VariableNode>(varName);
    REQUIRE(varNode->getVarName() == varName);

    int value = 100;
    auto constNode = std::make_shared<ConstantNode>(value);
    REQUIRE(constNode->getValue() == value);

    ArithmeticOperatorType operatorType = ArithmeticOperatorType::Times;
    auto arithmeticExpressionNode =
            std::make_shared<ArithmeticExpressionNode>(operatorType, varNode, constNode);
    REQUIRE(arithmeticExpressionNode->getOperatorType() == operatorType);
    REQUIRE(arithmeticExpressionNode->getRightExpression() == constNode);
    REQUIRE(arithmeticExpressionNode->getLeftExpression() == varNode);

    int readStatementNumber = statementNumber++;
    auto readNode = std::make_shared<ReadNode>(readStatementNumber, varNode);
    REQUIRE(readNode->getStatementNumber() == readStatementNumber);
    REQUIRE(readNode->getVar() == varNode);

    int printStatementNumber = statementNumber++;
    auto printNode = std::make_shared<PrintNode>(printStatementNumber, varNode);
    REQUIRE(printNode->getStatementNumber() == printStatementNumber);
    REQUIRE(printNode->getVar() == varNode);

    int assignStatementNumber = statementNumber++;
    auto assignNode = std::make_shared<AssignNode>(assignStatementNumber, varNode, arithmeticExpressionNode);
    REQUIRE(assignNode->getStatementNumber() == assignStatementNumber);
    REQUIRE(assignNode->getVar() == varNode);
    REQUIRE(assignNode->getExpression() == arithmeticExpressionNode);

    std::vector<std::shared_ptr<StatementNode>> statements = {
            readNode, printNode, assignNode
    };
    auto statementListNode = std::make_shared<StatementListNode>(statements);
    REQUIRE(statementListNode->getStatements() == statements);

    std::string procedureName = "Procedure";
    auto procedureNode = std::make_shared<ProcedureNode>(procedureName, statementListNode);
    REQUIRE(procedureNode->getProcedureName() == procedureName);
    REQUIRE(procedureNode->getStatementList() == statementListNode);

    std::vector<std::shared_ptr<ProcedureNode>> procedures = {
            procedureNode
    };
    auto programNode = std::make_shared<ProgramNode>(procedures);
    REQUIRE(programNode->getProcedures() == procedures);
}