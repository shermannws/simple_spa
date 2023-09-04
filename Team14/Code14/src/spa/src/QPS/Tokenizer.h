#ifndef SPA_TOKENIZER_H
#define SPA_TOKENIZER_H

#include <string>

class Tokenizer {
public:
    explicit Tokenizer(const std::string& input);
    int peek_char();
    int pop_char();
    std::string peek_string();
    std::string pop_string();
    std::string peek_token();
    std::string pop_token();
    bool is_curr_valid();

private:
    int curr;
    std::string input;
};


#endif //SPA_TOKENIZER_H
