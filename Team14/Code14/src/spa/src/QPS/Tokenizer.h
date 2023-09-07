#ifndef SPA_TOKENIZER_H
#define SPA_TOKENIZER_H

#include <string>
#include "Token.h"

class Tokenizer {
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

private:
    int curr;
    std::string input;
};


#endif //SPA_TOKENIZER_H
