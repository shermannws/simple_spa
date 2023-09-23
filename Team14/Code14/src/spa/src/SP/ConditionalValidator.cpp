#include "ConditionalValidator.h"

ConditionalValidator::ConditionalValidator(const std::vector<SPToken> &tokens) : tokens(tokens){}

void ConditionalValidator::validate() {
    std::deque<SPToken> tokensDeque(tokens.begin(), tokens.end());
    validateConditionalExpression(tokensDeque);
}

void ConditionalValidator::validateConditionalExpression(std::deque<SPToken> &expression) {
    SPToken token = expression.front();

    if (token.getType() == TokenType::OpenRoundParenthesis) {
        // Find the matching closing parenthesis
        size_t closingParenthesisIndex = findMatchingClosingParenthesis(expression);

        if (closingParenthesisIndex == expression.size()) {
            throw SyntaxError("Syntax error: Unmatched opening parenthesis");
        }

        // Extract the tokens inside the parentheses
        std::deque<SPToken> subExpression(expression.begin() + 1, expression.begin() + closingParenthesisIndex);

        // Check for invalid ((A > B)) cases
        if (subExpression.front().getType() == TokenType::OpenRoundParenthesis) {
            size_t nextClosingParenthesisIndex = findMatchingClosingParenthesis(subExpression);
            if (closingParenthesisIndex == nextClosingParenthesisIndex + 2) {
                throw SyntaxError("Syntax error: Invalid nesting in conditional expression");
            }
        }

        // Decide what to do with the subexpression
        // Option 1 - just remove closing parentheses
        if (closingParenthesisIndex == expression.size() - 1) {
            validateConditionalExpression(subExpression);
        }

        // Option 2 - check next token after the initial ')', split left and right
        if (closingParenthesisIndex < expression.size() - 1) {
            SPToken nextToken = expression[closingParenthesisIndex + 1];
            std::deque<SPToken> rightSubExpression(expression.begin() + closingParenthesisIndex + 2, expression.end());

            // Option 2.1 Conditional expr
            if (nextToken.getValue() == AppConstants::STRING_AND || nextToken.getValue() == AppConstants::STRING_OR) {
                validateConditionalExpression(subExpression);
                validateConditionalExpression(rightSubExpression);
            }

            // Option 2.2 Relational expr
            else if (nextToken.getType() == TokenType::RelationalOperator) {
                validateExpr(subExpression);
                validateExpr(rightSubExpression);
            }

            // Option 2.3 arithmetic expr (for cases like '( (A+B) + C > D )' )
            else if (nextToken.getType() == TokenType::ArithmeticOperator) {
                validateRelationalExpression(rightSubExpression);
            }

            else {
                throw SyntaxError("Syntax error: Missing / wrong operator");
            }
        }

    } else if (token.getType() == TokenType::ConditionalOperator && token.getValue() == AppConstants::STRING_NOT) {
        std::deque<SPToken> subExpression(expression.begin() + 1, expression.end());
        validateConditionalExpression(subExpression);

    } else if (token.getType() == TokenType::Name || token.getType() == TokenType::Integer) {
        validateRelationalExpression(expression);
    } else {
        throw SyntaxError("Syntax error: Unexpected token in conditional expr");
    }
}

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