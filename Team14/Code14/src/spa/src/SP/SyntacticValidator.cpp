#include "SyntacticValidator.h"

SyntacticValidator::SyntacticValidator(const std::vector<SPToken> &tokens) : tokens(tokens), curr(0) {
    this->tokens=tokens;
}

std::vector<SPToken> SyntacticValidator::validate() {
    while (isCurrValid()) {

        SPToken token = peekToken();
        TokenType ==
    }
}

void SyntacticValidator::validateProcedure() {
    // validate 'procedure'
    validateName();
    validateOpenCurlyParan();
    validateStmtLst();
    validateCloseCurlyParan();
}

void SyntacticValidator::validateRead() {
    // validate 'read'
    validateName();
    validateSemicolon();
}

void SyntacticValidator::validatePrint() {
    // validate 'print'
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
    // expr '+' term
    // expr '-' term
    // OR -- either one must be valid, else throw error
    // term
}

void SyntacticValidator::validateTerm() {
    // term '*' factor
    // term '/' factor
    // term '%' factor
    // OR -- either one must be valid, else throw error
    // factor
}

void SyntacticValidator::validateFactor() {
    // validateName()
    // OR
    // validateConst()
    // OR -- either one must be valid, else throw error
    // '(' expr ')'
}


bool SyntacticValidator::isCurrValid() {
    return curr >= 0 and curr < (int)tokens.size();
}

SPToken SyntacticValidator::peekToken() {
    return tokens[curr];
}

SPToken SyntacticValidator::popToken() {
    SPToken res = peekToken();
    curr += 1;
    return res;
}