#pragma once

#include <string>
#include <vector>
#include "SPTokenType.h"
#include "SPToken.h"

class SPTokenizer {
public:
    SPTokenizer(const std::string& input);
    std::vector<SPToken> tokenize();
private:
    int curr;
    std::string input;
    std::vector<SPToken> tokens;

    void tokenizeName();
    void tokenizeInteger();
    void tokenizeParantheses();
    void tokenizeSemicolon();
    void tokenizeEquals();
    void tokenizeArithmeticOperator();

    int peekChar();
    int popChar();
    bool isCurrValid();
};