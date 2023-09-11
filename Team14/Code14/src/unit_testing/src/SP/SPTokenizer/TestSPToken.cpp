
#include "SP/SPToken.h"

#include "catch.hpp"

TEST_CASE("SPToken Test") {
    INFO("Test case start");
    SPToken testToken(OPEN_CURLY_PARAN, "(");
    REQUIRE(testToken.getValue() == "(");
    REQUIRE(testToken.getType() == TokenType::OPEN_CURLY_PARAN);
}
