#include <vector>

#include "catch.hpp"
#include "SP/SPParser.h"
#include "SP/SPToken.h"
#include "SP/SPTokenType.h"
#include "SP/AST/Nodes/ProgramNode.h"
#include "TestingUtilities/ASTPrinter/ASTPrinter.h"
#include "TestingUtilities/ASTComparer/ASTComparer.h"

TEST_CASE("Test parse with one procedure, one read statement") {
    SPParser parser;
    VariableName varName= "num1";
    ProcedureName procName = "doMath";
    std::vector<SPToken> tokens = {
            SPToken(TokenType::Name, "procedure"),
            SPToken(TokenType::Name, procName),
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            SPToken(TokenType::Name, "read"),
            SPToken(TokenType::Name, varName),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::CloseCurlyParenthesis, "}")
    };

    std::shared_ptr<ProgramNode> parsedRootNode = parser.parse(tokens);

    // Create AST
    std::shared_ptr<VariableNode> varNode = std::make_shared<VariableNode>(varName);
    std::shared_ptr<ReadNode> readNode = std::make_shared<ReadNode>(1, varNode);

    std::vector<std::shared_ptr<StatementNode>> statements = { readNode };
    std::shared_ptr<StatementListNode> statementListNode = std::make_shared<StatementListNode>(statements);

    std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(procName, statementListNode);
    std::vector<std::shared_ptr<ProcedureNode>> procedures = { procedureNode };
    std::shared_ptr<ProgramNode> programNode = std::make_shared<ProgramNode>(procedures);

    REQUIRE(ASTComparer::isSameAST(parsedRootNode, programNode));
}

TEST_CASE("Test parse with one procedure, one print statement") {
    SPParser parser;
    VariableName varName = "num1";
    ProcedureName procName = "doMath";
    std::vector<SPToken> tokens = {
            SPToken(TokenType::Name, "procedure"),
            SPToken(TokenType::Name, procName),
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            SPToken(TokenType::Name, "print"),
            SPToken(TokenType::Name, varName),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::CloseCurlyParenthesis, "}")
    };

    std::shared_ptr<ProgramNode> parsedRootNode = parser.parse(tokens);

    // Create AST
    std::shared_ptr<VariableNode> varNode = std::make_shared<VariableNode>(varName);
    std::shared_ptr<PrintNode> printNode = std::make_shared<PrintNode>(1, varNode);

    std::vector<std::shared_ptr<StatementNode>> statements = { printNode };
    std::shared_ptr<StatementListNode> statementListNode = std::make_shared<StatementListNode>(statements);

    std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(procName, statementListNode);
    std::vector<std::shared_ptr<ProcedureNode>> procedures = { procedureNode };
    std::shared_ptr<ProgramNode> programNode = std::make_shared<ProgramNode>(procedures);

    REQUIRE(ASTComparer::isSameAST(parsedRootNode, programNode));
}

TEST_CASE("Test parse with one procedure, one assign statement") {
    SPParser parser;
    VariableName varName = "sum";
    ProcedureName procName = "doMath123";
    ConstantValue constVal = "12345";
    std::vector<SPToken> tokens = {
            SPToken(TokenType::Name, "procedure"),
            SPToken(TokenType::Name, procName),
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            SPToken(TokenType::Name, varName),
            SPToken(TokenType::Equals, "="),
            SPToken(TokenType::Integer, constVal),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::CloseCurlyParenthesis, "}")
    };

    std::shared_ptr<ProgramNode> parsedRootNode = parser.parse(tokens);

    // Create AST
    std::shared_ptr<VariableNode> varNode = std::make_shared<VariableNode>(varName);
    std::shared_ptr<ExpressionNode> exprNode = std::make_shared<ConstantNode>(constVal);
    std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1, varNode, exprNode);

    std::vector<std::shared_ptr<StatementNode>> statements = { assignNode };
    std::shared_ptr<StatementListNode> statementListNode = std::make_shared<StatementListNode>(statements);

    std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(procName, statementListNode);
    std::vector<std::shared_ptr<ProcedureNode>> procedures = { procedureNode };
    std::shared_ptr<ProgramNode> programNode = std::make_shared<ProgramNode>(procedures);

    REQUIRE(ASTComparer::isSameAST(parsedRootNode, programNode));

    ASTPrinter printerTraverser;
    printerTraverser.traverseAndPrint(parsedRootNode);
    printerTraverser.traverseAndPrint(programNode);
}

