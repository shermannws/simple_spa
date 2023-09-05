#ifndef SPA_TOKEN_H
#define SPA_TOKEN_H

#include <string>

enum class TokenType {
    // brackets
    LParenthesis,
    RParenthesis,

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

};

class Token {
public:
    Token(const std::string& rep);
    std::string get_rep();
    TokenType get_type();
private:
    std::string rep;
    TokenType type;
};


#endif //SPA_TOKEN_H
