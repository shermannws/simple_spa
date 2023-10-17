#include <string>

#include "SP/SPParser.h"
#include "SP/Validators/SemanticValidator/SemanticValidator.h"
#include "SP/Validators/SyntacticValidator/SyntacticValidator.h"
#include "catch.hpp"

TEST_CASE("SemanticValidator - Valid semantics") {
    SECTION("Valid call chain") {
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
                SPToken(TokenType::CloseCurlyParenthesis, "}")};
        std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
        REQUIRE_NOTHROW(semanticValidator.validate(rootNode));
    }
}

TEST_CASE("SemanticValidator - Invalid semantics") {
    SECTION("Non-existing procedure") {
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
        REQUIRE_THROWS_WITH(semanticValidator.validate(rootNode),
                            "Semantic error: Called non-existing procedure");
    }

    SECTION("Duplicate procedure name") {
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
                SPToken(TokenType::CloseCurlyParenthesis, "}")};
        std::shared_ptr<ProgramNode> rootNode = parser.parse(tokens);
        REQUIRE_THROWS_WITH(
                semanticValidator.validate(rootNode),
                "Semantic error: Repeated procedure names detected");
    }

    SECTION("Recursive call - procedure calls itself") {
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
        REQUIRE_THROWS_WITH(semanticValidator.validate(rootNode),
                            "Semantic error: Cyclic procedure calls detected");
    }

    SECTION("Recursive call - chain") {
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
        REQUIRE_THROWS_WITH(semanticValidator.validate(rootNode),
                            "Semantic error: Cyclic procedure calls detected");
    }
}