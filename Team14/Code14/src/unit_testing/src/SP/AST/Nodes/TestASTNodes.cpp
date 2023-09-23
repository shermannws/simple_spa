#include <memory>
#include <iostream>

#include "catch.hpp"
#include "SP/AST/Nodes/ASTNode.h"
#include "SP/AST/Nodes/ProgramNode.h"
#include "SP/AST/Nodes/ProcedureNode.h"
#include "SP/AST/Nodes/StatementListNode.h"
#include "SP/AST/Nodes/StatementNode.h"
#include "SP/AST/Nodes/AssignNode.h"
#include "SP/AST/Nodes/PrintNode.h"
#include "SP/AST/Nodes/ReadNode.h"
#include "SP/AST/Nodes/IfNode.h"
#include "SP/AST/Nodes/WhileNode.h"
#include "SP/AST/Nodes/CallNode.h"
#include "SP/AST/Nodes/ExpressionNode.h"
#include "SP/AST/Nodes/ArithmeticExpressionNode.h"
#include "SP/AST/Nodes/ArithmeticOperatorType.h"
#include "SP/AST/Nodes/VariableNode.h"
#include "SP/AST/Nodes/ConstantNode.h"
#include "SP/AST/Nodes/ConditionalExpressionNode.h"
#include "SP/AST/Nodes/BinaryConditionalExpressionNode.h"
#include "SP/AST/Nodes/UnaryConditionalExpressionNode.h"
#include "SP/AST/Nodes/RelativeExpressionNode.h"
#include "SP/AST/Nodes/ComparisonOperatorType.h"
#include "SP/AST/Nodes/BinaryConditionalExpressionType.h"

