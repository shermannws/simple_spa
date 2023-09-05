#include "Tokenizer.h"
#include "Token.h"

#include <string>

std::vector<std::string> specials{"(",")",";",",","_","+","-","*","/","%"};
std::vector<std::string> stars{"Follows", "Parent"};

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


std::shared_ptr<Token> Tokenizer::pop_token() {
    std::string res;

    if (!is_curr_valid()) {
        throw std::runtime_error("No more token");
    }

    // skip if whitespace
    while (isspace(peek_char())) {
        pop_char();
    }

    // one-character token
    auto it = std::find(specials.begin(), specials.end(), peek_string());
    if (it != specials.end()) {
        return std::make_shared<Token>(pop_string());
    }

    if (isalnum(peek_char())) {
        res += pop_string();

        // note: Parent* and Follows* will turn into two tokens
        while (is_curr_valid() && isalnum(peek_char())) {
            res += pop_string();
        }

        if (is_curr_valid() && peek_string() == "*") {
            std::string temp = peek_string();
            auto it_star = std::find(stars.begin(), stars.end(), res);
            if (it_star != stars.end()) {
                res += pop_string();
            }
        }

        return std::make_shared<Token>(res);
    }
    throw std::runtime_error("Invalid token");
}

std::shared_ptr<Token> Tokenizer::peek_token() {
    int tmp = curr;
    std::shared_ptr<Token> res = pop_token();
    curr = tmp;
    return res;
}

bool Tokenizer::is_curr_valid() {
    return curr >=0 and curr < (int)input.size();
}

int Tokenizer::get_curr() const {
    return curr;
}
