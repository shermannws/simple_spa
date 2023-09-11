#include <vector>

#include "catch.hpp"
#include "SP/SPParser.h"
#include "SP/SPToken.h"
#include "SP/SPTokenType.h"
#include "SP/AST/Nodes/ASTNode.h"
#include "SP/AST/Nodes/ProgramNode.h"

TEST_CASE("Test parse with one procedure, one statement") {
    SPParser parser;

    SECTION("one procedure, one read statement") {
        std::string varName = "num1";
        std::vector<SPToken> tokens = {
                SPToken(TokenType::NAME, "procedure"),
                SPToken(TokenType::NAME, "doMath"),
                SPToken(TokenType::OPEN_CURLY_PARAN, "{"),
                SPToken(TokenType::NAME, "read"),
                SPToken(TokenType::NAME, varName),
                SPToken(TokenType::SEMICOLON, ";"),
                SPToken(TokenType::CLOSE_CURLY_PARAN, "}")
        };
        std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
        REQUIRE(rootNode->getProcedures().size() == 1);

        std::shared_ptr<ProcedureNode> procedureNode = rootNode->getProcedures()[0];
        std::shared_ptr<StatementListNode> statementListNode = procedureNode->getStatementList();
        std::vector<std::shared_ptr<StatementNode>> statements = statementListNode->getStatements();
        REQUIRE(statements.size() == 1);

        std::shared_ptr<StatementNode> statement = statements[0];
        std::shared_ptr<ReadNode> readStatement = std::dynamic_pointer_cast<ReadNode>(statement);
        REQUIRE(readStatement != nullptr);
        REQUIRE(readStatement->getStatementNumber() == 1);
        REQUIRE(readStatement->getVar()->getVarName() == varName);
    }

    SECTION("one procedure, one print statement") {
        std::string varName = "num1";
        std::vector<SPToken> tokens = {
                SPToken(TokenType::NAME, "procedure"),
                SPToken(TokenType::NAME, "doMath"),
                SPToken(TokenType::OPEN_CURLY_PARAN, "{"),
                SPToken(TokenType::NAME, "print"),
                SPToken(TokenType::NAME, varName),
                SPToken(TokenType::SEMICOLON, ";"),
                SPToken(TokenType::CLOSE_CURLY_PARAN, "}")
        };
        std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
        REQUIRE(rootNode->getProcedures().size() == 1);

        std::shared_ptr<ProcedureNode> procedureNode = rootNode->getProcedures()[0];
        std::shared_ptr<StatementListNode> statementListNode = procedureNode->getStatementList();
        std::vector<std::shared_ptr<StatementNode>> statements = statementListNode->getStatements();
        REQUIRE(statements.size() == 1);

        std::shared_ptr<StatementNode> statement = statements[0];
        std::shared_ptr<PrintNode> printStatement = std::dynamic_pointer_cast<PrintNode>(statement);
        REQUIRE(printStatement != nullptr);
        REQUIRE(printStatement->getStatementNumber() == 1);
        REQUIRE(printStatement->getVar()->getVarName() == varName);
    }

    SECTION("one procedure, one assign statement") {
        std::string varName = "sum";
        std::vector<SPToken> tokens = {
                SPToken(TokenType::NAME, "procedure"),
                SPToken(TokenType::NAME, "doMath"),
                SPToken(TokenType::OPEN_CURLY_PARAN, "{"),
                SPToken(TokenType::NAME, varName),
                SPToken(TokenType::EQUALS, "="),
                SPToken(TokenType::INTEGER, "1"),
                SPToken(TokenType::SEMICOLON, ";"),
                SPToken(TokenType::CLOSE_CURLY_PARAN, "}")
        };
        std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
        REQUIRE(rootNode->getProcedures().size() == 1);

        std::shared_ptr<ProcedureNode> procedureNode = rootNode->getProcedures()[0];
        std::shared_ptr<StatementListNode> statementListNode = procedureNode->getStatementList();
        std::vector<std::shared_ptr<StatementNode>> statements = statementListNode->getStatements();
        REQUIRE(statements.size() == 1);

        std::shared_ptr<StatementNode> statement = statements[0];
        std::shared_ptr<AssignNode> assignStatement = std::dynamic_pointer_cast<AssignNode>(statement);
        REQUIRE(assignStatement != nullptr);
        REQUIRE(assignStatement->getStatementNumber() == 1);
        REQUIRE(assignStatement->getVar()->getVarName() == varName);

        std::shared_ptr<ExpressionNode> expression = assignStatement->getExpression();
        std::shared_ptr<ConstantNode> constantNode = std::dynamic_pointer_cast<ConstantNode>(expression);
        REQUIRE(constantNode != nullptr);
        REQUIRE(constantNode->getValue() == 1);
    }
}

