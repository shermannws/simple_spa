
#include "QPS/Tokenizer.h"

#include "catch.hpp"

TEST_CASE("Tokenizer Test") {
    Tokenizer tokenizer("stmt s; Select s such that Follows(2,3)");
    std::vector<std::string> res;
    REQUIRE(tokenizer.peek_token() == "stmt");
    REQUIRE(tokenizer.pop_token() == "stmt");
    REQUIRE(tokenizer.pop_token() == "s");
    REQUIRE(tokenizer.peek_token() != "s");
    REQUIRE(tokenizer.pop_token() == ";");
    REQUIRE(tokenizer.pop_token() == "Select");
    REQUIRE(tokenizer.pop_token() == "s");
    REQUIRE(tokenizer.pop_token() == "such");
    REQUIRE(tokenizer.pop_token() == "that");
    REQUIRE(tokenizer.pop_token() == "Follows");
    REQUIRE(tokenizer.pop_token() == "(");
    REQUIRE(tokenizer.pop_token() == "2");
    REQUIRE(tokenizer.pop_token() == ",");
    REQUIRE(tokenizer.pop_token() == "3");
    REQUIRE(tokenizer.pop_token() == ")");
}


