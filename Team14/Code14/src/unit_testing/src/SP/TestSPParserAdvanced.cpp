#include <vector>

#include "catch.hpp"
#include "SP/SPParser.h"
#include "SP/SPToken.h"
#include "SP/SPTokenType.h"
#include "SP/AST/Nodes/ProgramNode.h"

TEST_CASE("Valid program with single statements") {
    SPParser parser;

    SECTION("Single read") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "read"),
                SPToken(TokenType::Name, "var1"),
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        REQUIRE_NOTHROW(parser.parse(tokens));
    }

    SECTION("Single print") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "print"),
                SPToken(TokenType::Name, "var1"),
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        REQUIRE_NOTHROW(parser.parse(tokens));
    }

    SECTION("Single assign") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, "procedure"),
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
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        REQUIRE_NOTHROW(parser.parse(tokens));
    }

    SECTION("Single if") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "if"),
                // Conditional expression
                SPToken(TokenType::OpenRoundParenthesis, "("),
                SPToken(TokenType::Name, "s"),
                SPToken(TokenType::RelationalOperator, "=="),
                SPToken(TokenType::Name, "x"),
                SPToken(TokenType::CloseRoundParenthesis, ")"),

                SPToken(TokenType::Name, "then"),
                // then statement list
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "x"),
                SPToken(TokenType::Equals, "="),
                SPToken(TokenType::Name, "v"),
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}"),

                SPToken(TokenType::Name, "else"),
                // else statement list
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "x"),
                SPToken(TokenType::Equals, "="),
                SPToken(TokenType::Integer, "1"),
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}"),

                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        REQUIRE_NOTHROW(parser.parse(tokens));
    }

    SECTION("Single while") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "while"),
                // Conditional expression
                SPToken(TokenType::OpenRoundParenthesis, "("),
                SPToken(TokenType::Name, "k"),
                SPToken(TokenType::RelationalOperator, ">"),
                SPToken(TokenType::Name, "1"),
                SPToken(TokenType::CloseRoundParenthesis, ")"),

                // statement list
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
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

TEST_CASE("Valid program with multiple statements") {
    SPParser parser;

    std::vector<SPToken> tokens = {
            SPToken(TokenType::Name, "procedure"),
            SPToken(TokenType::Name, "procedure"),
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            // read statement
            SPToken(TokenType::Name, "read"),
            SPToken(TokenType::Name, "var1"),
            SPToken(TokenType::Semicolon, ";"),
            // print statement
            SPToken(TokenType::Name, "print"),
            SPToken(TokenType::Name, "var1"),
            SPToken(TokenType::Semicolon, ";"),
            // assign statement
            SPToken(TokenType::Name, "x"),
            SPToken(TokenType::Equals, "="),
            SPToken(TokenType::Integer, "1"),
            SPToken(TokenType::ArithmeticOperator, "/"),
            SPToken(TokenType::OpenRoundParenthesis, "("),
            SPToken(TokenType::Integer, "2"),
            SPToken(TokenType::ArithmeticOperator, "-"),
            SPToken(TokenType::Integer, "3"),
            SPToken(TokenType::CloseRoundParenthesis, ")"),
            SPToken(TokenType::Semicolon, ";"),
            // if with assign
            SPToken(TokenType::Name, "if"),
            SPToken(TokenType::OpenRoundParenthesis, "("),
            SPToken(TokenType::Name, "s"),
            SPToken(TokenType::RelationalOperator, "<="),
            SPToken(TokenType::Name, "x"),
            SPToken(TokenType::CloseRoundParenthesis, ")"),
            SPToken(TokenType::Name, "then"),
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            SPToken(TokenType::Name, "x"),
            SPToken(TokenType::Equals, "="),
            SPToken(TokenType::Name, "v"),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::CloseCurlyParenthesis, "}"),
            SPToken(TokenType::Name, "else"),
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            SPToken(TokenType::Name, "x"),
            SPToken(TokenType::Equals, "="),
            SPToken(TokenType::Integer, "1"),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::CloseCurlyParenthesis, "}"),
            // while with read and print
            SPToken(TokenType::Name, "while"),
            SPToken(TokenType::OpenRoundParenthesis, "("),
            SPToken(TokenType::Name, "k"),
            SPToken(TokenType::RelationalOperator, ">"),
            SPToken(TokenType::Name, "1"),
            SPToken(TokenType::CloseRoundParenthesis, ")"),
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            SPToken(TokenType::Name, "print"),
            SPToken(TokenType::Name, "var1"),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::Name, "read"),
            SPToken(TokenType::Name, "var2"),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::CloseCurlyParenthesis, "}"),

            SPToken(TokenType::CloseCurlyParenthesis, "}")
    };
    REQUIRE_NOTHROW(parser.parse(tokens));
}

