#include <string>

#include "../../TestingUtilities/TestFixture/UnitTestFixture.h"
#include "Commons/AppConstants.h"
#include "SP/SPTokenizer.h"
#include "catch.hpp"

TEST_CASE_METHOD(UnitTestFixture, "SPTokenizer - Valid Tokens") {

    SECTION("Name token") {
        std::string input = "var1 var2 var3 var4";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();

        REQUIRE(tokens.size() == 4);

        // check each token individually using .at() method
        REQUIRE(tokens.at(0).getType() == TokenType::Name);
        REQUIRE(tokens.at(0).getValue() == "var1");
        REQUIRE(tokens.at(1).getValue() == "var2");
        REQUIRE(tokens.at(2).getValue() == "var3");
        REQUIRE(tokens.at(3).getValue() == "var4");
    }

    SECTION("Name token with whitespace") {
        std::string input = "var1   var2";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();

        REQUIRE(tokens.size() == 2);

        // check each token individually using .at() method
        REQUIRE(tokens.at(0).getType() == TokenType::Name);
        REQUIRE(tokens.at(0).getValue() == "var1");
        REQUIRE(tokens.at(1).getValue() == "var2");
    }

    SECTION("Name and Integer tokens") {
        std::string input = "var1 123 var2 456";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();

        REQUIRE(tokens.size() == 4);

        REQUIRE(tokens.at(0).getType() == TokenType::Name);
        REQUIRE(tokens.at(0).getValue() == "var1");
        REQUIRE(tokens.at(1).getType() == TokenType::Integer);
        REQUIRE(tokens.at(1).getValue() == "123");
        REQUIRE(tokens.at(2).getType() == TokenType::Name);
        REQUIRE(tokens.at(2).getValue() == "var2");
        REQUIRE(tokens.at(3).getType() == TokenType::Integer);
        REQUIRE(tokens.at(3).getValue() == "456");
    }

    SECTION("Name and Integer with white space") {
        std::string input = "1 2 3 456 001 100 100000 1x10";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.size() == 9);
        REQUIRE(tokens.at(0).getType() == TokenType::Integer);
        REQUIRE(tokens.at(1).getType() == TokenType::Integer);
        REQUIRE(tokens.at(2).getType() == TokenType::Integer);
        REQUIRE(tokens.at(3).getType() == TokenType::Integer);
        REQUIRE(tokens.at(4).getType() == TokenType::Integer);
        REQUIRE(tokens.at(5).getType() == TokenType::Integer);
        REQUIRE(tokens.at(6).getType() == TokenType::Integer);
        REQUIRE(tokens.at(7).getType() == TokenType::Integer);
        REQUIRE(tokens.at(7).getValue() == "1");
        REQUIRE(tokens.at(8).getType() == TokenType::Name);
        REQUIRE(tokens.at(8).getValue() == "x10");
    }

    SECTION("Parenthesis test") {
        std::string input = "( hello world ) {1} {{}}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();

        REQUIRE(tokens.size() == 11);

        REQUIRE(tokens.at(0).getType() == TokenType::OpenRoundParenthesis);
        REQUIRE(tokens.at(1).getType() == TokenType::Name);
        REQUIRE(tokens.at(2).getType() == TokenType::Name);
        REQUIRE(tokens.at(3).getType() == TokenType::CloseRoundParenthesis);
        REQUIRE(tokens.at(4).getType() == TokenType::OpenCurlyParenthesis);
        REQUIRE(tokens.at(5).getType() == TokenType::Integer);
        REQUIRE(tokens.at(6).getType() == TokenType::CloseCurlyParenthesis);
        REQUIRE(tokens.at(7).getType() == TokenType::OpenCurlyParenthesis);
        REQUIRE(tokens.at(8).getType() == TokenType::OpenCurlyParenthesis);
        REQUIRE(tokens.at(9).getType() == TokenType::CloseCurlyParenthesis);
        REQUIRE(tokens.at(10).getType() == TokenType::CloseCurlyParenthesis);
    }

    SECTION("Semicolon and Equals test") {
        std::string input = "(=);{abc 123xyz}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();

        REQUIRE(tokens.size() == 9);

        REQUIRE(tokens.at(0).getType() == TokenType::OpenRoundParenthesis);
        REQUIRE(tokens.at(1).getType() == TokenType::Equals);
        REQUIRE(tokens.at(2).getType() == TokenType::CloseRoundParenthesis);
        REQUIRE(tokens.at(3).getType() == TokenType::Semicolon);
        REQUIRE(tokens.at(4).getType() == TokenType::OpenCurlyParenthesis);
        REQUIRE(tokens.at(5).getType() == TokenType::Name);
        REQUIRE(tokens.at(6).getType() == TokenType::Integer);
        REQUIRE(tokens.at(7).getType() == TokenType::Name);
        REQUIRE(tokens.at(8).getType() == TokenType::CloseCurlyParenthesis);
    }

    SECTION("Arithmetic test") {
        std::string input = "1+2-3*4/5%6";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();

        REQUIRE(tokens.size() == 11);

        REQUIRE(tokens.at(1).getType() == TokenType::ArithmeticOperator);
        REQUIRE(tokens.at(1).getValue() == "+");
        REQUIRE(tokens.at(3).getType() == TokenType::ArithmeticOperator);
        REQUIRE(tokens.at(3).getValue() == "-");
        REQUIRE(tokens.at(5).getType() == TokenType::ArithmeticOperator);
        REQUIRE(tokens.at(5).getValue() == "*");
        REQUIRE(tokens.at(7).getType() == TokenType::ArithmeticOperator);
        REQUIRE(tokens.at(7).getValue() == "/");
        REQUIRE(tokens.at(9).getType() == TokenType::ArithmeticOperator);
        REQUIRE(tokens.at(9).getValue() == "%");
    }

    SECTION("Conditional Not test") {
        std::string input = "!(var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(0).getType() == TokenType::ConditionalOperator);
        REQUIRE(tokens.at(0).getValue() == AppConstants::STRING_NOT);
        REQUIRE(tokens.at(1).getType() == TokenType::OpenRoundParenthesis);
    }

    SECTION("Conditional Not complex test") {
        std::string input = "! (var1) !    (var2) ! 1+2-3*4 ";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(0).getType() == TokenType::ConditionalOperator);
        REQUIRE(tokens.at(0).getValue() == AppConstants::STRING_NOT);
        REQUIRE(tokens.at(4).getType() == TokenType::ConditionalOperator);
        REQUIRE(tokens.at(4).getValue() == AppConstants::STRING_NOT);
        REQUIRE(tokens.at(8).getType() == TokenType::ConditionalOperator);
        REQUIRE(tokens.at(8).getValue() == AppConstants::STRING_NOT);
    }

    SECTION("Conditional And test") {
        std::string input = "(var2)&&(var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(3).getType() == TokenType::ConditionalOperator);
        REQUIRE(tokens.at(3).getValue() == AppConstants::STRING_AND);
    }

    SECTION("Conditional Or test") {
        std::string input = "(var2)||(var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(3).getType() == TokenType::ConditionalOperator);
        REQUIRE(tokens.at(3).getValue() == AppConstants::STRING_OR);
    }
}

