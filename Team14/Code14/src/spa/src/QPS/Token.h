#pragma once

#include <string>

enum class TokenType {
    // brackets
    LPARENTHESIS,
    RPARENTHESIS,

    // operators
    PLUS,
    MINUS,
    ASTERISK,
    SLASH,
    PERCENT,

    // others
    SEMICOLON,
    COMMA,
    QUOTE,
    UNDERSCORE,

    // alphanumeric letter(s)
    WORD,

    EMPTY,

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
    bool isSelectToken();
    bool isSuchThatToken();
    bool isPatternToken();
    bool isDesignEntity();
    bool isIdent();
};