TEST_CASE("Test ExpressionNode family") {
    std::string varName1 = "Variable1";
    std::string varName2 = "Variable2";
    ConstantValue constVal1 = "100";
    ConstantValue constVal2 = "200";
    std::vector<std::shared_ptr<ASTNode>> emptyChildVector;

    auto varNode1 = std::make_shared<VariableNode>(varName1);
    REQUIRE(varNode1->getVarName() == varName1);
    REQUIRE(varNode1->getAllChildNodes() == emptyChildVector);

    auto varNode2 = std::make_shared<VariableNode>(varName2);
    REQUIRE(varNode2->getVarName() == varName2);
    REQUIRE(varNode2->getAllChildNodes() == emptyChildVector);

    auto constNode1 = std::make_shared<ConstantNode>(constVal1);
    REQUIRE(constNode1->getValue() == constVal1);
    REQUIRE(constNode1->getAllChildNodes() == emptyChildVector);

    auto constNode2 = std::make_shared<ConstantNode>(constVal2);
    REQUIRE(constNode2->getValue() == constVal2);
    REQUIRE(constNode2->getAllChildNodes() == emptyChildVector);

    // var left, const right
    auto arithmeticExpressionNode1 =
            std::make_shared<ArithmeticExpressionNode>(ArithmeticOperatorType::Times, varNode1, constNode1);
    REQUIRE(arithmeticExpressionNode1->getOperatorType() == ArithmeticOperatorType::Times);
    REQUIRE(arithmeticExpressionNode1->getLeftExpression() == varNode1);
    REQUIRE(arithmeticExpressionNode1->getRightExpression() == constNode1);
    auto childNodes1 = arithmeticExpressionNode1->getAllChildNodes();
    REQUIRE(childNodes1 == std::vector<std::shared_ptr<ASTNode>>{varNode1, constNode1});

    // const left, var right
    auto arithmeticExpressionNode2 =
            std::make_shared<ArithmeticExpressionNode>(ArithmeticOperatorType::Divide, constNode1, varNode1);
    REQUIRE(arithmeticExpressionNode2->getOperatorType() == ArithmeticOperatorType::Divide);
    REQUIRE(arithmeticExpressionNode2->getLeftExpression() == constNode1);
    REQUIRE(arithmeticExpressionNode2->getRightExpression() == varNode1);
    auto childNodes2 = arithmeticExpressionNode2->getAllChildNodes();
    REQUIRE(childNodes2 == std::vector<std::shared_ptr<ASTNode>>{constNode1, varNode1});

    // arithmetic exp left, var right
    auto arithmeticExpressionNode3 =
            std::make_shared<ArithmeticExpressionNode>(ArithmeticOperatorType::Modulo, arithmeticExpressionNode1, varNode2);
    REQUIRE(arithmeticExpressionNode3->getOperatorType() == ArithmeticOperatorType::Modulo);
    REQUIRE(arithmeticExpressionNode3->getLeftExpression() == arithmeticExpressionNode1);
    REQUIRE(arithmeticExpressionNode3->getRightExpression() == varNode2);
    auto childNodes3 = arithmeticExpressionNode3->getAllChildNodes();
    REQUIRE(childNodes3 == std::vector<std::shared_ptr<ASTNode>>{arithmeticExpressionNode1, varNode2});

    // arithmetic exp left, const right
    auto arithmeticExpressionNode4 =
            std::make_shared<ArithmeticExpressionNode>(ArithmeticOperatorType::Plus, arithmeticExpressionNode2, constNode2);
    REQUIRE(arithmeticExpressionNode4->getOperatorType() == ArithmeticOperatorType::Plus);
    REQUIRE(arithmeticExpressionNode4->getLeftExpression() == arithmeticExpressionNode2);
    REQUIRE(arithmeticExpressionNode4->getRightExpression() == constNode2);
    auto childNodes4 = arithmeticExpressionNode4->getAllChildNodes();
    REQUIRE(childNodes4 == std::vector<std::shared_ptr<ASTNode>>{arithmeticExpressionNode2, constNode2});

    // var left, arithmetic exp right
    auto arithmeticExpressionNode5 =
            std::make_shared<ArithmeticExpressionNode>(ArithmeticOperatorType::Minus, varNode2, arithmeticExpressionNode2);
    REQUIRE(arithmeticExpressionNode5->getOperatorType() == ArithmeticOperatorType::Minus);
    REQUIRE(arithmeticExpressionNode5->getLeftExpression() == varNode2);
    REQUIRE(arithmeticExpressionNode5->getRightExpression() == arithmeticExpressionNode2);
    auto childNodes5 = arithmeticExpressionNode5->getAllChildNodes();
    REQUIRE(childNodes5 == std::vector<std::shared_ptr<ASTNode>>{varNode2, arithmeticExpressionNode2});

    // const left, arithmetic exp right
    auto arithmeticExpressionNode6 =
            std::make_shared<ArithmeticExpressionNode>(ArithmeticOperatorType::Divide, constNode2, arithmeticExpressionNode2);
    REQUIRE(arithmeticExpressionNode6->getOperatorType() == ArithmeticOperatorType::Divide);
    REQUIRE(arithmeticExpressionNode6->getLeftExpression() == constNode2);
    REQUIRE(arithmeticExpressionNode6->getRightExpression() == arithmeticExpressionNode2);
    auto childNodes6 = arithmeticExpressionNode6->getAllChildNodes();
    REQUIRE(childNodes6 == std::vector<std::shared_ptr<ASTNode>>{constNode2, arithmeticExpressionNode2});

    // const left, const right
    auto arithmeticExpressionNode7 =
            std::make_shared<ArithmeticExpressionNode>(ArithmeticOperatorType::Modulo, constNode1, constNode2);
    REQUIRE(arithmeticExpressionNode7->getOperatorType() == ArithmeticOperatorType::Modulo);
    REQUIRE(arithmeticExpressionNode7->getLeftExpression() == constNode1);
    REQUIRE(arithmeticExpressionNode7->getRightExpression() == constNode2);
    auto childNodes7 = arithmeticExpressionNode7->getAllChildNodes();
    REQUIRE(childNodes7 == std::vector<std::shared_ptr<ASTNode>>{constNode1, constNode2});

    // var left, var right
    auto arithmeticExpressionNode8 =
            std::make_shared<ArithmeticExpressionNode>(ArithmeticOperatorType::Plus, varNode1, varNode2);
    REQUIRE(arithmeticExpressionNode8->getOperatorType() == ArithmeticOperatorType::Plus);
    REQUIRE(arithmeticExpressionNode8->getLeftExpression() == varNode1);
    REQUIRE(arithmeticExpressionNode8->getRightExpression() == varNode2);
    auto childNodes8 = arithmeticExpressionNode8->getAllChildNodes();
    REQUIRE(childNodes8 == std::vector<std::shared_ptr<ASTNode>>{varNode1, varNode2});

    // arithmetic exp left, arithmetic exp right
    auto arithmeticExpressionNode9 =
            std::make_shared<ArithmeticExpressionNode>(ArithmeticOperatorType::Times, arithmeticExpressionNode5, arithmeticExpressionNode6);
    REQUIRE(arithmeticExpressionNode9->getOperatorType() == ArithmeticOperatorType::Times);
    REQUIRE(arithmeticExpressionNode9->getLeftExpression() == arithmeticExpressionNode5);
    REQUIRE(arithmeticExpressionNode9->getRightExpression() == arithmeticExpressionNode6);
    auto childNodes9 = arithmeticExpressionNode9->getAllChildNodes();
    REQUIRE(childNodes9 == std::vector<std::shared_ptr<ASTNode>>{arithmeticExpressionNode5, arithmeticExpressionNode6});

    SECTION("Test polymorphic behaviour") {
        std::shared_ptr<ExpressionNode> expressionNode1 = arithmeticExpressionNode1;
        REQUIRE(expressionNode1 == arithmeticExpressionNode1);

        std::shared_ptr<ExpressionNode> expressionNode2 = arithmeticExpressionNode2;
        REQUIRE(expressionNode2 == arithmeticExpressionNode2);

        std::shared_ptr<ExpressionNode> expressionNode3 = arithmeticExpressionNode3;
        REQUIRE(expressionNode3 == arithmeticExpressionNode3);

        std::shared_ptr<ExpressionNode> expressionNode4 = arithmeticExpressionNode4;
        REQUIRE(expressionNode4 == arithmeticExpressionNode4);

        std::shared_ptr<ExpressionNode> expressionNode5 = arithmeticExpressionNode5;
        REQUIRE(expressionNode5 == arithmeticExpressionNode5);

        std::shared_ptr<ExpressionNode> expressionNode6 = arithmeticExpressionNode6;
        REQUIRE(expressionNode6 == arithmeticExpressionNode6);

        std::shared_ptr<ExpressionNode> expressionNode7 = arithmeticExpressionNode7;
        REQUIRE(expressionNode7 == arithmeticExpressionNode7);

        std::shared_ptr<ExpressionNode> expressionNode8 = arithmeticExpressionNode8;
        REQUIRE(expressionNode8 == arithmeticExpressionNode8);

        std::shared_ptr<ExpressionNode> expressionNode9 = arithmeticExpressionNode9;
        REQUIRE(expressionNode9 == arithmeticExpressionNode9);
    }
}

