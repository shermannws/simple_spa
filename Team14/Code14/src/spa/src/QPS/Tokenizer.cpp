#include "Tokenizer.h"

#include <string>


Tokenizer::Tokenizer(const std::string& input): curr(0) {
    this->input = input;
}

int Tokenizer::peek_char() {
    if (!is_curr_valid()) {
        throw std::runtime_error("No more char");
    }

    return input[curr];
}

int Tokenizer::pop_char() {
    int res = peek_char();
    curr += 1;
    return res;
}

std::string Tokenizer::peek_string() {
    if (!is_curr_valid()) {
        throw std::runtime_error("No more string");
    }
    std::string res;
    res += input[curr];
    return res;
}

std::string Tokenizer::pop_string() {
    std::string res = peek_string();
    curr += 1;
    return res;
}


std::string Tokenizer::pop_token() {
    std::string res;

    if (!is_curr_valid()) {
        return "";
    }

    // skip if whitespace
    while (isspace(peek_char())) {
        pop_char();
    }

    // one-character token
    std::vector<std::string> specials{"(",")",";",",","_","+","-","*","/","%"};
    auto it = std::find(specials.begin(), specials.end(), peek_string());
    if (it != specials.end()) {
        return pop_string();
    }

    if (isalnum(peek_char())) {
        res += pop_string();

        // note: Parent* and Follows* will turn into two tokens
        while (is_curr_valid() && isalnum(peek_char())) {
            res += pop_string();
        }
        return res;
    }
    throw std::runtime_error("Invalid token");
}

std::string Tokenizer::peek_token() {
    int tmp = curr;
    std::string res = pop_token();
    curr = tmp;
    return res;
}

bool Tokenizer::is_curr_valid() {
    return curr <= (int)input.size();
}
