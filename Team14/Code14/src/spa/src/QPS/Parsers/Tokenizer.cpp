#include <stdexcept>
#include <string>
#include <vector>

#include "Commons/AppConstants.h"
#include "QPS/Exceptions/SyntaxException.h"
#include "Token.h"
#include "Tokenizer.h"


std::vector<std::string> specials{AppConstants::STRING_OPEN_ROUND_PARENTHESIS,
                                  AppConstants::STRING_CLOSE_ROUND_PARENTHESIS,
                                  AppConstants::STRING_PLUS,
                                  AppConstants::STRING_MINUS,
                                  AppConstants::STRING_TIMES,
                                  AppConstants::STRING_DIVIDE,
                                  AppConstants::STRING_MODULO,
                                  AppConstants::STRING_SEMICOLON,
                                  AppConstants::STRING_COMMA,
                                  AppConstants::STRING_QUOTE,
                                  AppConstants::STRING_UNDERSCORE,
                                  AppConstants::STRING_DOT,
                                  AppConstants::STRING_EQUAL};

std::vector<std::string> stars{AppConstants::STRING_FOLLOWS, AppConstants::STRING_PARENT, AppConstants::STRING_NEXT,
                               AppConstants::STRING_CALLS};

std::vector<std::string> hashtags{AppConstants::STRING_STATEMENT};

Tokenizer::Tokenizer(const std::string &input) : curr(0) { this->input = input; }

int Tokenizer::peekChar() {
    if (!isCurrValid()) { throw SyntaxException("No more char"); }

    return input[curr];
}

int Tokenizer::popChar() {
    int res = peekChar();
    curr += 1;
    return res;
}

std::string Tokenizer::peekString() {
    if (!isCurrValid()) { throw SyntaxException("No more string"); }
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

    if (!isCurrValid()) { return std::make_shared<Token>(""); }

    // skip if whitespace
    if (isspace(peekChar())) {
        popChar();
        return popToken();
    }

    // one-character token
    auto it = std::find(specials.begin(), specials.end(), peekString());
    if (it != specials.end()) { return std::make_shared<Token>(popString()); }

    if (isalnum(peekChar())) {
        res += popString();

        while (isCurrValid() && isalnum(peekChar())) { res += popString(); }

        // handle star abstraction as one token
        if (isCurrValid() && peekString() == "*") {
            std::string temp = peekString();
            auto it_star = std::find(stars.begin(), stars.end(), res);
            if (it_star != stars.end()) { res += popString(); }
        }

        // handle # abstraction as one token
        if (isCurrValid() && peekString() == "#") {
            std::string temp = peekString();
            auto it_star = std::find(hashtags.begin(), hashtags.end(), res);
            if (it_star != hashtags.end()) { res += popString(); }
        }

        // handle such that as one token
        if (isCurrValid() && res == "such" && peekToken()->getRep() == "that") {
            res += " that";
            popToken();
        }

        return std::make_shared<Token>(res);
    }
    throw SyntaxException("Invalid token");
}

std::shared_ptr<Token> Tokenizer::peekToken() {
    int tmp = curr;
    std::shared_ptr<Token> res = popToken();
    curr = tmp;
    return res;
}

bool Tokenizer::isCurrValid() { return curr >= 0 && curr < (int) input.size(); }

int Tokenizer::getCurr() const { return curr; }
