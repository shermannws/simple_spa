#include <string>
#include <utility>

#include "Commons/AppConstants.h"
#include "SPTokenizer.h"
#include "SPToken.h"

#include <iostream>

SPTokenizer::SPTokenizer(std::string  input) : curr(0), input(std::move(input)) {
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
            case AppConstants::CHAR_OPEN_ROUND_PARENTHESIS: // fallthrough
            case AppConstants::CHAR_CLOSE_ROUND_PARENTHESIS: // fallthrough
            case AppConstants::CHAR_OPEN_CURLY_PARENTHESIS: // fallthrough
            case AppConstants::CHAR_CLOSE_CURLY_PARENTHESIS:
                tokenizeParanthesis();
                break;

            case AppConstants::CHAR_SEMICOLON:
                tokenizeSemicolon();
                break;

            case AppConstants::CHAR_EQUAL:
                tokenizeEquals();
                break;

            case AppConstants::CHAR_PLUS: // fallthrough
            case AppConstants::CHAR_MINUS: // fallthrough
            case AppConstants::CHAR_TIMES: // fallthrough
            case AppConstants::CHAR_DIVIDE: // fallthrough
            case AppConstants::CHAR_MODULO:
                tokenizeArithmeticOperator();
                break;

            case AppConstants::CHAR_NOT:
                tokenizeNot();
                break;

            case AppConstants::CHAR_AMPERSAND: // fallthrough
            case AppConstants::CHAR_VERTICAL_BAR:
                tokenizeConditionalOperator();
                break;

            case AppConstants::CHAR_GREATER_THAN: // fallthrough
            case AppConstants::CHAR_LESS_THAN:
                tokenizeRelationalOperator();
                break;

            default:
                // Handle unrecognized chars or errors
                break;
        }
    }

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

int SPTokenizer::peekNextChar() {
    return input[curr + 1];
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
    SPToken token(TokenType::Name, tokenValue);
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
    SPToken token(TokenType::Integer, tokenValue);
    tokens.push_back(token);
};

void SPTokenizer::tokenizeParanthesis() {
    int currChar = peekChar();
    std::string tokenValue;
    tokenValue.push_back(popChar());
    SPToken token;

    switch (currChar) {
        case AppConstants::CHAR_OPEN_ROUND_PARENTHESIS:
            token = SPToken(TokenType::OpenRoundParenthesis, tokenValue);
            break;
        case AppConstants::CHAR_CLOSE_ROUND_PARENTHESIS:
            token = SPToken(TokenType::CloseRoundParenthesis, tokenValue);
            break;
        case AppConstants::CHAR_OPEN_CURLY_PARENTHESIS:
            token = SPToken(TokenType::OpenCurlyParenthesis, tokenValue);
            break;
        case AppConstants::CHAR_CLOSE_CURLY_PARENTHESIS:
            token = SPToken(TokenType::CloseCurlyParenthesis, tokenValue);
            break;
        default:
            break;
    }
    tokens.push_back(token);
};

void SPTokenizer::tokenizeSemicolon() {
    std::string tokenValue;
    tokenValue.push_back(popChar());
    SPToken token(TokenType::Semicolon, tokenValue);
    tokens.push_back(token);
};

void SPTokenizer::tokenizeEquals() {
    std::string tokenValue;

    // Could be '=' or '=='
    if (peekNextChar() == AppConstants::CHAR_EQUAL) {
        tokenizeRelationalOperator();
    } else {
        tokenValue.push_back(popChar());
        SPToken token(TokenType::Equals, tokenValue);
        tokens.push_back(token);
    }
};

void SPTokenizer::tokenizeArithmeticOperator() {
    std::string tokenValue;
    tokenValue.push_back(popChar());
    SPToken token(TokenType::ArithmeticOperator, tokenValue);
    tokens.push_back(token);
};

//TODO: Check if they can be separated by a whitespace? e.g. '&  &'
void SPTokenizer::tokenizeConditionalOperator() {
    std::string tokenValue;
    int currChar = peekChar();

    switch (currChar) {
        case AppConstants::CHAR_NOT :
            tokenValue.push_back(popChar());
            break;

        case AppConstants::CHAR_AMPERSAND:
        case AppConstants::CHAR_VERTICAL_BAR:
            if (peekNextChar() == currChar) {
                tokenValue.push_back(popChar());
                tokenValue.push_back(popChar());
            } else {
                break; //TODO: Throw error
            }

        default:
            break;
    }

    SPToken token(TokenType::ConditionalOperator, tokenValue);
    tokens.push_back(token);
}

void SPTokenizer::tokenizeRelationalOperator() {
    std::string tokenValue;
    tokenValue.push_back(popChar());

    if (peekChar() == AppConstants::CHAR_EQUAL) {
        tokenValue.push_back(popChar());
    }

    SPToken token(TokenType::RelationalOperator, tokenValue);
    tokens.push_back(token);
}

void SPTokenizer::tokenizeNot() {
    if (peekNextChar() == '=') {
        tokenizeRelationalOperator();
    } else {
        tokenizeConditionalOperator();
    }
}