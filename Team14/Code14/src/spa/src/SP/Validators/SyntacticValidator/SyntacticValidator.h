#pragma once

#include <string>
#include <vector>

#include "Commons/AppConstants.h"
#include "ConditionalValidator.h"
#include "SP/SPToken.h"

/**
 * An SP subcomponent to validate the syntax of the tokenized source program.
 */
class SyntacticValidator {
private:
    /**
     * A counter to keep track of the current token.
     */
    int curr;

    /**
     * A vector of tokens to perform recursive descent on.
     */
    std::vector<SPToken> tokens;

    /**
     * Validates a 'procedure' terminal and pops a token, followed by the rest
     * of the procedure CGS.
     */
    void validateProcedure();

    /**
     * Loops through statements in a procedure and calls relevant validate
     * methods.
     */
    void validateStmtLst();

    /**
     * Validates a 'read/print/call' terminal and pops a token, followed by the
     * rest of the CGS.
     */
    void validateReadPrintCall();

    /**
     * Validates an assign statement by calling relevant validate methods in the
     * CGS.
     */
    void validateAssign();

    /**
     * Validates a term, followed by an arithmetic operator and expression if
     * relevant.
     */
    void validateExpr();

    /**
     * Validates a Name or Integer, or a nested expression.
     */
    void validateTerm();

    /**
     * Validates a 'while' loop by calling on a helper class,
     * ConditionalValidator, to validate the conditional expression, followed by
     * the rest of the 'while' CGS.
     */
    void validateWhile();

    /**
     * Validates an 'if' loop by calling on a helper class,
     * ConditionalValidator, to validate the conditional expression, followed by
     * the rest of the 'if' CGS.
     */
    void validateIf();

    /**
     * Validates a 'then' terminal as part of the 'if' loop.
     */
    void validateThen();

    /**
     * Validates an 'else' terminal as part of the 'if' loop.
     */
    void validateElse();

    /**
     * Validates a token of type name which could be a var_name or proc_name.
     */
    void validateName();

    /**
     * Validates an integer which cannot start with '0' if it is non-zero in
     * value.
     */
    void validateInteger();

    /**
     * Validates a token of type '('.
     */
    void validateOpenRoundParen();

    /**
     * Validates a token of type ')'.
     */
    void validateCloseRoundParen();

    /**
     * Validates a token of type '{'.
     */
    void validateOpenCurlyParen();

    /**
     * Validates a token of type '}'.
     */
    void validateCloseCurlyParen();

    /**
     * Validates a token of type ';'.
     */
    void validateSemicolon();

    /**
     * Validates a token of type '='.
     */
    void validateEquals();

    /**
     * Validates a token of type '+,-,*,/,%'
     */
    void validateArithmeticOperator();

    /**
     * Checks the current token pointed to without removing it from the vector.
     * @return SPToken from the tokens vector
     */
    SPToken peekToken();

    /**
     * Checks the next token pointed to without removing it from the vector.
     * @return SPToken from the tokens vector
     */
    SPToken peekNextToken();

    /**
     * Removes the current token pointed to and increment the counter.
     * @return SPToken from the tokens vector
     */
    SPToken popToken();

    /**
     * Checks if the curr counter is indexed at a valid token.
     * @return boolean if true or false
     */
    bool isCurrValid();

public:
    /**
     * Creates and initialises a SyntacticValidator.
     * @param tokens Tokens of the simple source program to be checked
     */
    SyntacticValidator(const std::vector<SPToken> &tokens);

    /**
     * Validates the vector of tokens via a recursive descent by providing an
     * entry point.
     * @return A syntactically valid vector of tokens of the source program
     */
    std::vector<SPToken> validate();
};