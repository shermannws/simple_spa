#pragma once

#include <string>
#include "Token.h"

class Tokenizer {
private:
    int curr;
    std::string input;

public:
    explicit Tokenizer(const std::string& input);
    int peekChar();
    int popChar();
    std::string peekString();
    std::string popString();
    std::shared_ptr<Token> peekToken();
    std::shared_ptr<Token> popToken();
    bool isCurrValid();
    int getCurr() const;
};