TEST_CASE("Test parse with one procedure, one assign statement, different RHS") {
    SPParser parser;

    SECTION("assign statement, RHS constant") {
        VariableName varName = "sum";
        ProcedureName procName = "doMath123";
        ConstantValue constVal = "12345";
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, procName),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, varName),
                SPToken(TokenType::Equals, "="),
                SPToken(TokenType::Integer, constVal),
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        std::shared_ptr<ProgramNode> parsedRootNode = parser.parse(tokens);

        // Create AST
        std::shared_ptr<VariableNode> varNode = std::make_shared<VariableNode>(varName);
        std::shared_ptr<ExpressionNode> exprNode = std::make_shared<ConstantNode>(constVal);
        std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1, varNode, exprNode);

        std::vector<std::shared_ptr<StatementNode>> statements = { assignNode };
        std::shared_ptr<StatementListNode> statementListNode = std::make_shared<StatementListNode>(statements);

        std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(procName, statementListNode);
        std::vector<std::shared_ptr<ProcedureNode>> procedures = { procedureNode };
        std::shared_ptr<ProgramNode> programNode = std::make_shared<ProgramNode>(procedures);

        REQUIRE(ASTComparer::isSameAST(parsedRootNode, programNode));
    }

    SECTION("assign statement, RHS variable") {
        VariableName varName1 = "sum";
        VariableName varName2 = "num1";
        ProcedureName procName = "doMath123";
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, procName),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, varName1),
                SPToken(TokenType::Equals, "="),
                SPToken(TokenType::Name, varName2),
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        std::shared_ptr<ProgramNode> parsedRootNode = parser.parse(tokens);

        // Create AST
        std::shared_ptr<VariableNode> varNode = std::make_shared<VariableNode>(varName1);
        std::shared_ptr<ExpressionNode> exprNode = std::make_shared<VariableNode>(varName2);
        std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1, varNode, exprNode);

        std::vector<std::shared_ptr<StatementNode>> statements = { assignNode };
        std::shared_ptr<StatementListNode> statementListNode = std::make_shared<StatementListNode>(statements);

        std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(procName, statementListNode);
        std::vector<std::shared_ptr<ProcedureNode>> procedures = { procedureNode };
        std::shared_ptr<ProgramNode> programNode = std::make_shared<ProgramNode>(procedures);

        REQUIRE(ASTComparer::isSameAST(parsedRootNode, programNode));
    }

    SECTION("assign statement, RHS simple arithmetic expression") {
        VariableName varName1 = "sum";
        VariableName varName2 = "num1";
        ProcedureName procName = "doMath123";
        ConstantValue constVal = "12345";
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, procName),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, varName1),
                SPToken(TokenType::Equals, "="),
                SPToken(TokenType::Name, varName2),
                SPToken(TokenType::ArithmeticOperator, "+"),
                SPToken(TokenType::Integer, constVal),
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        std::shared_ptr<ProgramNode> parsedRootNode = parser.parse(tokens);

        // Create AST
        std::shared_ptr<VariableNode> varNode = std::make_shared<VariableNode>(varName1);

        std::shared_ptr<ExpressionNode> exprNode = std::make_shared<ArithmeticExpressionNode>(
                ArithmeticOperatorType::Plus,
                std::make_shared<VariableNode>(varName2),
                std::make_shared<ConstantNode>(constVal)
            );

        std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1, varNode, exprNode);

        std::vector<std::shared_ptr<StatementNode>> statements = { assignNode };
        std::shared_ptr<StatementListNode> statementListNode = std::make_shared<StatementListNode>(statements);

        std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(procName, statementListNode);
        std::vector<std::shared_ptr<ProcedureNode>> procedures = { procedureNode };
        std::shared_ptr<ProgramNode> programNode = std::make_shared<ProgramNode>(procedures);

        REQUIRE(ASTComparer::isSameAST(parsedRootNode, programNode));
    }

    SECTION("assign statement, RHS nested arithmetic expression") {
        VariableName varX = "x";
        VariableName varY = "y";
        VariableName varZ = "z";
        VariableName varT = "t";
        VariableName varV = "v";
        ProcedureName procName = "doMath123";
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, procName),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                // x = v + x * y + z * t
                // varNode
                SPToken(TokenType::Name, varX),
                SPToken(TokenType::Equals, "="),
                // exprNode
                SPToken(TokenType::Name, varV),
                SPToken(TokenType::ArithmeticOperator, "+"),
                SPToken(TokenType::Name, varX),
                SPToken(TokenType::ArithmeticOperator, "*"),
                SPToken(TokenType::Name, varY),
                SPToken(TokenType::ArithmeticOperator, "+"),
                SPToken(TokenType::Name, varZ),
                SPToken(TokenType::ArithmeticOperator, "*"),
                SPToken(TokenType::Name, varT),
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        std::shared_ptr<ProgramNode> parsedRootNode = parser.parse(tokens);

        // Create AST
        std::shared_ptr<VariableNode> varNode = std::make_shared<VariableNode>(varX);

        // create exprNode
        std::shared_ptr<ArithmeticExpressionNode> x_y = std::make_shared<ArithmeticExpressionNode>(
                ArithmeticOperatorType::Times,
                std::make_shared<VariableNode>(varX),
                std::make_shared<VariableNode>(varY)
        );
        std::shared_ptr<ArithmeticExpressionNode> z_t = std::make_shared<ArithmeticExpressionNode>(
                ArithmeticOperatorType::Times,
                std::make_shared<VariableNode>(varZ),
                std::make_shared<VariableNode>(varT)
        );
        std::shared_ptr<ArithmeticExpressionNode> v_xy = std::make_shared<ArithmeticExpressionNode>(
                ArithmeticOperatorType::Plus,
                std::make_shared<VariableNode>(varV),
                x_y
        );
        std::shared_ptr<ExpressionNode> vxy_zt = std::make_shared<ArithmeticExpressionNode>(
                ArithmeticOperatorType::Plus,
                v_xy,
                z_t
        );

        std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1, varNode, vxy_zt);

        std::vector<std::shared_ptr<StatementNode>> statements = { assignNode };
        std::shared_ptr<StatementListNode> statementListNode = std::make_shared<StatementListNode>(statements);

        std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(procName, statementListNode);
        std::vector<std::shared_ptr<ProcedureNode>> procedures = { procedureNode };
        std::shared_ptr<ProgramNode> programNode = std::make_shared<ProgramNode>(procedures);

        REQUIRE(ASTComparer::isSameAST(parsedRootNode, programNode));
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

    /*
    procedure doMath {
        if (s + 1 + 2 + t * u % v == x) then {
            x = v + x * y + z * t;
        } else {
            x = 1 / (2 - 3) * w;
        }
    }
     */
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

    /*
    procedure doMath {
        while ((k) > (r)) {
            a = r;
        }
    }
     */
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

