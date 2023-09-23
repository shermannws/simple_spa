#include "ConditionalValidator.h"

class SyntaxError : public std::runtime_error {
public:
    SyntaxError(const std::string& message) : std::runtime_error(message) {}
};

ConditionalValidator::ConditionalValidator(const std::vector<SPToken> &tokens) : tokens(tokens){}

void ConditionalValidator::validate() {

    std::deque<SPToken> tokensDeque(tokens.begin(), tokens.end());
    validateConditionalExpression(tokensDeque);
}

void ConditionalValidator::validateConditionalExpression(std::deque<SPToken>& expression) {
    if (expression.empty()) {
        throw SyntaxError("Syntax error: Expected conditional expression but received nothing");
    }

    // Remove first and last braces
    if (expression.front().getType() == TokenType::OpenRoundParenthesis && expression.back().getType() == TokenType::CloseRoundParenthesis) {
        expression.pop_front();
        expression.pop_back();
    } else {
        throw SyntaxError("Syntax error: Expected matching parenthesis for conditional expression");
    }

    std::deque<SPToken> LHS;
    std::deque<SPToken> RHS;
    std::string operatorAsString;
    std::tie(LHS, RHS, operatorAsString) = splitExpression(expression, TokenType::ConditionalOperator);

    // Operator found
    if (!RHS.empty()) {

        if (operatorAsString == AppConstants::STRING_NOT) {
            if (!LHS.empty()) {
                throw SyntaxError("Syntax error: Wrong use of '!' conditional");
            }
            validateConditionalExpression(RHS);
        }

        if (operatorAsString == AppConstants::STRING_AND || operatorAsString == AppConstants::STRING_OR) {
            validateConditionalExpression(LHS);
            validateConditionalExpression(RHS);
        }
    }

    // If operator not found, process the whole expression as a rel_expr
    if (RHS.empty()) {
        validateRelationalExpression(LHS);
    }
};

void ConditionalValidator::validateRelationalExpression(std::deque<SPToken>& expression) {
    std::deque<SPToken> LHS, RHS;
    std::string operatorAsString;
    std::tie(LHS, RHS, operatorAsString) = splitExpression(expression, TokenType::RelationalOperator);

    if (LHS.empty() || RHS.empty()) {
        throw SyntaxError("Syntax Error: Expected rel_expr in Relation Expression");
    }

    validateExpr(LHS);
    validateExpr(RHS);
}

std::tuple<std::deque<SPToken>, std::deque<SPToken>, std::string> ConditionalValidator::splitExpression(std::deque<SPToken>& expression, TokenType type) {
    std::deque<SPToken> LHS;
    std::deque<SPToken> RHS;

    bool operatorFound = false;
    std::string operatorAsString;

    // Construct LHS and RHS
    for (SPToken token : expression) {
        if (operatorFound) {
            RHS.push_back(token);
        } else {
            if (token.getType() == type) {
                operatorAsString = token.getValue();
                operatorFound = true;
            } else {
                LHS.push_back(token);
            }
        }
    }

    return std::make_tuple(LHS, RHS, operatorAsString);
}

void ConditionalValidator::validateExpr(std::deque<SPToken>& tokens) {
    if (tokens.empty()) {
        throw SyntaxError("Syntax error: Empty expression");
    }

    validateTerm(tokens);

    if(!tokens.empty() && tokens.front().getType() != TokenType::ArithmeticOperator) {
        throw SyntaxError("Syntax error: Expected arithmetic operator while checking relational expr");
    }

    if (!tokens.empty() && tokens.front().getType() == TokenType::ArithmeticOperator) {
        tokens.pop_front();
        validateExpr(tokens);
    }
}

void ConditionalValidator::validateTerm(std::deque<SPToken>& tokens) {
    if (tokens.empty()) {
        throw SyntaxError("Syntax error: Empty term");
    }

    SPToken& currToken = tokens.front();

    if (currToken.getType() == TokenType::Name)  {
        validateName(tokens);
    } else if (currToken.getType() == TokenType::Integer) {
        validateInteger(tokens);
    } else if (currToken.getType() == TokenType::OpenRoundParenthesis) {
        size_t closingParenthesisIndex = findMatchingClosingParenthesis(tokens);

        if (closingParenthesisIndex == tokens.size()) {
            throw SyntaxError("Syntax error: Unmatched opening parenthesis");
        }

        std::deque<SPToken> exprTokens(tokens.begin() + 1, tokens.begin() + closingParenthesisIndex);

        validateExpr(exprTokens);

        tokens.erase(tokens.begin(), tokens.begin() + closingParenthesisIndex + 1);
    } else {
        throw SyntaxError("Syntax error: Invalid Term");
    }
}

