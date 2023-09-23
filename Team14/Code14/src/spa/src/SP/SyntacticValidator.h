#pragma once

#include <string>
#include <vector>

#include "SPToken.h"
#include "ConditionalValidator.h"

class SyntacticValidator {
public:
    SyntacticValidator(const std::vector<SPToken>& tokens);
    std::vector<SPToken> validate();

private:
    int curr;
    std::vector<SPToken> tokens;

    void validateProcedure();

    void validateStmtLst();

    void validateReadPrintCall();
    void validateAssign();

    void validateExpr();
    void validateTerm();

    void validateWhile();
    void validateIf();
    void validateThen();
    void validateElse();

    void validateName(); // var_name or proc_name
    void validateInteger();
    void validateOpenRoundParen();
    void validateCloseRoundParen();
    void validateOpenCurlyParen();
    void validateCloseCurlyParen();
    void validateSemicolon();
    void validateEquals();
    void validateArithmeticOperator();

    SPToken peekToken();
    SPToken peekNextToken();
    SPToken popToken();
    bool isCurrValid();
};