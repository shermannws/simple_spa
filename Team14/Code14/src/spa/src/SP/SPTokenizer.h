//
#ifndef SPA_SPTOKENIZER_H
#define SPA_SPTOKENIZER_H

#include <string>
#include <vector>
#include "SPTokenType.h"
#include "SPToken.h"

class SPTokenizer {
public:
    std::vector<SPToken> tokenize(const std::string& input);
private:
    int curr;
    std::string input;

    SPToken tokenizeName(const std::string& input);
    SPToken tokenizeInteger(const std::string& input);
    SPToken tokenizeParantheses(char);
    SPToken tokenizeSemicolon(char);
    SPToken tokenizeEquals(char);
    SPToken tokenizeArithmeticOperator(char);

    int peekChar();
    int popChar();
    std::string peekString();
    std::string popString();
};


#endif //SPA_SPTOKENIZER_H
