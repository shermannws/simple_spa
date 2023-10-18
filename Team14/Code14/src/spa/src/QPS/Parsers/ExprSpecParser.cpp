#include "ExprSpecParser.h"
#include "QPS/Exceptions/SyntaxException.h"

ExprSpecParser::ExprSpecParser(std::shared_ptr<Tokenizer> tokenizer) : tokenizer(tokenizer) {}

ExpressionSpec ExprSpecParser::extractExpressionSpec() {
    std::shared_ptr<Token> curr = tokenizer->peekToken();
    if (curr->isToken(TokenType::Underscore)) {// WILDCARD OR PARTIAL MATCH
        tokenizer->popToken();
        curr = tokenizer->peekToken();
        if (!curr->isToken(TokenType::Quote)) {// WILDCARD
            return {ExpressionSpecType::Wildcard, ""};
        } else {
            Expression expr = extractExpression();
            curr = tokenizer->popToken();// consume expected trailing underscore
            if (!curr->isToken(TokenType::Underscore)) {
                throw SyntaxException("Invalid Expression Spec, missing trailing _");
            }
            return {ExpressionSpecType::PartialMatch, expr};
        }
    } else if (curr->isToken(TokenType::Quote)) {// EXACT MATCH
        Expression expr = extractExpression();
        return {ExpressionSpecType::ExactMatch, expr};
    } else {
        throw SyntaxException("Invalid Expression Spec");
    }
}

Expression ExprSpecParser::extractExpression() {
    std::shared_ptr<Token> curr = tokenizer->peekToken();// consume Quote
    if (!curr->isToken(TokenType::Quote)) { throw SyntaxException("Invalid expression spec"); }
    tokenizer->popToken();

    std::stack<std::shared_ptr<Token>> operators;
    std::stack<std::string> expression;
    std::vector<std::shared_ptr<Token>> tokens;

    curr = tokenizer->popToken();
    while (!curr->isToken(TokenType::Quote)) {
        tokens.push_back(curr);
        if (curr->isOperand()) {
            expression.push("(" + curr->getRep() + ")");
        } else if (curr->isToken(TokenType::Lparenthesis)) {
            operators.push(curr);
        } else if (curr->isOperator()) {
            while (!operators.empty() && !operators.top()->isToken(TokenType::Lparenthesis) &&
                   operators.top()->precedes(curr)) {
                if (expression.size() < 2) { throw SyntaxException("not enough factors"); }
                processSubExpr(operators, expression);
            }
            operators.push(curr);
        } else if (curr->isToken(TokenType::Rparenthesis)) {
            while (!operators.empty() && !operators.top()->isToken(TokenType::Lparenthesis)) {
                if (expression.size() < 2) { throw SyntaxException("not enough factors"); }
                processSubExpr(operators, expression);
            }
            if (operators.empty() || !operators.top()->isToken(TokenType::Lparenthesis)) {// pop Lparentheses
                throw SyntaxException("Invalid expression spec");
            }
            operators.pop();
        } else {// unexpected token
            throw SyntaxException("Invalid expression spec");
        }
        curr = tokenizer->popToken();
    }
    while (!operators.empty()) {
        if (expression.size() < 2) { throw SyntaxException("not enough factors"); }
        processSubExpr(operators, expression);
    }

    if (expression.empty() || expression.size() > 1) {// empty expression OR too many factors e.g "x y"
        throw SyntaxException("Invalid Expression Spec");
    }
    if (!validateExprSyntax(tokens)) { throw SyntaxException("Invalid Expression Spec from VALIDATE"); }
    return expression.top();
}

void ExprSpecParser::processSubExpr(std::stack<std::shared_ptr<Token>> &operators,
                                    std::stack<std::string> &expression) {
    Expression rightOperand = expression.top();
    expression.pop();
    Expression leftOperand = expression.top();
    expression.pop();
    std::string op = operators.top()->getRep();

    Expression subExpr = std::string("(").append(leftOperand).append(op).append(rightOperand).append(")");
    expression.push(subExpr);
    operators.pop();
}


bool ExprSpecParser::validateExprSyntax(std::vector<std::shared_ptr<Token>> &input) {
    size_t currIndex = 0;
    return isExpr(input, currIndex) && currIndex == input.size();
}

bool ExprSpecParser::isExpr(std::vector<std::shared_ptr<Token>> &input, size_t &index) {
    if (index >= input.size()) { return false; }
    if (isTerm(input, index)) {
        while (index < input.size() &&
               (input[index]->isToken(TokenType::Plus) || input[index]->isToken(TokenType::Minus))) {
            index++;
            if (!isTerm(input, index)) { return false; }
        }
        return true;
    }
    return false;
}

bool ExprSpecParser::isTerm(std::vector<std::shared_ptr<Token>> &input, size_t &index) {
    if (index >= input.size()) { return false; }
    if (isFactor(input, index)) {
        while (index < input.size() &&
               (input[index]->isToken(TokenType::Asterisk) || input[index]->isToken(TokenType::Slash) ||
                input[index]->isToken(TokenType::Percent))) {
            index++;
            if (!isFactor(input, index)) { return false; }
        }
        return true;
    }
    return false;
}

bool ExprSpecParser::isFactor(std::vector<std::shared_ptr<Token>> &input, size_t &index) {
    if (index >= input.size()) { return false; }
    if (input[index]->isIdent() || input[index]->isInteger()) {
        index++;
        return true;
    }
    if (input[index]->isToken(TokenType::Lparenthesis)) {
        index++;
        bool hasValidExpr = isExpr(input, index);
        if (hasValidExpr && index < input.size()) {
            bool hasRParenthesis = input[index]->isToken(TokenType::Rparenthesis);
            index++;
            return hasRParenthesis;
        }
    }
    return false;
}
