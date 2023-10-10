#pragma once

#include <string>
#include <memory>

/**
 * @brief The enum class of TokenType
 */
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
    Dot,

    // alphanumeric letter(s)
    Word,

    Empty,

};

/**
 * @brief Token class
 */
class Token {
private:
    /**
     * @brief The string representation of the token
     */
    std::string rep;

    /**
     * @brief The type of token
     */
    TokenType type;

public:
    /**
     * @brief The constructor of Token
     * @param rep The string representation of the Token
     */
    explicit Token(const std::string& rep);

    /**
     * @brief Returns the string representation of the Token
     * @return The string representation of the Token
     */
    std::string getRep();

    /**
     * @brief Returns the TokenType of the Token
     * @return The TokenType of the Token
     */
    TokenType getType();

    /**
     * @brief Checks if the token is of TokenType::Word and has a string representation equal to str
     * @param str The expected string
     * @return The result of the check in boolean
     */
    bool isToken(const std::string& str);

    /**
     * @brief Checks if the token is of TokenType ttype
     * @param ttype The expected TokenType
     * @return The result of the check in boolean
     */
    bool isToken(TokenType ttype);

    /**
     * @brief Checks if the token is of TokenType::Word and the string representation is of design-entity
     * @return The result of the check in boolean
     */
    bool isDesignEntity();

    /**
     * @brief Checks if the string representation matches the pattern of an INTEGER
     * @return The result of the check in boolean
     */
    bool isInteger();

    /**
     * @brief Checks if the string representation matches the pattern of an IDENT
     * @return The result of the check in boolean
     */
    bool isIdent();

    /**
     * @brief Checks if the string representation matches the pattern of an operand
     * @return The result of the check in boolean
     */
    bool isOperand();

    /**
     * @brief Checks if the TokenType of the Token matches that of an operator
     * @return The result of the check in boolean
     */
    bool isOperator();

    /**
     * @brief Checks if this Token precedes the other Token
     * @param other The Token to be compared
     * @return The result of the check in boolean
     */
    bool precedes(const std::shared_ptr<Token> other);
};
