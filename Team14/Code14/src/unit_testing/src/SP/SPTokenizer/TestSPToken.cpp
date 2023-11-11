
#include "../../TestingUtilities/TestFixture/UnitTestFixture.h"
#include "SP/SPToken.h"
#include "catch.hpp"

TEST_CASE_METHOD(UnitTestFixture, "SPToken Test") {
    INFO("Test case start");
    SPToken testToken(TokenType::OpenRoundParenthesis, "(");
    REQUIRE(testToken.getValue() == "(");
    REQUIRE(testToken.getType() == TokenType::OpenRoundParenthesis);
}
