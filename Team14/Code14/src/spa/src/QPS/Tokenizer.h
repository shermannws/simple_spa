#ifndef SPA_TOKENIZER_H
#define SPA_TOKENIZER_H

#include <string>
#include "Token.h"

class Tokenizer {
public:
    explicit Tokenizer(const std::string& input);
    int peek_char();
    int pop_char();
    std::string peek_string();
    std::string pop_string();
    std::shared_ptr<Token> peek_token();
    std::shared_ptr<Token> pop_token();
    bool is_curr_valid();
    int get_curr() const;

private:
    int curr;
    std::string input;
};


#endif //SPA_TOKENIZER_H
