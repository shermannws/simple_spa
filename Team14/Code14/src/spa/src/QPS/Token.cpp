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
    } else {
        this->type = TokenType::WORD;
    }
}

std::string Token::getRep() {
    return rep;
}

TokenType Token::getType() {
    return type;
}

bool Token::isToken(const std::string& str) {
    return rep == str && type == TokenType::WORD;
}

bool Token::isToken(TokenType ttype) {
    return type == ttype;
}

bool Token::isSelectToken() {
    return rep == "Select" && type==TokenType::WORD;
}

bool Token::isSuchThatToken() {
    return rep == "such that" && type==TokenType::WORD;;
}

bool Token::isPatternToken() {
    return rep == "pattern" && type==TokenType::WORD;
}

bool Token::isDesignEntity() {
    if (type ==TokenType::WORD && (rep == "procedure" || rep == "stmt" || rep == "read" || rep == "print" ||
    rep == "assign" || rep == "call" || rep == "while" || rep == "if" || rep == "variable" || rep == "constant")
    ) {
        return true;
    }
    return false;
}

