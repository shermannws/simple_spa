#include <vector>

#include "catch.hpp"
#include "SP/SPParser.h"
#include "SP/SPToken.h"
#include "SP/SPTokenType.h"
#include "SP/AST/Nodes/ProgramNode.h"

TEST_CASE("Test parse with one procedure, one read statement") {
    SPParser parser;
    VariableName = "num1";
    std::vector<SPToken> tokens = {
            SPToken(TokenType::Name, "procedure"),
            SPToken(TokenType::Name, "doMath"),
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            SPToken(TokenType::Name, "read"),
            SPToken(TokenType::Name, varName),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::CloseCurlyParenthesis, "}")
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

TEST_CASE("Test parse with one procedure, one print statement") {
    SPParser parser;
        VariableName varName = "num1";
    std::vector<SPToken> tokens = {
            SPToken(TokenType::Name, "procedure"),
            SPToken(TokenType::Name, "doMath"),
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            SPToken(TokenType::Name, "print"),
            SPToken(TokenType::Name, varName),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::CloseCurlyParenthesis, "}")
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

TEST_CASE("Test parse with one procedure, one assign statement") {
    SPParser parser;
    VariableName varName = "sum";
    std::vector<SPToken> tokens = {
            SPToken(TokenType::Name, "procedure"),
            SPToken(TokenType::Name, "doMath"),
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            SPToken(TokenType::Name, varName),
            SPToken(TokenType::Equals, "="),
            SPToken(TokenType::Integer, "1"),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::CloseCurlyParenthesis, "}")
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
    REQUIRE(constantNode->getValue() == "1");
}


TEST_CASE("Test parse with one procedure, one assign statement, different RHS") {
    SPParser parser;

    SECTION("assign statement, RHS constant") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, "doMath"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "sum"),
                SPToken(TokenType::Equals, "="),
                SPToken(TokenType::Integer, "1"),
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
    }

    SECTION("assign statement, RHS variable") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, "doMath"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "sum"),
                SPToken(TokenType::Equals, "="),
                SPToken(TokenType::Name, "num1"),
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
    }

    SECTION("assign statement, RHS simple arithmetic expression") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, "doMath"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "sum"),
                SPToken(TokenType::Equals, "="),
                SPToken(TokenType::Name, "num1"),
                SPToken(TokenType::ArithmeticOperator, "+"),
                SPToken(TokenType::Integer, "1"),
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };

        std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
    }

    SECTION("assign statement, RHS nested arithmetic expression") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, "doMath"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "x"),
                SPToken(TokenType::Equals, "="),
                SPToken(TokenType::Name, "v"),
                SPToken(TokenType::ArithmeticOperator, "+"),
                SPToken(TokenType::Name, "x"),
                SPToken(TokenType::ArithmeticOperator, "*"),
                SPToken(TokenType::Name, "y"),
                SPToken(TokenType::ArithmeticOperator, "+"),
                SPToken(TokenType::Name, "z"),
                SPToken(TokenType::ArithmeticOperator, "*"),
                SPToken(TokenType::Name, "t"),
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
    }

    SECTION("assign statement, RHS nested arithmetic expression") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, "doMath"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "x"),
                SPToken(TokenType::Equals, "="),
                SPToken(TokenType::Name, "v"),
                SPToken(TokenType::ArithmeticOperator, "+"),
                SPToken(TokenType::Name, "x"),
                SPToken(TokenType::ArithmeticOperator, "*"),
                SPToken(TokenType::Name, "y"),
                SPToken(TokenType::ArithmeticOperator, "+"),
                SPToken(TokenType::Name, "z"),
                SPToken(TokenType::ArithmeticOperator, "*"),
                SPToken(TokenType::Name, "t"),
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
    }
}

TEST_CASE("Test parse with one procedure, all statement types") {
    SPParser parser;
    VariableName varName = "num1";

    std::vector<SPToken> tokens = {
            SPToken(TokenType::Name, "procedure"),
            SPToken(TokenType::Name, "doMath"),
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            SPToken(TokenType::Name, "x"),
            SPToken(TokenType::Equals, "="),
            SPToken(TokenType::Name, "v"),
            SPToken(TokenType::ArithmeticOperator, "+"),
            SPToken(TokenType::Name, "x"),
            SPToken(TokenType::ArithmeticOperator, "*"),
            SPToken(TokenType::Name, "y"),
            SPToken(TokenType::ArithmeticOperator, "+"),
            SPToken(TokenType::Name, "z"),
            SPToken(TokenType::ArithmeticOperator, "*"),
            SPToken(TokenType::Name, "t"),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::Name, "read"),
            SPToken(TokenType::Name, varName),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::Name, "print"),
            SPToken(TokenType::Name, varName),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::CloseCurlyParenthesis, "}")
    };

    std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
}

