#pragma once

#include <string>
#include <memory>

enum class TokenType {
    // brackets
    Lparenthesis,
    Rparenthesis,

    // operators
    Plus,
    Minus,
    Asterisk,
    Slash,
    Percent,

    // others
    Semicolon,
    Comma,
    Quote,
    Underscore,

    // alphanumeric letter(s)
    Word,

    Empty,

};

class Token {
private:
    std::string rep;
    TokenType type;

public:
    explicit Token(const std::string& rep);
    std::string getRep();
    TokenType getType();
    bool isToken(const std::string& str);
    bool isToken(TokenType ttype);
    bool isDesignEntity();
    bool isInteger();
    bool isIdent();
    bool isOperand();
    bool isOperator();
    bool precedes(const std::shared_ptr<Token> other);
};
