#pragma once

#include <string>
#include <memory>

#include "Token.h"

/*
 * @brief Tokenizer class
 */
class Tokenizer {
private:
    /*
     * @brief The index of the current pointer
     */
    int curr;

    /*
     * The input to the Tokenizer in string
     */
    std::string input;

public:
    /*
     * @brief The constructor of Tokenizer
     * @param input The input string
     */
    explicit Tokenizer(const std::string& input);

    /*
     * @brief Peeks the next Char
     * @return The integer representation of the next Char
     */
    int peekChar();

    /*
     * @brief Pops the next Char
     * @return The integer representation of the next Char
     */
    int popChar();

    /*
     * @brief Peeks the next string in the tokenizer
     * @return The next string
     */
    std::string peekString();

    /*
     * @brief Pops the next string in the tokenizer
     * @return The next string
     */
    std::string popString();

    /*
     * @brief Peeks the next Token
     * @return The shared pointer of the next Token
     */
    std::shared_ptr<Token> peekToken();

    /*
     * @brief Pops the next Token
     * @return The shared pointer of the next Token
     */
    std::shared_ptr<Token> popToken();

    /*
     * @brief Checks if the current pointer of the tokenizer is valid
     * @return The result of the check in boolean
     */
    bool isCurrValid();

    /*
     * @brief Gets the current index of the pointer
     * @return The integer representation of the current index
     */
    int getCurr() const;
};
