#pragma once

#include <string>
#include <vector>
#include <stdexcept>

#include "Tokenizer.h"
#include "Token.h"


std::vector<std::string> specials{"(",")",";",",","_","+","-","*","/","%"};
std::vector<std::string> stars{"Follows", "Parent"};

Tokenizer::Tokenizer(const std::string& input) : curr(0) {
    this->input = input;
}

int Tokenizer::peekChar() {
    if (!isCurrValid()) {
        throw std::runtime_error("No more char");
    }

    return input[curr];
}

int Tokenizer::popChar() {
    int res = peekChar();
    curr += 1;
    return res;
}

std::string Tokenizer::peekString() {
    if (!isCurrValid()) {
        throw std::runtime_error("No more string");
    }
    std::string res;
    res += input[curr];
    return res;
}

std::string Tokenizer::popString() {
    std::string res = peekString();
    curr += 1;
    return res;
}

std::shared_ptr<Token> Tokenizer::popToken() {
    std::string res;

    if (!isCurrValid()) {
        return std::make_shared<Token>("");
    }

    // skip if whitespace
    while (isspace(peekChar())) {
        popChar();
    }

    // one-character token
    auto it = std::find(specials.begin(), specials.end(), peekString());
    if (it != specials.end()) {
        return std::make_shared<Token>(popString());
    }

    if (isalnum(peekChar())) {
        res += popString();

        while (isCurrValid() && isalnum(peekChar())) {
            res += popString();
        }

        // handle star abstraction as one token
        if (isCurrValid() && peekString() == "*") {
            std::string temp = peekString();
            auto it_star = std::find(stars.begin(), stars.end(), res);
            if (it_star != stars.end()) {
                res += popString();
            }
        }

        // handle such that as one token
        if (isCurrValid() && res == "such" && peekToken()->getRep() == "that") {
            res += " that";
            popToken();
        }

        return std::make_shared<Token>(res);
    }
    throw std::runtime_error("Invalid token");
}

std::shared_ptr<Token> Tokenizer::peekToken() {
    int tmp = curr;
    std::shared_ptr<Token> res = popToken();
    curr = tmp;
    return res;
}

bool Tokenizer::isCurrValid() {
    return curr >=0 && curr < (int)input.size();
}

int Tokenizer::getCurr() const {
    return curr;
}
