#pragma once

#include <string>
#include <vector>
#include "SPToken.h"

class SyntacticValidator {
public:
    SyntacticValidator(const std::vector<SPToken>& tokens);
    std::vector<SPToken> validate();

private:
    int curr;
    std::vector<SPToken> tokens;

    void validateProcedure();
    void validateName(); // var_name or proc_name
    void validateOpenCurlyParan();
    void validateStmtLst();
    void validateCloseCurlyParan();

    void validateRead();
    void validatePrint();
    void validateSemicolon();

    void validateAssign();
    void validateEquals();
    void validateExpr();




    SPToken peekToken();
    SPToken popToken();
    bool isCurrValid();
};