
#include "QPS/Tokenizer.h"

#include "catch.hpp"

std::string input{"stmt s;\nSelect s such that Follows*(2,3)"};

// TODO: CREATE A MORE COMPREHENSIVE TEST SUITE

TEST_CASE("Tokenizer Test") {
    Tokenizer tokenizer(input);
    REQUIRE(tokenizer.getCurr() == 0);

    REQUIRE(tokenizer.peekToken()->get_rep() == "stmt");
    REQUIRE(tokenizer.peekToken()->get_type() == TokenType::WORD);
    REQUIRE(tokenizer.getCurr() == 0);
    REQUIRE(tokenizer.popToken()->get_rep() == "stmt");

    REQUIRE(tokenizer.getCurr() == 4);

    REQUIRE(tokenizer.peekChar() == 32); // space after stmt
    REQUIRE(tokenizer.popToken()->get_rep() == "s");

    REQUIRE(tokenizer.popChar() == 59); // pop ";" in int
    tokenizer.popString();

    REQUIRE(tokenizer.peekString() == "S");
    REQUIRE(tokenizer.peekString() == "S");
    REQUIRE(tokenizer.popToken()->get_rep() == "Select");
    REQUIRE(tokenizer.popToken()->get_rep() == "s");
    REQUIRE_FALSE(tokenizer.peekToken()->get_rep() == "s");

    REQUIRE(tokenizer.popToken()->get_rep() == "such");
    REQUIRE(tokenizer.popToken()->get_rep() == "that");

    REQUIRE(tokenizer.popToken()->get_rep() == "Follows*");
    std::shared_ptr<Token> t = tokenizer.popToken();
    REQUIRE(t->get_rep() == "(");
    REQUIRE(t->get_type() == TokenType::LPARENTHESIS);
    REQUIRE(tokenizer.popToken()->get_rep() == "2");
    REQUIRE(tokenizer.popToken()->get_rep() == ",");
    REQUIRE(tokenizer.popToken()->get_rep() == "3");
    REQUIRE(tokenizer.popToken()->get_rep() == ")");
    REQUIRE(tokenizer.getCurr() == 40);
    REQUIRE_FALSE(tokenizer.isCurrValid());
}


