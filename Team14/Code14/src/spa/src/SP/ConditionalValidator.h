#include <vector>
#include <deque>
#include <stack>

#include "SPToken.h"
#include "Commons/AppConstants.h"

class ConditionalValidator {
public:
    ConditionalValidator(const std::vector<SPToken>& tokens);

    // Entry point to validate a relational expression
    void validate();

private:
    const std::vector<SPToken>& tokens;
    void validateConditionalExpression(std::deque<SPToken>& expression);
    void validateRelationalExpression(std::deque<SPToken>& expression);
    void validateExpr(std::deque<SPToken>& tokens);
    void validateTerm(std::deque<SPToken>& tokens);
    size_t findMatchingClosingParenthesis(std::deque<SPToken>& tokens);
    void validateName(std::deque<SPToken>& tokens);
    void validateInteger(std::deque<SPToken>& tokens);

    void validateConditionalExpression2(std::deque<SPToken>& expression);

    std::tuple<std::deque<SPToken>, std::deque<SPToken>, std::string> splitExpression(std::deque<SPToken> &expression, TokenType type);
};