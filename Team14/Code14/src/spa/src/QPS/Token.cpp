#include "Token.h"

#include <string>

Token::Token(const std::string& input) {
    // set type
    this->rep = input;
    if (rep == "(") {
        this->type = TokenType::LParenthesis;
    } else if (rep == ")") {
        this->type = TokenType::RParenthesis;
    } else if (rep == "+") {
        this->type = TokenType::Plus;
    } else if (rep == "-") {
        this->type = TokenType::Minus;
    } else if (rep == "*") {
        this->type = TokenType::Asterisk;
    } else if (rep == "/") {
        this->type = TokenType::Slash;
    } else if (rep == "%") {
        this->type = TokenType::Percent;
    } else if (rep == ";") {
        this->type = TokenType::Semicolon;
    } else if (rep == ",") {
        this->type = TokenType::Comma;
    } else if (rep == "\"") {
        this->type = TokenType::Quote;
    } else if (rep == "_") {
        this->type = TokenType::Underscore;
    } else {
        this->type = TokenType::Word;
    }
}

std::string Token::get_rep() {
    return rep;
}

TokenType Token::get_type() {
    return type;
}