size_t ConditionalValidator::findMatchingClosingParenthesis(std::deque<SPToken>& tokens) {
    int nestingLvl = 1;

    for (size_t i = 1; i < tokens.size(); i++) {
        if (tokens[i].getType() == TokenType::OpenRoundParenthesis) {
            nestingLvl++;
        } else if (tokens[i].getType() == TokenType::CloseRoundParenthesis) {
            nestingLvl --;
            if (nestingLvl == 0) {
                return i;
            }
        }
    }

    // No matching closing parenthesis found
    return tokens.size();
}

void ConditionalValidator::validateName(std::deque<SPToken>& tokens) {
    if (tokens.front().getType() == TokenType::Name) {
        tokens.pop_front();
    } else {
        throw SyntaxError("Syntax error: Expected TokenType NAME");
    }
}

void ConditionalValidator::validateInteger(std::deque<SPToken>& tokens) {
    SPToken currToken = tokens.front();

    if (currToken.getType() == TokenType::Integer) {
        if (currToken.getValue()[0] == '0' && currToken.getValue().size() != 1) {
            throw SyntaxError("Syntax error: INTEGER cannot start with 0");
        }
       tokens.pop_front();
    } else {
        throw SyntaxError("Syntax error: Expected TokenType INTEGER");
    }
}

void ConditionalValidator::validateConditionalExpression2(std::deque<SPToken> &expression) {
    std::stack<std::deque<SPToken>> expressionStack;
    std::string operatorAsString;

    while (!expression.empty()) {
        SPToken token = expression.front();
        expression.pop_front();

        if (token.getType() == TokenType::ConditionalOperator) {
            operatorAsString = token.getValue();
        } else if (token.getType() == TokenType::OpenRoundParenthesis) {
            // Find the matching closing parenthesis
            size_t closingParenthesisIndex = findMatchingClosingParenthesis(expression);

            if (closingParenthesisIndex == expression.size()) {
                throw SyntaxError("Syntax error: Unmatched opening parenthesis");
            }

            // Extract the tokens inside the parentheses
            std::deque<SPToken> subExpression(expression.begin(), expression.begin() + closingParenthesisIndex);

            // Validate the sub-expression
            validateConditionalExpression(subExpression);

            // Remove the processed tokens
            expression.erase(expression.begin(), expression.begin() + closingParenthesisIndex + 1);

            // Push the result of the sub-expression onto the stack
            expressionStack.push(subExpression);
        } else {
            throw SyntaxError("Syntax error: Unexpected token in conditional expression");
        }

        if (!operatorAsString.empty()) {
            if (operatorAsString == AppConstants::STRING_NOT) {
                if (expressionStack.empty()) {
                    throw SyntaxError("Syntax error: Wrong use of '!' conditional");
                }
                std::deque<SPToken> rhs = expressionStack.top();
                expressionStack.pop();
                // Validate the '!' operator here if needed

                // Combine the result with the '!' operator
                // Perform any validation or processing you need to do here
            } else if (operatorAsString == AppConstants::STRING_AND || operatorAsString == AppConstants::STRING_OR) {
                if (expressionStack.size() < 2) {
                        throw SyntaxError("Syntax error: Insufficient operands for logical operator");
                }
                std::deque<SPToken> rhs = expressionStack.top();
                expressionStack.pop();
                std::deque<SPToken> lhs = expressionStack.top();
                expressionStack.pop();

                // Validate and process the '&&' or '||' operator here

                // Combine the results of lhs and rhs based on the operator
                // Perform any validation or processing you need to do here

                // Push the combined result back onto the stack
                expressionStack.push(result);
            }
            operatorAsString.clear();
        }
    }


    }


}