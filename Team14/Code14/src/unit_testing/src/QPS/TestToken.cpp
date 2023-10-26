#include "../TestingUtilities/TestFixture/UnitTestFixture.h"
#include "QPS/Parsers/Token.h"

#include "catch.hpp"

TEST_CASE_METHOD(UnitTestFixture, "Token isInteger Test") {
    std::shared_ptr<Token> integer_token = std::make_shared<Token>("54");
    std::shared_ptr<Token> invalid_token = std::make_shared<Token>("012");
    std::shared_ptr<Token> zero_token = std::make_shared<Token>("0");
    std::shared_ptr<Token> invalid_zero_token = std::make_shared<Token>("00");

    REQUIRE(integer_token->isInteger());
    REQUIRE_FALSE(invalid_token->isInteger());
    REQUIRE(zero_token->isInteger());
    REQUIRE_FALSE(invalid_zero_token->isInteger());
}

TEST_CASE_METHOD(UnitTestFixture, "Token isIdent Test") {
    // IDENT : LETTER ( LETTER | DIGIT )*
    std::shared_ptr<Token> all_alpha = std::make_shared<Token>("Follows");
    std::shared_ptr<Token> one_letter = std::make_shared<Token>("x");
    std::shared_ptr<Token> letter_digit = std::make_shared<Token>("y6");
    std::shared_ptr<Token> non_alphanum = std::make_shared<Token>("Follows*");
    std::shared_ptr<Token> digit_letter = std::make_shared<Token>("1a");
    std::shared_ptr<Token> all_num = std::make_shared<Token>("54");

    REQUIRE(all_alpha->isIdent());
    REQUIRE(one_letter->isIdent());
    REQUIRE(letter_digit->isIdent());
    REQUIRE_FALSE(non_alphanum->isIdent());
    REQUIRE_FALSE(digit_letter->isIdent());
    REQUIRE_FALSE(all_num->isIdent());
}