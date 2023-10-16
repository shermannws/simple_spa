#include <deque>
#include <stack>
#include <vector>

#include "Commons/AppConstants.h"
#include "SP/Errors/SyntaxError.h"
#include "SP/SPToken.h"

/**
 * A helper to the SP subcomponent SyntacticValidator to check conditional
 * expressions.
 */
class ConditionalValidator {
private:
    /**
     * Store of tokens to validate the conditional expression.
     */
    const std::vector<SPToken> &tokens;

    /**
     * Consumes an expression and validates it is a relational expression via
     * recursive descent.
     * @param expression Deque of tokens passed by reference
     */
    void validateConditionalExpression(std::deque<SPToken> &expression);

    /**
     * Consumes an expression and validates it is a relational expression via
     * recursive descent.
     * @param expression Deque of tokens passed by reference
     */
    void validateRelationalExpression(std::deque<SPToken> &expression);

    /**
     * Consumes a deque of tokens and validates it is an expression via
     * recursive descent.
     * @param tokens Deque of tokens passed by reference
     */
    void validateExpr(std::deque<SPToken> &tokens);

    /**
     * Consumes a deque of tokens and validates it is term in an expression via
     * recursive descent.
     * @param tokens Deque of tokens passed by reference
     */
    void validateTerm(std::deque<SPToken> &tokens);

    /**
     * Consumes a token and validates a name.
     * @param tokens Deque of tokens passed by reference
     */
    void validateName(std::deque<SPToken> &tokens);

    /**
     * Consumes a token and validates an integer.
     * @param tokens Deque of tokens passed by reference
     */
    void validateInteger(std::deque<SPToken> &tokens);

    /**
     * Takes in a deque of tokens starting with a '(' and finds the index of the
     * matching closing parenthesis.
     * @param tokens Deque of tokens passed by reference
     * @return The index of the matching closing parenthesis
     */
    size_t findMatchingClosingParenthesis(std::deque<SPToken> &tokens);

    /**
     * Splits an expression by a operator provided as a param.
     * @param expression Deque of tokens passed by reference
     * @param type TokenType to split by
     * @return LHS, RHS deque of tokens split by a TokenType
     */
    std::tuple<std::deque<SPToken>, std::deque<SPToken>, std::string>
    splitExpression(std::deque<SPToken> &expression, TokenType type);

public:
    /**
     * Creates and instantiates a ConditionalValidator.
     * @param tokens Expression to validate
     */
    ConditionalValidator(const std::vector<SPToken> &tokens);

    /**
     * Validates expression via a recursive descent.
     */
    void validate();
};