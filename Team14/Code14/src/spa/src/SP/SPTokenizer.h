#pragma once

#include <string>
#include <vector>
#include <utility>
#include <stdexcept>

#include "Commons/AppConstants.h"
#include "SPTokenType.h"
#include "SPToken.h"

/**
 * An SP subcomponent to tokenize the input SIMPLE source program string.
 */
class SPTokenizer {
private:
    /**
     * A counter to keep track of the current char in the input.
     */
    int curr;

    /**
     * Input string of SIMPLE source code.
     */
    std::string input;

    /**
     * Output tokens to return.
     */
    std::vector<SPToken> tokens;

    /**
     * Checks the input string for next chars to create an Name token,
     * which starts with alphabet followed by alphanumeric chars.
     */
    void tokenizeName();

    /**
     * Checks the input string for next chars to create an Integer token,
     * which is a series of digits.
     */
    void tokenizeInteger();

    /**
     * Takes the next char in the input string to create various Parenthesis tokens.
     */
    void tokenizeParenthesis();

    /**
     * Takes the next char in the input string to create a Semicolon token.
     */
    void tokenizeSemicolon();

    /**
     * Takes the next char in the input string to create an Equals token or
     * calls tokenizeRelationalOperator() for possible '==' input.
     */
    void tokenizeEquals();

    /**
     * Takes the next char in the input string to create a ArithmeticOperator token.
     */
    void tokenizeArithmeticOperator();

    /**
     * Takes in the next char/chars in the input string to create a ConditionalOperator token.
     */
    void tokenizeConditionalOperator();

    /**
     * Takes in the next char/chars in the input string to create a RelationalOperator token.
     */
    void tokenizeRelationalOperator();

    /**
     * Checks the next char and calls either tokenizeRelationalOperator() or tokenizeConditionalOperator().
     */
    void tokenizeNot();

    /**
     * Checks the current char in the string input without incrementing the counter.
     * @return The character as an int
     */
    int peekChar();

    /**
     * Increments the counter to go to the next char in the string input.
     * @return The current character the counter is at as an int
     */
    int popChar();

    /**
     * Checks if the counter is pointing to a valid char in the string input.
     * @return true or false
     */
    bool isCurrValid();

    /**
     * Checks the next char in the string input without incrementing the counter.
     * @return
     */
    int peekNextChar();

public:
    /**
     * Creates and initialises a SPTokenizer.
     * @param input String of the simple source program to be tokenized
     */
    explicit SPTokenizer(std::string input);

    /**
     * Tokenizes the string input source program by checking each char and creating tokens,
     * serving as the entry point to the rest of the tokenizer.
     * @return
     */
    std::vector<SPToken> tokenize();
};