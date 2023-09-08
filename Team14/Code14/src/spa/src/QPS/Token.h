#ifndef SPA_TOKEN_H
#define SPA_TOKEN_H

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

};

class Token {
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
private:
    std::string rep;
    TokenType type;
};


#endif //SPA_TOKEN_H