TEST_CASE("Test ConditionalExpressionNode family") {
    std::string varName1 = "Variable1";
    std::string varName2 = "Variable2";
    ConstantValue constVal1 = "100";
    ConstantValue constVal2 = "200";

    std::shared_ptr<ExpressionNode> expNode1 = std::make_shared<VariableNode>(varName1);
    std::shared_ptr<ExpressionNode> expNode2 = std::make_shared<VariableNode>(varName2);
    std::shared_ptr<ExpressionNode> expNode3 = std::make_shared<ConstantNode>(constVal1);
    std::shared_ptr<ExpressionNode> expNode4 = std::make_shared<ConstantNode>(constVal2);

    SECTION("RelativeExpressionNode tests") {
        // Test each ComparisonOperatorType
        for (int op = static_cast<int>(ComparisonOperatorType::GreaterThan);
             op <= static_cast<int>(ComparisonOperatorType::NotEqual); ++op) {
            ComparisonOperatorType operatorType = static_cast<ComparisonOperatorType>(op);
            std::shared_ptr<RelativeExpressionNode> relativeNode =
                    std::make_shared<RelativeExpressionNode>(operatorType, expNode1, expNode2);

            // Check the ComparisonOperatorType
            REQUIRE(relativeNode->getComparisonOperatorType() == operatorType);

            // Check the left and right expressions
            REQUIRE(relativeNode->getLeftExpression() == expNode1);
            REQUIRE(relativeNode->getRightExpression() == expNode2);
            REQUIRE(relativeNode->getAllChildNodes() == std::vector<std::shared_ptr<ASTNode>>{ expNode1, expNode2 });
        }

        SECTION("Polymorphic behavior tests") {
            std::shared_ptr<ConditionalExpressionNode> condNode = std::make_shared<RelativeExpressionNode>(
                    ComparisonOperatorType::LessThan, expNode1, expNode2);
        }
    }

    SECTION("UnaryConditionalExpression tests") {
        // Create a ConditionalExpressionNode instance for testing
        std::shared_ptr<ConditionalExpressionNode> conditionalExp = std::make_shared<RelativeExpressionNode>(
                ComparisonOperatorType::GreaterThanEqual, expNode3, expNode4);

        std::shared_ptr<UnaryConditionalExpressionNode> unaryNode =
                std::make_shared<UnaryConditionalExpressionNode>(conditionalExp);

        REQUIRE(unaryNode->getConditionalExpression() == conditionalExp);
        REQUIRE(unaryNode->getAllChildNodes() == std::vector<std::shared_ptr<ASTNode>>{ conditionalExp });

        SECTION("Polymorphic behavior tests") {
            std::shared_ptr<ConditionalExpressionNode> condNode = unaryNode;
        }
    }

    SECTION("BinaryConditionalExpression tests") {
        std::shared_ptr<ConditionalExpressionNode> leftConditionalExp = std::make_shared<RelativeExpressionNode>(
                ComparisonOperatorType::GreaterThanEqual, expNode3, expNode4);

        std::shared_ptr<ConditionalExpressionNode> rightConditionalExp =
                std::make_shared<UnaryConditionalExpressionNode>(leftConditionalExp);

        // Test each BinaryConditionalExpressionType
        for (int type = static_cast<int>(BinaryConditionalExpressionType::And);
             type <= static_cast<int>(BinaryConditionalExpressionType::Or); ++type) {
            BinaryConditionalExpressionType binaryType = static_cast<BinaryConditionalExpressionType>(type);
            std::shared_ptr<BinaryConditionalExpressionNode> binaryNode =
                    std::make_shared<BinaryConditionalExpressionNode>(binaryType, leftConditionalExp, rightConditionalExp);

            // Check the BinaryConditionalExpressionType
            REQUIRE(binaryNode->getBinaryConditionalExpressionType() == binaryType);

            // Check the left and right conditional expressions
            REQUIRE(binaryNode->getLeftConditionalExpression() == leftConditionalExp);
            REQUIRE(binaryNode->getRightConditionalExpression() == rightConditionalExp);
        }

        SECTION("Polymorphic behavior tests") {
            std::shared_ptr<ConditionalExpressionNode> condNode = std::make_shared<BinaryConditionalExpressionNode>(
                    BinaryConditionalExpressionType::And, leftConditionalExp, rightConditionalExp);
        }
    }
}

