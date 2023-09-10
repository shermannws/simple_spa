
#include "QPS/Tokenizer.h"

#include "catch.hpp"

// TODO: CREATE A MORE COMPREHENSIVE TEST SUITE

TEST_CASE("Tokenizer Test") {

    SECTION("Valid query") {
        Tokenizer tokenizer("stmt s;\nSelect s such that Follows*(2,3)");
        REQUIRE(tokenizer.getCurr() == 0);

        REQUIRE(tokenizer.peekToken()->getRep() == "stmt");
        REQUIRE(tokenizer.peekToken()->getType() == TokenType::Word);
        REQUIRE(tokenizer.getCurr() == 0);
        REQUIRE(tokenizer.popToken()->getRep() == "stmt");

        REQUIRE(tokenizer.getCurr() == 4);

        REQUIRE(tokenizer.peekChar() == 32); // space after stmt
        REQUIRE(tokenizer.popToken()->getRep() == "s");

        REQUIRE(tokenizer.popChar() == 59); // pop ";" in int
        tokenizer.popString();

        REQUIRE(tokenizer.peekString() == "S");
        REQUIRE(tokenizer.peekString() == "S");
        REQUIRE(tokenizer.popToken()->getRep() == "Select");
        REQUIRE(tokenizer.popToken()->getRep() == "s");
        REQUIRE_FALSE(tokenizer.peekToken()->getRep() == "s");

        REQUIRE(tokenizer.popToken()->getRep() == "such that");

        REQUIRE(tokenizer.popToken()->getRep() == "Follows*");
        std::shared_ptr<Token> t = tokenizer.popToken();
        REQUIRE(t->getRep() == "(");
        REQUIRE(t->getType() == TokenType::Lparenthesis);
        REQUIRE(tokenizer.popToken()->getRep() == "2");
        REQUIRE(tokenizer.popToken()->getRep() == ",");
        REQUIRE(tokenizer.popToken()->getRep() == "3");
        REQUIRE(tokenizer.popToken()->getRep() == ")");
        REQUIRE(tokenizer.getCurr() == 40);
        REQUIRE(tokenizer.popToken()->getType() == TokenType::Empty);
        REQUIRE_FALSE(tokenizer.isCurrValid());
    }

    SECTION("Valid query with such synonym") {
        Tokenizer tokenizer("stmt such; Select such such that Uses(1, such)");
        REQUIRE(tokenizer.popToken()->getRep() == "stmt");
        REQUIRE(tokenizer.popToken()->getRep() == "such");
        REQUIRE(tokenizer.popToken()->getRep() == ";");
        REQUIRE(tokenizer.popToken()->getRep() == "Select");
        REQUIRE(tokenizer.popToken()->getRep() == "such");
        REQUIRE(tokenizer.popToken()->getRep() == "such that");
        REQUIRE(tokenizer.popToken()->getRep() == "Uses");
        REQUIRE(tokenizer.popToken()->getRep() == "(");
        REQUIRE(tokenizer.popToken()->getRep() == "1");
        REQUIRE(tokenizer.popToken()->getRep() == ",");
        REQUIRE(tokenizer.popToken()->getRep() == "such");
        REQUIRE(tokenizer.popToken()->getRep() == ")");
        REQUIRE(tokenizer.popToken()->getType() == TokenType::Empty);
    }

    SECTION("Invalid tokens") {
        Tokenizer tokenizer("follows * follows* Follows *");
        REQUIRE_FALSE(tokenizer.popToken()->getRep() == "follows*");
        tokenizer.popToken();
        REQUIRE_FALSE(tokenizer.popToken()->getRep() == "follows*");
        REQUIRE_FALSE(tokenizer.popToken()->getRep() == "Follows*");
        REQUIRE_FALSE(tokenizer.popToken()->getType() == TokenType::Empty);
    }

    SECTION("test trailing whitespaces") {
        Tokenizer tokenizer(" \n Parent* \n     ");
        REQUIRE(tokenizer.popToken()->getRep() == "Parent*");
        REQUIRE(tokenizer.popToken()->getType() == TokenType::Empty);
    }

    SECTION("test specials") {
        Tokenizer tokenizer("\"specials ();,_+-*/% \"");

        std::shared_ptr<Token> t = tokenizer.popToken();
        REQUIRE(t->getRep() == "\"");
        REQUIRE(t->getType() == TokenType::Quote);

        REQUIRE(tokenizer.popToken()->getRep() == "specials");

        t = tokenizer.popToken();
        REQUIRE(t->getRep() == "(");
        REQUIRE(t->getType() == TokenType::Lparenthesis);

        t = tokenizer.popToken();
        REQUIRE(t->getRep() == ")");
        REQUIRE(t->getType() == TokenType::Rparenthesis);

        t = tokenizer.popToken();
        REQUIRE(t->getRep() == ";");
        REQUIRE(t->getType() == TokenType::Semicolon);

        t = tokenizer.popToken();
        REQUIRE(t->getRep() == ",");
        REQUIRE(t->getType() == TokenType::Comma);

        t = tokenizer.popToken();
        REQUIRE(t->getRep() == "_");
        REQUIRE(t->getType() == TokenType::Underscore);

        t = tokenizer.popToken();
        REQUIRE(t->getRep() == "+");
        REQUIRE(t->getType() == TokenType::Plus);

        t = tokenizer.popToken();
        REQUIRE(t->getRep() == "-");
        REQUIRE(t->getType() == TokenType::Minus);

        t = tokenizer.popToken();
        REQUIRE(t->getRep() == "*");
        REQUIRE(t->getType() == TokenType::Asterisk);

        t = tokenizer.popToken();
        REQUIRE(t->getRep() == "/");
        REQUIRE(t->getType() == TokenType::Slash);

        t = tokenizer.popToken();
        REQUIRE(t->getRep() == "%");
        REQUIRE(t->getType() == TokenType::Percent);

        REQUIRE(tokenizer.popToken()->getRep() == "\"");
        REQUIRE(tokenizer.popToken()->getType() == TokenType::Empty);
    }

}