TEST_CASE_METHOD(UnitTestFixture, "Relational operator test") {

    SECTION("Greater than test 1") {
        std::string input = "(var2 > var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(2).getType() == TokenType::RelationalOperator);
        REQUIRE(tokens.at(2).getValue() == AppConstants::STRING_GREATER_THAN);
    }

    SECTION("Greater than test 2") {
        std::string input = "(var2>var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(2).getType() == TokenType::RelationalOperator);
        REQUIRE(tokens.at(2).getValue() == AppConstants::STRING_GREATER_THAN);
    }

    SECTION("Less than test 1") {
        std::string input = "(var2 < var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(2).getType() == TokenType::RelationalOperator);
        REQUIRE(tokens.at(2).getValue() == AppConstants::STRING_LESS_THAN);
    }

    SECTION("Less than test 2") {
        std::string input = "(var2<var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(2).getType() == TokenType::RelationalOperator);
        REQUIRE(tokens.at(2).getValue() == AppConstants::STRING_LESS_THAN);
    }

    SECTION("Less than equal to test 1") {
        std::string input = "(var2 <= var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(2).getType() == TokenType::RelationalOperator);
        REQUIRE(tokens.at(2).getValue() == AppConstants::STRING_LESS_EQUAL);
    }

    SECTION("Less than equal to test 2") {
        std::string input = "(var2<=var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(2).getType() == TokenType::RelationalOperator);
        REQUIRE(tokens.at(2).getValue() == AppConstants::STRING_LESS_EQUAL);
    }

    SECTION("Greater than equal to test 1") {
        std::string input = "(var2 >= var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(2).getType() == TokenType::RelationalOperator);
        REQUIRE(tokens.at(2).getValue() == AppConstants::STRING_GREATER_EQUAL);
    }

    SECTION("Less than equal to test 2") {
        std::string input = "(var2>=var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(2).getType() == TokenType::RelationalOperator);
        REQUIRE(tokens.at(2).getValue() == AppConstants::STRING_GREATER_EQUAL);
    }

    SECTION("Complex Conditional") {
        std::string input = "((var2 * 5) >= var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(6).getType() == TokenType::RelationalOperator);
        REQUIRE(tokens.at(6).getValue() == AppConstants::STRING_GREATER_EQUAL);
    }

    SECTION("Equal") {
        std::string input = "(var2==var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(2).getType() == TokenType::RelationalOperator);
        REQUIRE(tokens.at(2).getValue() == AppConstants::STRING_DOUBLE_EQUAL);
    }

    SECTION("Not Equal") {
        std::string input = "(var2!=var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(2).getType() == TokenType::RelationalOperator);
        REQUIRE(tokens.at(2).getValue() == AppConstants::STRING_NOT_EQUAL);
    }
}

TEST_CASE_METHOD(UnitTestFixture, "Test invalid cases") {

    SECTION("Unexpected char") {
        std::string input = "~";
        SPTokenizer tokenizer(input);
        REQUIRE_THROWS_WITH(tokenizer.tokenize(), "Unexpected character found: ~");
    }
}