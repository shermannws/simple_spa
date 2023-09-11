#include <stdexcept>
#include <vector>
#include <string>

#include "SyntacticValidator.h"

class SyntaxError : public std::runtime_error {
public:
    SyntaxError(const std::string& message) : std::runtime_error(message) {}
};

SyntacticValidator::SyntacticValidator(const std::vector<SPToken> &tokens) : tokens(tokens), curr(0) {}

// main function
std::vector<SPToken> SyntacticValidator::validate() {

        // Check for procedures
        while (isCurrValid()) {
            validateProcedure();
        }
    return tokens;
}

void SyntacticValidator::validateProcedure() {
    // validate 'procedure'
    SPToken token = peekToken();
    if (token.getType() == TokenType::NAME && token.getValue() == "procedure" ) {
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected 'procedure'");
    }

    // validate procedure CGS
    validateName();
    validateOpenCurlyParan();
    validateStmtLst();
    validateCloseCurlyParan();
}

void SyntacticValidator::validateStmtLst() {
    while (isCurrValid()) {
        SPToken token = peekToken();

        if (token.getType() == TokenType::NAME) {
            if (token.getValue() == "read") {
                validateRead();
            } else if (token.getValue() == "print") {
                validatePrint();
            } else {
                validateAssign();
            }
        }  else if (token.getType() == TokenType::CLOSE_CURLY_PARAN) {
            break;
        } else {
            throw SyntaxError("Syntax error: Expected TokenType NAME for statement");
        }
    }
}

void SyntacticValidator::validateRead() {
    // 'read' terminal validated by validateStmtLst()
    popToken();

    // validate rest of read CGS
    validateName();
    validateSemicolon();
}

void SyntacticValidator::validatePrint() {
    // 'print' terminal validated by validateStmtLst()
    popToken();

    // validate rest of print CGS
    validateName();
    validateSemicolon();
}

void SyntacticValidator::validateAssign() {
    validateName();
    validateEquals();
    validateExpr();
    validateSemicolon();
}

void SyntacticValidator::validateExpr() {
    SPToken currToken = peekToken();
    SPToken nextToken = peekNextToken();

    // Recursively check for the next valid term or arithmetic operator til reach end of exp
    validateTerm();
    if (peekNextToken().getType() != TokenType::SEMICOLON &&
        peekToken().getType() == TokenType::ARITHMETIC_OPERATOR) {
        validateArithmeticOperator();
        validateExpr();
    }
}

// TODO: check necessity of this middle factor validation according to CGS
//void SyntacticValidator::validateTerm() {
//    SPToken currToken = peekToken();
//    SPToken nextToken = peekNextToken();
//
//    if (nextToken.getType() == TokenType::ARITHMETIC_OPERATOR) {
//        validateFactor();
//        validateArithmeticOperator(); //TODO: change to * or / or %
//        validateTerm();
//    } else {
//        validateFactor();
//    }
//}

void SyntacticValidator::validateTerm() {
    SPToken currToken = peekToken();
    if (currToken.getType() == TokenType::NAME) {
        validateName();
    } else if (currToken.getType() == TokenType::INTEGER) {
        validateInteger();
    } else if (currToken.getType() == TokenType::OPEN_ROUND_PARAN) {
        validateOpenRoundParan();
        validateExpr();
        validateCloseRoundParan();
    } else {
        throw SyntaxError("Syntax error: Invalid Term");
    }
}

void SyntacticValidator::validateName() {
    SPToken currToken = peekToken();
    if (currToken.getType() == TokenType::NAME) {
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected TokenType NAME");
    }
}

void SyntacticValidator::validateInteger() {
    SPToken currToken = peekToken();
    if (currToken.getType() == TokenType::INTEGER) {
        if (currToken.getValue()[0] == '0') {
            throw SyntaxError("Syntax error: INTEGER cannot start with 0");
        }
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected TokenType INTEGER");
    }
}

void SyntacticValidator::validateOpenRoundParan() {
    SPToken currToken = peekToken();
    if (currToken.getType() == TokenType::OPEN_ROUND_PARAN) {
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected TokenType OPEN_ROUND_PARAN");
    }
}

void SyntacticValidator::validateCloseRoundParan() {
    SPToken currToken = peekToken();
    if (currToken.getType() == TokenType::CLOSE_ROUND_PARAN) {
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected TokenType CLOSE_ROUND_PARAN");
    }
}

void SyntacticValidator::validateOpenCurlyParan() {
    SPToken currToken = peekToken();
    if (currToken.getType() == TokenType::OPEN_CURLY_PARAN) {
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected TokenType OPEN_CURLY_PARAN");
    }
}

void SyntacticValidator::validateCloseCurlyParan() {
    SPToken currToken = peekToken();
    if (currToken.getType() == TokenType::CLOSE_CURLY_PARAN) {
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected TokenType CLOSE_CURLY_PARAN");
    }
}

void SyntacticValidator::validateSemicolon() {
    SPToken currToken = peekToken();
    if (currToken.getType() == TokenType::SEMICOLON) {
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected TokenType SEMICOLON");
    }
}

void SyntacticValidator::validateEquals() {
    SPToken currToken = peekToken();
    if (currToken.getType() == TokenType::EQUALS) {
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected TokenType EQUALS");
    }
}

void SyntacticValidator::validateArithmeticOperator() {
    SPToken currToken = peekToken();
    if (currToken.getType() == TokenType::ARITHMETIC_OPERATOR) {
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected TokenType ARITHMETIC_OPERATOR");
    }
}

bool SyntacticValidator::isCurrValid() {
    return curr >= 0 && curr < (int)tokens.size();
}

SPToken SyntacticValidator::peekToken() {
    return tokens[curr];
}

SPToken SyntacticValidator::peekNextToken() {
    return tokens[curr + 1];
}

SPToken SyntacticValidator::popToken() {
    SPToken res = peekToken();
    curr += 1;
    return res;
}