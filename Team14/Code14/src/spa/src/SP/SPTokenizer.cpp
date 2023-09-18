#include <string>

#include "Commons/AppConstants.h"
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
            case AppConstants::CHAR_OPEN_ROUND_PARENTHESIS: // fallthrough
            case AppConstants::CHAR_CLOSE_ROUND_PARENTHESIS: // fallthrough
            case AppConstants::CHAR_OPEN_CURLY_PARENTHESIS: // fallthrough
            case AppConstants::CHAR_CLOSE_CURLY_PARENTHESIS:
                tokenizeParantheses();
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

            default:
                // Handle unrecognized chars or errors
                break;
        }
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

void SPTokenizer::tokenizeParantheses() {
    int currChar = peekChar();
    std::string tokenValue;
    tokenValue.push_back(popChar());
    SPToken token;

    switch (currChar) {
        case '(':
            token = SPToken(TokenType::OpenRoundParenthesis, tokenValue);
            break;
        case ')':
            token = SPToken(TokenType::CloseRoundParenthesis, tokenValue);
            break;
        case '{':
            token = SPToken(TokenType::OpenCurlyParenthesis, tokenValue);
            break;
        case '}':
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
    tokenValue.push_back(popChar());
    SPToken token(TokenType::Equals, tokenValue);
    tokens.push_back(token);
};

void SPTokenizer::tokenizeArithmeticOperator() {
    std::string tokenValue;
    tokenValue.push_back(popChar());
    SPToken token(TokenType::ArithmeticOperator, tokenValue);
    tokens.push_back(token);
};
