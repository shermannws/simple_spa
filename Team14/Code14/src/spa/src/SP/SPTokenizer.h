#pragma once

#include <string>
#include <vector>

#include "SPTokenType.h"
#include "SPToken.h"

class SPTokenizer {
public:
    explicit SPTokenizer(std::string  input);
    std::vector<SPToken> tokenize();
private:
    int curr;
    std::string input;
    std::vector<SPToken> tokens;

    void tokenizeName();
    void tokenizeInteger();
    void tokenizeParenthesis();
    void tokenizeSemicolon();
    void tokenizeEquals();
    void tokenizeArithmeticOperator();
    void tokenizeConditionalOperator();
    void tokenizeRelationalOperator();
    void tokenizeNot();

    int peekChar();
    int popChar();
    bool isCurrValid();
    int peekNextChar();
};