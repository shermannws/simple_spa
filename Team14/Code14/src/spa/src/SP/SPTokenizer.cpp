#include <string>
#include <iostream>

#include "SPTokenizer.h"
#include "SPToken.h"

SPTokenizer::SPTokenizer(const std::string& input) : curr(0), input(input) {
//    this->input = input;
    tokens = std::vector<SPToken>();
}

// main function, does not handle syntactic validation
std::vector<SPToken> SPTokenizer::tokenize() {

    while (isCurrValid()) {

        // skip if whitespace
        if (isspace(peekChar())) {
            popChar();
        }

        // read current char
        int currChar = peekChar();

        // call different tokenize methods based on curr char
        if (isalpha(currChar)) {
            tokenizeName();
        }

        if (isdigit(currChar)) {
            tokenizeInteger();
        }

        switch (currChar) {
            case '(':
            case ')':
            case '{':
            case '}':
                tokenizeParantheses();
                break;

            case ';':
                tokenizeSemicolon();
                break;

            case '=':
                tokenizeEquals();
                break;

            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
                tokenizeArithmeticOperator();
                break;

            default:
                // Handle unrecognized chars or errors
                break;
        }
    }

    // print statements for debugging
    for (SPToken token : tokens) {
        std::cout << "Token Value: " << token.getValue() << std::endl;
    }

    return this->tokens;
}

bool SPTokenizer::isCurrValid() {
    return curr >= 0 && curr < (int)input.size();
}

int SPTokenizer::peekChar() {
    return input[curr];
}

int SPTokenizer::popChar() {
    int res = peekChar();
    curr += 1;
    return res;
}

void SPTokenizer::tokenizeName() {
    std::string tokenValue;

    while(isCurrValid()) {
        // if alphabet or number, add to token. else break
        if (isalnum(peekChar())) {
            tokenValue.push_back(popChar());
        } else {
            break;
        }
    }
    SPToken token(TokenType::NAME, tokenValue);
    tokens.push_back(token);
};

void SPTokenizer::tokenizeInteger() {
    std::string tokenValue;

    while(isCurrValid()) {
        // if number, add to token. else break
        if (isdigit(peekChar())) {
            tokenValue.push_back(popChar());
        } else {
            break;
        }
    }
    SPToken token(INTEGER, tokenValue);
    tokens.push_back(token);
};

void SPTokenizer::tokenizeParantheses() {
    int currChar = peekChar();
    std::string tokenValue;
    tokenValue.push_back(popChar());
    SPToken token;

    switch (currChar) {
        case '(':
            token = SPToken(OPEN_ROUND_PARAN, tokenValue);
            break;
        case ')':
            token = SPToken(CLOSE_ROUND_PARAN, tokenValue);
            break;
        case '{':
            token = SPToken(OPEN_CURLY_PARAN, tokenValue);
            break;
        case '}':
            token = SPToken(CLOSE_CURLY_PARAN, tokenValue);
            break;
        default:
            break;
    }
    tokens.push_back(token);
};

void SPTokenizer::tokenizeSemicolon() {
    std::string tokenValue;
    tokenValue.push_back(popChar());
    SPToken token(SEMICOLON, tokenValue);
    tokens.push_back(token);
};

void SPTokenizer::tokenizeEquals() {
    std::string tokenValue;
    tokenValue.push_back(popChar());
    SPToken token(EQUALS, tokenValue);
    tokens.push_back(token);
};

void SPTokenizer::tokenizeArithmeticOperator() {
    std::string tokenValue;
    tokenValue.push_back(popChar());
    SPToken token(ARITHMETIC_OPERATOR, tokenValue);
    tokens.push_back(token);
};
