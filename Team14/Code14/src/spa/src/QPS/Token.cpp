#include "Token.h"

#include <string>
#include <regex>

Token::Token(const std::string& input) {
    this->rep = input;
    if (rep == "(") {
        this->type = TokenType::Lparenthesis;
    } else if (rep == ")") {
        this->type = TokenType::Rparenthesis;
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
    } else if (!rep.empty()){
        this->type = TokenType::Word;
    } else {
        this->type = TokenType::Empty;
    }
}

std::string Token::getRep() {
    return rep;
}

TokenType Token::getType() {
    return type;
}

bool Token::isToken(const std::string& str) {
    return rep == str && type == TokenType::Word;
}

bool Token::isToken(TokenType ttype) {
    return type == ttype;
}

bool Token::isDesignEntity() {
    if (type ==TokenType::Word && (rep == "procedure" || rep == "stmt" || rep == "read" || rep == "print" ||
    rep == "assign" || rep == "call" || rep == "while" || rep == "if" || rep == "variable" || rep == "constant")
    ) {
        return true;
    }
    return false;
}

bool Token::isIdent() {
    std::regex pattern("[a-zA-Z][a-zA-Z0-9]*");
    return std::regex_match(rep, pattern);
}

bool Token::isInteger() {
    std::regex pattern("^(0|[1-9]\\d*)$");
    return std::regex_match(rep, pattern);
}
