#include "../TestingUtilities/TestFixture/UnitTestFixture.h"
#include "QPS/Parsers/ExprSpecParser.h"

#include "catch.hpp"

TEST_CASE_METHOD(UnitTestFixture, "extractExpressionSpec") {
    SECTION("wildcard") {
        std::string input = "_";
        auto tokenizer = std::make_shared<Tokenizer>(input);
        auto parser = std::make_shared<ExprSpecParser>(tokenizer);
        auto actual = parser->extractExpressionSpec();

        REQUIRE(actual.first == ExpressionSpecType::Wildcard);
        REQUIRE(actual.second.empty());
    }

    SECTION("only const value") {
        std::string input = "\"9999\"";
        auto tokenizer = std::make_shared<Tokenizer>(input);
        auto parser = std::make_shared<ExprSpecParser>(tokenizer);
        auto actual = parser->extractExpressionSpec();

        REQUIRE(actual.first == ExpressionSpecType::ExactMatch);
        REQUIRE(actual.second == "(9999)");
    }

    SECTION("only var name") {
        std::string input = "_\"thisisaverylongvariablename123\"_";
        std::string expected = "(thisisaverylongvariablename123)";

        auto tokenizer = std::make_shared<Tokenizer>(input);
        auto parser = std::make_shared<ExprSpecParser>(tokenizer);
        auto actual = parser->extractExpressionSpec();
        REQUIRE(actual.first == ExpressionSpecType::PartialMatch);
        REQUIRE(actual.second == expected);
    }

    SECTION("only var name with brackets") {
        std::string input = "\"(v)\"";
        std::string expected = "(v)";

        auto tokenizer = std::make_shared<Tokenizer>(input);
        auto parser = std::make_shared<ExprSpecParser>(tokenizer);
        auto actual = parser->extractExpressionSpec();
        REQUIRE(actual.first == ExpressionSpecType::ExactMatch);
        REQUIRE(actual.second == expected);
    }

    SECTION("only var name with multiple brackets") {
        std::string input = "\"((v))\"";
        std::string expected = "(v)";

        auto tokenizer = std::make_shared<Tokenizer>(input);
        auto parser = std::make_shared<ExprSpecParser>(tokenizer);
        auto actual = parser->extractExpressionSpec();
        REQUIRE(actual.first == ExpressionSpecType::ExactMatch);
        REQUIRE(actual.second == expected);
    }

    SECTION("all operators, no brackets") {
        std::string input = "\"x + y % z * 3 - a + b / q / 9\"";
        std::string expected = "((((x)+(((y)%(z))*(3)))-(a))+(((b)/(q))/(9)))";

        auto tokenizer = std::make_shared<Tokenizer>(input);
        auto parser = std::make_shared<ExprSpecParser>(tokenizer);
        auto actual = parser->extractExpressionSpec();
        REQUIRE(actual.first == ExpressionSpecType::ExactMatch);
        REQUIRE(actual.second == expected);
    }

    SECTION("brackets with more than 1 operator") {
        std::string input = "\"(x+1) * 8 % q - (a+b+c)     +1\"";
        std::string expected = "((((((x)+(1))*(8))%(q))-(((a)+(b))+(c)))+(1))";

        auto tokenizer = std::make_shared<Tokenizer>(input);
        auto parser = std::make_shared<ExprSpecParser>(tokenizer);
        auto actual = parser->extractExpressionSpec();
        REQUIRE(actual.first == ExpressionSpecType::ExactMatch);
        REQUIRE(actual.second == expected);
    }

    SECTION("nested brackets ") {
        std::string input = "\"x * (b * a + (n + (1%c))) \"";
        std::string expected = "((x)*(((b)*(a))+((n)+((1)%(c)))))";
        auto tokenizer = std::make_shared<Tokenizer>(input);
        auto parser = std::make_shared<ExprSpecParser>(tokenizer);
        auto actual = parser->extractExpressionSpec();
        REQUIRE(actual.first == ExpressionSpecType::ExactMatch);
        REQUIRE(actual.second == expected);
    }

    SECTION("invalid const value") {
        std::string input = "\"09999\"";
        auto tokenizer = std::make_shared<Tokenizer>(input);
        auto parser = std::make_shared<ExprSpecParser>(tokenizer);
        REQUIRE_THROWS_WITH(parser->extractExpressionSpec(), "Invalid expression spec");
    }

    SECTION("invalid expressions") {
        std::string input = "\"x+(y-z\"";
        auto tokenizer = std::make_shared<Tokenizer>(input);
        auto parser = std::make_shared<ExprSpecParser>(tokenizer);
        REQUIRE_THROWS_WITH(parser->extractExpressionSpec(), "not enough factors");
    }
}
