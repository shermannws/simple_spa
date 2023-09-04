
#include "QPS/Tokenizer.h"

#include "catch.hpp"

std::string input = "stmt s; Select s such that Follows(2,3)";

TEST_CASE("Tokenizer Test") {
    Tokenizer tokenizer(input);
    REQUIRE(tokenizer.get_curr() == 0);

    REQUIRE(tokenizer.peek_token() == "stmt");
    REQUIRE(tokenizer.get_curr() == 0);
    REQUIRE(tokenizer.pop_token() == "stmt");

    REQUIRE(tokenizer.get_curr() == 4);

    REQUIRE(tokenizer.peek_char() == 32); // space after stmt
    REQUIRE(tokenizer.pop_token() == "s");

    REQUIRE(tokenizer.pop_char() == 59); // pop ";" in int

    REQUIRE(tokenizer.pop_string() == " ");

    REQUIRE(tokenizer.peek_string() == "S");
    REQUIRE(tokenizer.peek_string() == "S");
    REQUIRE(tokenizer.pop_token() == "Select");
    REQUIRE(tokenizer.pop_token() == "s");
    REQUIRE_FALSE(tokenizer.peek_token() == "s");

    REQUIRE(tokenizer.pop_token() == "such");
    REQUIRE(tokenizer.pop_token() == "that");
    REQUIRE(tokenizer.pop_token() == "Follows");
    REQUIRE(tokenizer.pop_token() == "(");
    REQUIRE(tokenizer.pop_token() == "2");
    REQUIRE(tokenizer.pop_token() == ",");
    REQUIRE(tokenizer.pop_token() == "3");
    REQUIRE(tokenizer.pop_token() == ")");
    REQUIRE(tokenizer.get_curr() == input.size());
    REQUIRE_FALSE(tokenizer.is_curr_valid());
}