TEST_CASE("Test statement family") {
    int statementNumber = 1;
    ConstantValue constVal1 = "100";
    ConstantValue constVal2 = "200";
    std::vector<std::shared_ptr<ASTNode>> emptyChildVector;
    std::string procedureName = "Procedure";
    auto varNode = std::make_shared<VariableNode>("variable");
    auto constNode = std::make_shared<ConstantNode>("100");
    auto arithmeticExpressionNode =
            std::make_shared<ArithmeticExpressionNode>(ArithmeticOperatorType::Times, varNode, constNode);
    std::shared_ptr<ExpressionNode> expressionNode = arithmeticExpressionNode;

    auto readNode = std::make_shared<ReadNode>(statementNumber++, varNode);
    REQUIRE(readNode->getVar() == varNode);
    REQUIRE(readNode->getStatementType() == StatementNodeType::Read);
    REQUIRE(readNode->getAllChildNodes() == std::vector<std::shared_ptr<ASTNode>>{ varNode });

    auto printNode = std::make_shared<PrintNode>(statementNumber++, varNode);
    REQUIRE(printNode->getVar() == varNode);
    REQUIRE(printNode->getStatementType() == StatementNodeType::Print);
    REQUIRE(printNode->getAllChildNodes() == std::vector<std::shared_ptr<ASTNode>>{ varNode });

    auto callNode = std::make_shared<CallNode>(statementNumber++, procedureName);
    REQUIRE(callNode->getProcedureName() == procedureName);
    REQUIRE(callNode->getStatementType() == StatementNodeType::Call);
    REQUIRE(callNode->getAllChildNodes() == emptyChildVector);

    // RHS expressionNode
    auto assignNode1 = std::make_shared<AssignNode>(statementNumber++, varNode, expressionNode);
    REQUIRE(assignNode1->getVar() == varNode);
    REQUIRE(assignNode1->getExpression() == expressionNode);
    REQUIRE(assignNode1->getStatementType() == StatementNodeType::Assign);
    REQUIRE(assignNode1->getAllChildNodes() == std::vector<std::shared_ptr<ASTNode>>{ varNode, expressionNode });

    // RHS arithmeticExpressionNode
    auto assignNode2 = std::make_shared<AssignNode>(statementNumber++, varNode, arithmeticExpressionNode);
    REQUIRE(assignNode2->getVar() == varNode);
    REQUIRE(assignNode2->getExpression() == arithmeticExpressionNode);
    REQUIRE(assignNode2->getStatementType() == StatementNodeType::Assign);
    REQUIRE(assignNode2->getAllChildNodes() == std::vector<std::shared_ptr<ASTNode>>{ varNode, arithmeticExpressionNode });

    // RHS constNode
    auto assignNode3 = std::make_shared<AssignNode>(statementNumber++, varNode, constNode);
    REQUIRE(assignNode3->getVar() == varNode);
    REQUIRE(assignNode3->getExpression() == constNode);
    REQUIRE(assignNode3->getStatementType() == StatementNodeType::Assign);
    REQUIRE(assignNode3->getAllChildNodes() == std::vector<std::shared_ptr<ASTNode>>{ varNode, constNode });

    // RHS varNode
    auto assignNode4 = std::make_shared<AssignNode>(statementNumber++, varNode, varNode);
    REQUIRE(assignNode4->getVar() == varNode);
    REQUIRE(assignNode4->getExpression() == varNode);
    REQUIRE(assignNode4->getStatementType() == StatementNodeType::Assign);
    REQUIRE(assignNode4->getAllChildNodes() == std::vector<std::shared_ptr<ASTNode>>{ varNode, varNode });

    std::vector<std::shared_ptr<StatementNode>> statements1 = {
            readNode, printNode,
    };
    std::vector<std::shared_ptr<StatementNode>> statements2 = {
            assignNode2, assignNode3, assignNode4
    };
    std::vector<std::shared_ptr<StatementNode>> statements3 = {
            assignNode1, callNode
    };

    auto statementListNode1 = std::make_shared<StatementListNode>(statements1);
    auto statementListNode2 = std::make_shared<StatementListNode>(statements2);
    auto statementListNode3 = std::make_shared<StatementListNode>(statements3);
    auto statementListNode1Copy = statementListNode1;
    REQUIRE(statementListNode1 != statementListNode2);
    REQUIRE(statementListNode1 == statementListNode1Copy);

    std::shared_ptr<ExpressionNode> expNode1 = std::make_shared<ConstantNode>(constVal1);
    std::shared_ptr<ExpressionNode> expNode2 = std::make_shared<ConstantNode>(constVal2);
    std::shared_ptr<ConditionalExpressionNode> condExpNode =
            std::make_shared<RelativeExpressionNode>(ComparisonOperatorType::GreaterThanEqual, expNode1, expNode2);
    auto ifNode =
            std::make_shared<IfNode>(statementNumber++, condExpNode, statementListNode1, statementListNode2);
    REQUIRE(ifNode->getStatementType() == StatementNodeType::If);
    std::vector<std::shared_ptr<ASTNode>> ifChildren = { condExpNode, statementListNode1, statementListNode2 };
    REQUIRE(ifNode->getAllChildNodes() == ifChildren);
    REQUIRE(ifNode->getConditionalExpression() == condExpNode);
    REQUIRE(ifNode->getThenStatementList() == statementListNode1);
    REQUIRE(ifNode->getElseStatementList() == statementListNode2);

    auto whileNode =
            std::make_shared<WhileNode>(statementNumber++, condExpNode, statementListNode1);
    REQUIRE(whileNode->getStatementType() == StatementNodeType::While);
    std::vector<std::shared_ptr<ASTNode>> whileChildren = { condExpNode, statementListNode1 };
    REQUIRE(whileNode->getAllChildNodes() == whileChildren);
    REQUIRE(whileNode->getConditionalExpression() == condExpNode);
    REQUIRE(whileNode->getStatementList() == statementListNode1);

    //add if and while tests
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
                ifNode,
                whileNode,
                callNode,
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

    ConstantValue value = "100";
    auto constNode = std::make_shared<ConstantNode>("value");
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

TEST_CASE("Test ExpressionNode toString() method") {
    // test case of 3
    auto constantNode3 = ConstantNode("3");
    std::shared_ptr<ExpressionNode> expression = std::make_shared<ConstantNode>(constantNode3);
    assert(expression->toString() == "(3)");

    // test case of (2+v)
    std::shared_ptr<ExpressionNode> constantNode2 = std::make_shared<ConstantNode>(ConstantNode("2"));
    std::shared_ptr<ExpressionNode> varV = std::make_shared<VariableNode>(VariableNode("v"));
    std::shared_ptr<ExpressionNode> expression2 = std::make_shared<ArithmeticExpressionNode>(ArithmeticExpressionNode(ArithmeticOperatorType::Plus, constantNode2, varV));
    assert(expression2->toString() == "((2)+(v))");

    // test case of ((2+v)*(10/g)-8)
    std::shared_ptr<ExpressionNode> constantNode10 = std::make_shared<ConstantNode>(ConstantNode("10"));
    std::shared_ptr<ExpressionNode> varG = std::make_shared<VariableNode>(VariableNode("g"));
    std::shared_ptr<ExpressionNode> expression3 = std::make_shared<ArithmeticExpressionNode>(ArithmeticExpressionNode(ArithmeticOperatorType::Divide, constantNode10, varG));

    std::shared_ptr<ExpressionNode> expression4 = std::make_shared<ArithmeticExpressionNode>(ArithmeticExpressionNode(ArithmeticOperatorType::Times, expression2, expression3));

    std::shared_ptr<ExpressionNode> constantNode8 = std::make_shared<ConstantNode>(ConstantNode("8"));
    std::shared_ptr<ExpressionNode> expression5 = std::make_shared<ArithmeticExpressionNode>(ArithmeticExpressionNode(ArithmeticOperatorType::Minus, expression4, constantNode8));
    assert(expression5->toString() == "((((2)+(v))*((10)/(g)))-(8))");
}