TEST_CASE("Valid program to test conditional expressions") {
    SPParser parser;

    SECTION("Simple rel_expr") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "while"),
                // Conditional expression
                SPToken(TokenType::OpenRoundParenthesis, "("),
                SPToken(TokenType::Name, "a"),
                SPToken(TokenType::RelationalOperator, ">"),
                SPToken(TokenType::Name, "b"),
                SPToken(TokenType::CloseRoundParenthesis, ")"),
                // statement list
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "a"),
                SPToken(TokenType::Equals, "="),
                SPToken(TokenType::Name, "r"),
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}"),

                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        REQUIRE_NOTHROW(parser.parse(tokens));
    }

    SECTION("Simple unary cond_expr") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "while"),
                // Conditional expression
                SPToken(TokenType::OpenRoundParenthesis, "("),
                SPToken(TokenType::ConditionalOperator, "!"),
                SPToken(TokenType::OpenRoundParenthesis, "("),
                SPToken(TokenType::Name, "a"),
                SPToken(TokenType::RelationalOperator, "<"),
                SPToken(TokenType::Name, "b"),
                SPToken(TokenType::CloseRoundParenthesis, ")"),
                SPToken(TokenType::CloseRoundParenthesis, ")"),
                // statement list
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "a"),
                SPToken(TokenType::Equals, "="),
                SPToken(TokenType::Name, "r"),
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}"),

                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        REQUIRE_NOTHROW(parser.parse(tokens));
    }

    SECTION("Simple binary cond_expr") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "while"),
                // Conditional expression
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
                // statement list
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "a"),
                SPToken(TokenType::Equals, "="),
                SPToken(TokenType::Name, "r"),
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}"),

                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        REQUIRE_NOTHROW(parser.parse(tokens));
    }

    SECTION("Nested unary cond_expr, !(simple_unary)") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "while"),
                // Conditional expression
                SPToken(TokenType::OpenRoundParenthesis, "("),
                SPToken(TokenType::ConditionalOperator, "!"),
                SPToken(TokenType::OpenRoundParenthesis, "("),
                SPToken(TokenType::ConditionalOperator, "!"),
                SPToken(TokenType::OpenRoundParenthesis, "("),
                SPToken(TokenType::Name, "a"),
                SPToken(TokenType::RelationalOperator, "!="),
                SPToken(TokenType::Name, "b"),
                SPToken(TokenType::CloseRoundParenthesis, ")"),
                SPToken(TokenType::CloseRoundParenthesis, ")"),
                SPToken(TokenType::CloseRoundParenthesis, ")"),
                // statement list
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "a"),
                SPToken(TokenType::Equals, "="),
                SPToken(TokenType::Name, "r"),
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}"),

                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        REQUIRE_NOTHROW(parser.parse(tokens));
    }

    SECTION("Nested unary cond_expr, !(simple_binary)") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "while"),
                // Conditional expression
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
                // statement list
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "a"),
                SPToken(TokenType::Equals, "="),
                SPToken(TokenType::Name, "r"),
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}"),

                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        REQUIRE_NOTHROW(parser.parse(tokens));
    }

    SECTION("Nested binary cond_expr, (simple_unary) (simple_unary)") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "while"),
                // Conditional expression ((!(...))&&(!(...)))
                SPToken(TokenType::OpenRoundParenthesis, "("),
                SPToken(TokenType::OpenRoundParenthesis, "("),
                SPToken(TokenType::ConditionalOperator, "!"),
                SPToken(TokenType::OpenRoundParenthesis, "("),
                SPToken(TokenType::Name, "a"),
                SPToken(TokenType::RelationalOperator, ">="),
                SPToken(TokenType::Name, "b"),
                SPToken(TokenType::CloseRoundParenthesis, ")"),
                SPToken(TokenType::CloseRoundParenthesis, ")"),
                SPToken(TokenType::ConditionalOperator, "&&"),
                SPToken(TokenType::OpenRoundParenthesis, "("),
                SPToken(TokenType::ConditionalOperator, "!"),
                SPToken(TokenType::OpenRoundParenthesis, "("),
                SPToken(TokenType::Name, "a"),
                SPToken(TokenType::RelationalOperator, "<="),
                SPToken(TokenType::Name, "b"),
                SPToken(TokenType::CloseRoundParenthesis, ")"),
                SPToken(TokenType::CloseRoundParenthesis, ")"),
                SPToken(TokenType::CloseRoundParenthesis, ")"),
                // statement list
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "a"),
                SPToken(TokenType::Equals, "="),
                SPToken(TokenType::Name, "r"),
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}"),

                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        REQUIRE_NOTHROW(parser.parse(tokens));
    }

    SECTION("Nested binary cond_expr, (simple_binary) (simple_binary)") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "while"),
                // Conditional expression (((...)&&(...))&&((...)&&(...)))
                SPToken(TokenType::OpenRoundParenthesis, "("),
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
                SPToken(TokenType::ConditionalOperator, "&&"),
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
                // statement list
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "a"),
                SPToken(TokenType::Equals, "="),
                SPToken(TokenType::Name, "r"),
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}"),

                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        REQUIRE_NOTHROW(parser.parse(tokens));
    }

    SECTION("Nested binary cond_expr, (nested_binary) (nested_binary)") {
        std::vector<SPToken> tokens = {
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::Name, "procedure"),
                SPToken(TokenType::OpenCurlyParenthesis, "{"),
                SPToken(TokenType::Name, "while"),
                // Conditional expression ((((...)&&(...))&&((...)&&(...)))||(((...)&&(...))&&((...)&&(...))))
                SPToken(TokenType::OpenRoundParenthesis, "("),
                SPToken(TokenType::OpenRoundParenthesis, "("),
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
                SPToken(TokenType::ConditionalOperator, "&&"),
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
                SPToken(TokenType::ConditionalOperator, "&&"),
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
                SPToken(TokenType::Name, "a"),
                SPToken(TokenType::Equals, "="),
                SPToken(TokenType::Name, "r"),
                SPToken(TokenType::Semicolon, ";"),
                SPToken(TokenType::CloseCurlyParenthesis, "}"),

                SPToken(TokenType::CloseCurlyParenthesis, "}")
        };
        REQUIRE_NOTHROW(parser.parse(tokens));
    }

    SECTION("Nested binary cond_expr, (nested_unary) (nested_unary)") {
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