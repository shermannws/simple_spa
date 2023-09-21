#include <string>

#include "catch.hpp"
#include "SP/SPParser.h"
#include "SP/SyntacticValidator.h"
#include "SP/AST/SemanticValidator/SemanticValidator.h"

TEST_CASE("SEMANTIC VALIDATION - valid call") {
    SPParser parser;
    SemanticValidator semanticValidator;
    std::vector<SPToken> tokens = {
            SPToken(TokenType::Name, "procedure"),
            SPToken(TokenType::Name, "A"),
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            SPToken(TokenType::Name, "call"),
            SPToken(TokenType::Name, "B"),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::CloseCurlyParenthesis, "}"),
            SPToken(TokenType::Name, "procedure"),
            SPToken(TokenType::Name, "B"),
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            SPToken(TokenType::Name, "print"),
            SPToken(TokenType::Name, "C"),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::CloseCurlyParenthesis, "}")
    };
    std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
    REQUIRE_NOTHROW(semanticValidator.validate(rootNode));
}

TEST_CASE("SEMANTIC VALIDATION - invalid call") {
    SPParser parser;
    SemanticValidator semanticValidator;
    std::vector<SPToken> tokens = {
            SPToken(TokenType::Name, "procedure"),
            SPToken(TokenType::Name, "A"),
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            SPToken(TokenType::Name, "call"),
            SPToken(TokenType::Name, "B"),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::CloseCurlyParenthesis, "}"),
    };
    std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
    REQUIRE_THROWS_WITH(semanticValidator.validate(rootNode), "Semantic error: Called non-existing procedure");
}

TEST_CASE("SEMANTIC VALIDATION - duplicate procedure name") {
    SPParser parser;
    SemanticValidator semanticValidator;
    std::vector<SPToken> tokens = {
            SPToken(TokenType::Name, "procedure"),
            SPToken(TokenType::Name, "A"),
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            SPToken(TokenType::Name, "call"),
            SPToken(TokenType::Name, "B"),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::CloseCurlyParenthesis, "}"),
            SPToken(TokenType::Name, "procedure"),
            SPToken(TokenType::Name, "A"),
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            SPToken(TokenType::Name, "call"),
            SPToken(TokenType::Name, "C"),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::CloseCurlyParenthesis, "}")
    };
    std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
    REQUIRE_THROWS_WITH(semanticValidator.validate(rootNode), "Semantic error: Repeated procedure names detected");
}

TEST_CASE("SEMANTIC VALIDATION - recursive call 1") {
    SPParser parser;
    SemanticValidator semanticValidator;
    std::vector<SPToken> tokens = {
            SPToken(TokenType::Name, "procedure"),
            SPToken(TokenType::Name, "A"),
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            SPToken(TokenType::Name, "call"),
            SPToken(TokenType::Name, "A"),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::CloseCurlyParenthesis, "}"),
    };
    std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
    REQUIRE_THROWS_WITH(semanticValidator.validate(rootNode), "Semantic error: Cyclic procedure calls detected");
}

TEST_CASE("SEMANTIC VALIDATION - recursive call 2") {
    SPParser parser;
    SemanticValidator semanticValidator;
    std::vector<SPToken> tokens = {
            SPToken(TokenType::Name, "procedure"),
            SPToken(TokenType::Name, "A"),
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            SPToken(TokenType::Name, "call"),
            SPToken(TokenType::Name, "B"),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::CloseCurlyParenthesis, "}"),
            SPToken(TokenType::Name, "procedure"),
            SPToken(TokenType::Name, "B"),
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            SPToken(TokenType::Name, "call"),
            SPToken(TokenType::Name, "C"),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::CloseCurlyParenthesis, "}"),
            SPToken(TokenType::Name, "procedure"),
            SPToken(TokenType::Name, "C"),
            SPToken(TokenType::OpenCurlyParenthesis, "{"),
            SPToken(TokenType::Name, "call"),
            SPToken(TokenType::Name, "A"),
            SPToken(TokenType::Semicolon, ";"),
            SPToken(TokenType::CloseCurlyParenthesis, "}"),
    };
    std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
    REQUIRE_THROWS_WITH(semanticValidator.validate(rootNode), "Semantic error: Cyclic procedure calls detected");
}