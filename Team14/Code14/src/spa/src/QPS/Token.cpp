#include "Token.h"

#include <string>

Token::Token(const std::string& input) {
    this->rep = input;
    if (rep == "(") {
        this->type = TokenType::LPARENTHESIS;
    } else if (rep == ")") {
        this->type = TokenType::RPARENTHESIS;
    } else if (rep == "+") {
        this->type = TokenType::PLUS;
    } else if (rep == "-") {
        this->type = TokenType::MINUS;
    } else if (rep == "*") {
        this->type = TokenType::ASTERISK;
    } else if (rep == "/") {
        this->type = TokenType::SLASH;
    } else if (rep == "%") {
        this->type = TokenType::PERCENT;
    } else if (rep == ";") {
        this->type = TokenType::SEMICOLON;
    } else if (rep == ",") {
        this->type = TokenType::COMMA;
    } else if (rep == "\"") {
        this->type = TokenType::QUOTE;
    } else if (rep == "_") {
        this->type = TokenType::UNDERSCORE;
    } else if (!rep.empty()){
        this->type = TokenType::WORD;
    } else {
        this->type = TokenType::EMPTY;
    }
}

std::string Token::getRep() {
    return rep;
}

TokenType Token::getType() {
    return type;
}
