
#include "QPS/Tokenizer.h"

#include "catch.hpp"

std::string input{"stmt s;\nSelect s such that Follows*(2,3)"};

TEST_CASE("Tokenizer Test") {
    Tokenizer tokenizer(input);
    REQUIRE(tokenizer.get_curr() == 0);

    REQUIRE(tokenizer.peek_token()->get_rep() == "stmt");
    REQUIRE(tokenizer.peek_token()->get_type() == TokenType::Word);
    REQUIRE(tokenizer.get_curr() == 0);
    REQUIRE(tokenizer.pop_token()->get_rep() == "stmt");

    REQUIRE(tokenizer.get_curr() == 4);

    REQUIRE(tokenizer.peek_char() == 32); // space after stmt
    REQUIRE(tokenizer.pop_token()->get_rep() == "s");

    REQUIRE(tokenizer.pop_char() == 59); // pop ";" in int
    tokenizer.pop_string();

    REQUIRE(tokenizer.peek_string() == "S");
    REQUIRE(tokenizer.peek_string() == "S");
    REQUIRE(tokenizer.pop_token()->get_rep() == "Select");
    REQUIRE(tokenizer.pop_token()->get_rep() == "s");
    REQUIRE_FALSE(tokenizer.peek_token()->get_rep() == "s");

    REQUIRE(tokenizer.pop_token()->get_rep() == "such");
    REQUIRE(tokenizer.pop_token()->get_rep() == "that");

    REQUIRE(tokenizer.pop_token()->get_rep() == "Follows*");
    std::shared_ptr<Token> t = tokenizer.pop_token();
    REQUIRE(t->get_rep() == "(");
    REQUIRE(t->get_type() == TokenType::LParenthesis);
    REQUIRE(tokenizer.pop_token()->get_rep() == "2");
    REQUIRE(tokenizer.pop_token()->get_rep() == ",");
    REQUIRE(tokenizer.pop_token()->get_rep() == "3");
    REQUIRE(tokenizer.pop_token()->get_rep() == ")");
    REQUIRE(tokenizer.get_curr() == input.size());
    REQUIRE_FALSE(tokenizer.is_curr_valid());
}