TEST_CASE("Test ASTPrinter") {
    SPParser parser;
    VariableName varName= "num1";
    std::vector<SPToken> tokens = {
            SPToken(TokenType::Name, "procedure"),
            SPToken(TokenType::Name, "procedure"),
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            SPToken(TokenType::Name, "while"),
            // Conditional expression ((!((...)&&(...)))||(!((...)&&(...))))
            SPToken(TokenType::OpenRoundParenthesis, "("),
            SPToken(TokenType::OpenRoundParenthesis, "("),
            SPToken(TokenType::ConditionalOperator, "!"),
            SPToken(TokenType::OpenRoundParenthesis, "("),
            SPToken(TokenType::OpenRoundParenthesis, "("),
            SPToken(TokenType::Name, "a"),
            SPToken(TokenType::RelationalOperator, ">="),
            SPToken(TokenType::Name, "b"),
            SPToken(TokenType::CloseRoundParenthesis, ")"),
            SPToken(TokenType::ConditionalOperator, "&&"),
            SPToken(TokenType::OpenRoundParenthesis, "("),
            SPToken(TokenType::Name, "a"),
            SPToken(TokenType::RelationalOperator, "<="),
            SPToken(TokenType::Name, "b"),
            SPToken(TokenType::CloseRoundParenthesis, ")"),
            SPToken(TokenType::CloseRoundParenthesis, ")"),
            SPToken(TokenType::CloseRoundParenthesis, ")"),
            SPToken(TokenType::ConditionalOperator, "||"),
            SPToken(TokenType::OpenRoundParenthesis, "("),
            SPToken(TokenType::ConditionalOperator, "!"),
            SPToken(TokenType::OpenRoundParenthesis, "("),
            SPToken(TokenType::OpenRoundParenthesis, "("),
            SPToken(TokenType::Name, "a"),
            SPToken(TokenType::RelationalOperator, ">="),
            SPToken(TokenType::Name, "b"),
            SPToken(TokenType::CloseRoundParenthesis, ")"),
            SPToken(TokenType::ConditionalOperator, "&&"),
            SPToken(TokenType::OpenRoundParenthesis, "("),
            SPToken(TokenType::Name, "a"),
            SPToken(TokenType::RelationalOperator, "<="),
            SPToken(TokenType::Name, "b"),
            SPToken(TokenType::CloseRoundParenthesis, ")"),
            SPToken(TokenType::CloseRoundParenthesis, ")"),
            SPToken(TokenType::CloseRoundParenthesis, ")"),
            SPToken(TokenType::CloseRoundParenthesis, ")"),
            // statement list
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            SPToken(TokenType::Name, "r"),
            SPToken(TokenType::Equals, "="),
            SPToken(TokenType::Name, "a"),
            SPToken(TokenType::ArithmeticOperator, "-"),
            SPToken(TokenType::Name, "b"),
            SPToken(TokenType::ArithmeticOperator, "/"),
            SPToken(TokenType::Integer, "3"),
            SPToken(TokenType::ArithmeticOperator, "+"),
            SPToken(TokenType::Integer, "2"),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::CloseCurlyParenthesis, "}"),

            SPToken(TokenType::CloseCurlyParenthesis, "}")
    };

    std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
    ASTPrinter printerTraverser;

    printerTraverser.traverseAndPrint(rootNode);
}