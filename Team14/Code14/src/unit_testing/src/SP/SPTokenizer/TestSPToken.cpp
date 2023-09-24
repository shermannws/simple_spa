
#include "SP/SPToken.h"

#include "catch.hpp"

TEST_CASE("SPToken Test") {
    INFO("Test case start");
    SPToken testToken(TokenType::OpenRoundParenthesis, "(");
    REQUIRE(testToken.getValue() == "(");
    REQUIRE(testToken.getType() == TokenType::OpenRoundParenthesis);
}