TEST_CASE("Tests parse with one procedure, one if statement with one assign statement for each statementlist") {
    SPParser parser;

    SECTION("Complicated conditional expression 1") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, "doMath"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "if"),
                SPToken(TokenType::OpenRoundParenthesis, "("),
                // Conditional expression
                SPToken(TokenType::Name, "s"),
                SPToken(TokenType::ArithmeticOperator, "+"),
                SPToken(TokenType::Integer, "1"),
                SPToken(TokenType::ArithmeticOperator, "+"),
                SPToken(TokenType::Integer, "2"),
                SPToken(TokenType::ArithmeticOperator, "+"),
                SPToken(TokenType::Name, "t"),
                SPToken(TokenType::ArithmeticOperator, "*"),
                SPToken(TokenType::Name, "u"),
                SPToken(TokenType::ArithmeticOperator, "%"),
                SPToken(TokenType::Name, "v"),
                SPToken(TokenType::RelationalOperator, "=="),
                SPToken(TokenType::Name, "x"),

                SPToken(TokenType::CloseRoundParenthesis, ")"),
                SPToken(TokenType::Name, "then"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                // then statement list
                SPToken(TokenType::Name, "x"),
                SPToken(TokenType::Equals, "="),
                SPToken(TokenType::Name, "v"),
                SPToken(TokenType::ArithmeticOperator, "+"),
                SPToken(TokenType::Name, "x"),
                SPToken(TokenType::ArithmeticOperator, "*"),
                SPToken(TokenType::Name, "y"),
                SPToken(TokenType::ArithmeticOperator, "+"),
                SPToken(TokenType::Name, "z"),
                SPToken(TokenType::ArithmeticOperator, "*"),
                SPToken(TokenType::Name, "t"),
                SPToken(TokenType::Semicolon, ";"),

                SPToken(TokenType::CloseCurlyParenthesis, "}"),
                // else statement list
                SPToken(TokenType::Name, "else"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "x"),
                SPToken(TokenType::Equals, "="),
                SPToken(TokenType::Integer, "1"),
                SPToken(TokenType::ArithmeticOperator, "/"),
                SPToken(TokenType::OpenRoundParenthesis, "("),
                SPToken(TokenType::Integer, "2"),
                SPToken(TokenType::ArithmeticOperator, "-"),
                SPToken(TokenType::Integer, "3"),
                SPToken(TokenType::CloseRoundParenthesis, ")"),
                SPToken(TokenType::ArithmeticOperator, "*"),
                SPToken(TokenType::Name, "w"),
                SPToken(TokenType::Semicolon, ";"),

                SPToken(TokenType::CloseCurlyParenthesis, "}"),
                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        REQUIRE_NOTHROW(parser.parse(tokens));
    }
}

TEST_CASE("Tests parse with one procedure, one while statement with one assign statement") {
    SPParser parser;

    SECTION("Complicated conditional expression 1") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, "doMath"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "while"),
                SPToken(TokenType::OpenRoundParenthesis, "("),
                // Conditional expression
                SPToken(TokenType::OpenRoundParenthesis, "("),
                SPToken(TokenType::Name, "k"),
                SPToken(TokenType::CloseRoundParenthesis, ")"),
                SPToken(TokenType::RelationalOperator, ">"),
                SPToken(TokenType::OpenRoundParenthesis, "("),
                SPToken(TokenType::Name, "r"),
                SPToken(TokenType::CloseRoundParenthesis, ")"),

                SPToken(TokenType::CloseRoundParenthesis, ")"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                // statement list
                SPToken(TokenType::Name, "a"),
                SPToken(TokenType::Equals, "="),
                SPToken(TokenType::Name, "r"),
                SPToken(TokenType::Semicolon, ";"),

                SPToken(TokenType::CloseCurlyParenthesis, "}"),
                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        REQUIRE_NOTHROW(parser.parse(tokens));
    }
}
