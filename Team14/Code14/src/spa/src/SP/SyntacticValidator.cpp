#include "SyntacticValidator.h"
#include "Errors/SyntaxError.h"

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
    if (token.getType() == TokenType::Name && token.getValue() == AppConstants::STRING_PROCEDURE ) {
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
    if (peekToken().getType() == TokenType::CloseCurlyParenthesis) {
        throw SyntaxError("Syntax error: StmtLst cannot be empty");
    }

    while (isCurrValid()) {
        SPToken token = peekToken();

        if (token.getType() == TokenType::CloseCurlyParenthesis) {
            break;
        } else if (peekNextToken().getType() == TokenType::Equals) {
            validateAssign();
        } else if (token.getType() == TokenType::Name) {
            if (token.getValue() == AppConstants::STRING_READ) {
                validateRead();
            } else if (token.getValue() == AppConstants::STRING_PRINT) {
                validatePrint();
            } else if (token.getValue() == AppConstants::STRING_CALL) {
                validateCall();
            } else if (token.getValue() == AppConstants::STRING_WHILE) {
                validateWhile();
            } else if (token.getValue() == AppConstants::STRING_IF) {
                validateIf();
            } else {
                throw SyntaxError("Syntax error: Invalid Stmt");
            }
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

void SyntacticValidator::validateCall() {
    // 'call' terminal validated by validateStmtLst()
    popToken();

    // validate rest of call CGS
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
    if (peekNextToken().getType() != TokenType::Semicolon &&
        peekToken().getType() == TokenType::ArithmeticOperator) {
        validateArithmeticOperator();
        validateExpr();
    }
}

void SyntacticValidator::validateTerm() {
    SPToken currToken = peekToken();
    if (currToken.getType() == TokenType::Name) {
        validateName();
    } else if (currToken.getType() == TokenType::Integer) {
        validateInteger();
    } else if (currToken.getType() == TokenType::OpenRoundParenthesis) {
        validateOpenRoundParan();
        validateExpr();
        validateCloseRoundParan();
    } else {
        throw SyntaxError("Syntax error: Invalid Term");
    }
}

void SyntacticValidator::validateWhile() {
    // 'while' terminal validated by validateStmtLst()
    popToken();

    validateOpenRoundParan();
    validateConditionalExpression();
    validateCloseRoundParan();

    validateOpenCurlyParan();
    validateStmtLst();
    validateCloseCurlyParan();
}

void SyntacticValidator::validateIf() {
    // 'if' terminal validated by validateStmtLst()
    popToken();

    validateOpenRoundParan();
    validateConditionalExpression();
    validateCloseRoundParan();

    validateThen();
    validateOpenCurlyParan();
    validateStmtLst();
    validateCloseCurlyParan();

    validateElse();
    validateOpenCurlyParan();
    validateStmtLst();
    validateCloseCurlyParan();
}

void SyntacticValidator::validateThen() {
    if (peekToken().getType() == TokenType::Name &&
        peekToken().getValue() == AppConstants::STRING_THEN) {
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected 'then' in if statement");
    }
}

void SyntacticValidator::validateElse() {
    if (peekToken().getType() == TokenType::Name &&
        peekToken().getValue() == AppConstants::STRING_ELSE) {
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected 'else' in if statement");
    }
}

void SyntacticValidator::validateConditionalExpression() {
    if (peekToken().getType() == TokenType::ConditionalOperator &&
        peekToken().getValue() == AppConstants::STRING_NOT) {
        popToken();
        validateOpenRoundParan();
        validateConditionalExpression();
        validateCloseRoundParan();
    } else if (peekToken().getType() == TokenType::OpenRoundParenthesis) {
        validateOpenRoundParan();
        validateConditionalExpression();
        validateCloseRoundParan();

        validateAndOrOperator();

        validateOpenRoundParan();
        validateConditionalExpression();
        validateCloseRoundParan();
    } else {
        validateRelationalExpression();
    }
}

void SyntacticValidator::validateAndOrOperator() {
    if (peekToken().getType() == TokenType::ConditionalOperator &&
    (peekToken().getValue() == AppConstants::STRING_AND || peekToken().getValue() == AppConstants::STRING_OR)) {
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected '&&' or '||' logical operator");
    }
}

void SyntacticValidator::validateRelationalExpression() {
    validateExpr();
    validateRelationalOperator();
    validateExpr();
}

void SyntacticValidator::validateRelationalOperator() {
    if (peekToken().getType() == TokenType::RelationalOperator) {
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected relational operator");
    }
}

void SyntacticValidator::validateName() {
    SPToken currToken = peekToken();
    if (currToken.getType() == TokenType::Name) {
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected TokenType NAME");
    }
}

void SyntacticValidator::validateInteger() {
    SPToken currToken = peekToken();
    if (currToken.getType() == TokenType::Integer) {
        if (currToken.getValue()[0] == '0' && currToken.getValue().size() != 1) {
            throw SyntaxError("Syntax error: INTEGER cannot start with 0");
        }
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected TokenType INTEGER");
    }
}

void SyntacticValidator::validateOpenRoundParan() {
    SPToken currToken = peekToken();
    if (currToken.getType() == TokenType::OpenRoundParenthesis) {
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected TokenType OPEN_ROUND_PARAN");
    }
}

void SyntacticValidator::validateCloseRoundParan() {
    SPToken currToken = peekToken();
    if (currToken.getType() == TokenType::CloseRoundParenthesis) {
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected TokenType CLOSE_ROUND_PARAN");
    }
}

void SyntacticValidator::validateOpenCurlyParan() {
    SPToken currToken = peekToken();
    if (currToken.getType() == TokenType::OpenCurlyParenthesis) {
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected TokenType OPEN_CURLY_PARAN");
    }
}

void SyntacticValidator::validateCloseCurlyParan() {
    SPToken currToken = peekToken();
    if (currToken.getType() == TokenType::CloseCurlyParenthesis) {
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected TokenType CLOSE_CURLY_PARAN");
    }
}

void SyntacticValidator::validateSemicolon() {
    SPToken currToken = peekToken();
    if (currToken.getType() == TokenType::Semicolon) {
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected TokenType SEMICOLON");
    }
}

void SyntacticValidator::validateEquals() {
    SPToken currToken = peekToken();
    if (currToken.getType() == TokenType::Equals) {
        popToken();
    } else {
        throw SyntaxError("Syntax error: Expected TokenType EQUALS");
    }
}

void SyntacticValidator::validateArithmeticOperator() {
    SPToken currToken = peekToken();
    if (currToken.getType() == TokenType::ArithmeticOperator) {
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