TEST_CASE("Test parse with one procedure, one assign statement") {
    SPParser parser;

    // TODO: fix TokenType::INTEGER causing issues
    SECTION("assign statement, RHS constant") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::NAME, "procedure"),
                SPToken(TokenType::NAME, "doMath"),
                SPToken(TokenType::OPEN_CURLY_PARAN, "{"),
                SPToken(TokenType::NAME, "sum"),
                SPToken(TokenType::EQUALS, "="),
                SPToken(TokenType::INTEGER, "1"),
                SPToken(TokenType::SEMICOLON, ";"),
                SPToken(TokenType::CLOSE_CURLY_PARAN, "}")
        };
        std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
    }

    SECTION("assign statement, RHS variable") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::NAME, "procedure"),
                SPToken(TokenType::NAME, "doMath"),
                SPToken(TokenType::OPEN_CURLY_PARAN, "{"),
                SPToken(TokenType::NAME, "sum"),
                SPToken(TokenType::EQUALS, "="),
                SPToken(TokenType::NAME, "num1"),
                SPToken(TokenType::SEMICOLON, ";"),
                SPToken(TokenType::CLOSE_CURLY_PARAN, "}")
        };
        std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
    }

    // TODO: fix
    SECTION("assign statement, RHS simple arithmetic expression") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::NAME, "procedure"),
                SPToken(TokenType::NAME, "doMath"),
                SPToken(TokenType::OPEN_CURLY_PARAN, "{"),
                SPToken(TokenType::NAME, "sum"),
                SPToken(TokenType::EQUALS, "="),
                SPToken(TokenType::NAME, "num1"),
                SPToken(TokenType::ARITHMETIC_OPERATOR, "+"),
                SPToken(TokenType::INTEGER, "1"),
                SPToken(TokenType::SEMICOLON, ";"),
                SPToken(TokenType::CLOSE_CURLY_PARAN, "}")
        };
        std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
    }

    SECTION("assign statement, RHS nested arithmetic expression") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::NAME, "procedure"),
                SPToken(TokenType::NAME, "doMath"),
                SPToken(TokenType::OPEN_CURLY_PARAN, "{"),
                SPToken(TokenType::NAME, "x"),
                SPToken(TokenType::EQUALS, "="),
                SPToken(TokenType::NAME, "v"),
                SPToken(TokenType::ARITHMETIC_OPERATOR, "+"),
                SPToken(TokenType::NAME, "x"),
                SPToken(TokenType::ARITHMETIC_OPERATOR, "*"),
                SPToken(TokenType::NAME, "y"),
                SPToken(TokenType::ARITHMETIC_OPERATOR, "+"),
                SPToken(TokenType::NAME, "z"),
                SPToken(TokenType::ARITHMETIC_OPERATOR, "*"),
                SPToken(TokenType::NAME, "t"),
                SPToken(TokenType::SEMICOLON, ";"),
                SPToken(TokenType::CLOSE_CURLY_PARAN, "}")
        };
        std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
    }
}

TEST_CASE("Test parse with one procedure, all statement types") {
    SPParser parser;
    std::string varName = "num1";

    std::vector<SPToken> tokens = {
            SPToken(TokenType::NAME, "procedure"),
            SPToken(TokenType::NAME, "doMath"),
            SPToken(TokenType::OPEN_CURLY_PARAN, "{"),
            SPToken(TokenType::NAME, "x"),
            SPToken(TokenType::EQUALS, "="),
            SPToken(TokenType::NAME, "v"),
            SPToken(TokenType::ARITHMETIC_OPERATOR, "+"),
            SPToken(TokenType::NAME, "x"),
            SPToken(TokenType::ARITHMETIC_OPERATOR, "*"),
            SPToken(TokenType::NAME, "y"),
            SPToken(TokenType::ARITHMETIC_OPERATOR, "+"),
            SPToken(TokenType::NAME, "z"),
            SPToken(TokenType::ARITHMETIC_OPERATOR, "*"),
            SPToken(TokenType::NAME, "t"),
            SPToken(TokenType::SEMICOLON, ";"),
            SPToken(TokenType::NAME, "read"),
            SPToken(TokenType::NAME, varName),
            SPToken(TokenType::SEMICOLON, ";"),
            SPToken(TokenType::NAME, "print"),
            SPToken(TokenType::NAME, varName),
            SPToken(TokenType::SEMICOLON, ";"),
            SPToken(TokenType::CLOSE_CURLY_PARAN, "}")
    };
    std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
}