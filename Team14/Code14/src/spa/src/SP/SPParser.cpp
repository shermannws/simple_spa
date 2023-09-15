#include <regex>
#include <stack>
#include <deque>

#include "Commons/AppConstants.h"
#include "SPParser.h"

SPParser::SPParser() {
    runningStatementNumber = 1;
}

std::shared_ptr<ProgramNode> SPParser::parse(std::vector<SPToken> tokens) {
    // std::queue is an adapter that wraps the underlying std::deque container
    std::queue<SPToken> tokensQueue(std::deque<SPToken>(tokens.begin(), tokens.end()));
    std::vector<std::shared_ptr<ProcedureNode>> procedures;
    while (!tokensQueue.empty()) {
        procedures.push_back(parseProcedure(tokensQueue));
    }
    std::shared_ptr<ProgramNode> programNode = std::make_shared<ProgramNode>(procedures);
    return programNode;
}

std::shared_ptr<ProcedureNode> SPParser::parseProcedure(std::queue<SPToken>& tokens) {
    assert(tokens.front().getValue() == AppConstants::STRING_PROCEDURE && tokens.front().getType() == TokenType::Name);
    tokens.pop(); // consume "procedure" keyword

    assert(tokens.front().getType() == TokenType::Name);
    std::string procedureName = tokens.front().getValue();
    tokens.pop();

    assert(tokens.front().getType() == TokenType::OpenCurlyParenthesis);
    tokens.pop(); // consume "{"
    std::shared_ptr<StatementListNode> statementList = parseStatementList(tokens);
    assert(tokens.front().getType() == TokenType::CloseCurlyParenthesis);
    tokens.pop(); // consume "}"

    std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(procedureName, statementList);
    return procedureNode;
}

std::shared_ptr<StatementListNode> SPParser::parseStatementList(std::queue<SPToken>& tokens) {
    std::vector<std::shared_ptr<StatementNode>> statements;
    while (tokens.front().getType() != TokenType::CloseCurlyParenthesis) {
        if (tokens.front().getType() == TokenType::Name && tokens.front().getValue() == AppConstants::STRING_READ) {
            statements.push_back(parseReadStatement(tokens));
        } else if (tokens.front().getType() == TokenType::Name && tokens.front().getValue() == AppConstants::STRING_PRINT) {
            statements.push_back(parsePrintStatement(tokens));
        } else { // assign is the only statementType not starting with a keyword
            statements.push_back(parseAssignStatement(tokens));
        }
    }
    std::shared_ptr<StatementListNode> statementListNode = std::make_shared<StatementListNode>(statements);
    return statementListNode;
}

std::shared_ptr<AssignNode> SPParser::parseAssignStatement(std::queue<SPToken>& tokens) {
    assert(tokens.front().getType() == TokenType::Name);
    std::shared_ptr<VariableNode> var = parseVariable(tokens);

    assert(tokens.front().getType() == TokenType::Equals);
    tokens.pop(); // consume equals symbol

    std::shared_ptr<ExpressionNode> expression = parseExpression(tokens);

    assert(tokens.front().getType() == TokenType::Semicolon);
    tokens.pop(); // consume semicolon

    std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(runningStatementNumber, var, expression);
    runningStatementNumber++;
    return assignNode;
}

std::shared_ptr<ReadNode> SPParser::parseReadStatement(std::queue<SPToken>& tokens) {
    assert(tokens.front().getType() == TokenType::Name && tokens.front().getValue() == AppConstants::STRING_READ);
    tokens.pop(); // consume "read" keyword

    std::shared_ptr<VariableNode> var = parseVariable(tokens);

    assert(tokens.front().getType() == TokenType::Semicolon);
    tokens.pop(); // consume semicolon

    std::shared_ptr<ReadNode> readNode = std::make_shared<ReadNode>(runningStatementNumber, var);
    runningStatementNumber++;
    return readNode;
}

std::shared_ptr<PrintNode> SPParser::parsePrintStatement(std::queue<SPToken>& tokens) {
    assert(tokens.front().getType() == TokenType::Name && tokens.front().getValue() == AppConstants::STRING_PRINT);
    tokens.pop(); // consume "print" keyword

    std::shared_ptr<VariableNode> var = parseVariable(tokens);

    assert(tokens.front().getType() == TokenType::Semicolon);
    tokens.pop(); // consume semicolon

    std::shared_ptr<PrintNode> printNode = std::make_shared<PrintNode>(runningStatementNumber, var);
    runningStatementNumber++;
    return printNode;
}

// helper function for infixToPostfix function
int getPrecedence(SPToken& operatorToken) {
    assert(operatorToken.getType() == TokenType::ArithmeticOperator);
    std::unordered_map<std::string, int> precedenceMap = {
            { AppConstants::STRING_PLUS, 5 },
            { AppConstants::STRING_MINUS, 5 },
            { AppConstants::STRING_TIMES, 10 },
            { AppConstants::STRING_DIVIDE, 10 },
            { AppConstants::STRING_MODULO, 10 },
    };
    assert(precedenceMap.find(operatorToken.getValue()) != precedenceMap.end());
    return precedenceMap[operatorToken.getValue()];
}

// helper function for SPParser::parseExpression
// See shunting yard algorithm: https://en.wikipedia.org/wiki/Shunting_yard_algorithm
std::queue<SPToken> infixToPostfix(std::queue<SPToken>& tokens) {
    std::queue<SPToken> outputQueue;
    std::stack<SPToken> operatorStack;

    while (tokens.front().getType() != TokenType::Semicolon) {
        SPToken nextToken = tokens.front();
        tokens.pop(); // consume token from queue

        if (nextToken.getType() == TokenType::Name) {   // variable or constant
            outputQueue.push(nextToken);
        } else if (nextToken.getType() == TokenType::Integer) {
            outputQueue.push(nextToken);
        } else if (nextToken.getType() == TokenType::ArithmeticOperator) {
            while (!operatorStack.empty()
                   && operatorStack.top().getType() != TokenType::OpenRoundParenthesis
                   && (getPrecedence(operatorStack.top()) >= getPrecedence(nextToken))
                    ) {
                outputQueue.push(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.push(nextToken);
        } else if (nextToken.getType() == TokenType::OpenRoundParenthesis) {
            operatorStack.push(nextToken);
        } else if (nextToken.getType() == TokenType::CloseRoundParenthesis) {
            while (operatorStack.top().getType() != TokenType::OpenRoundParenthesis) {
                assert(!operatorStack.empty()); // if this fails, parentheses are mismatched
                outputQueue.push(operatorStack.top());
                operatorStack.pop();
            }
            assert(operatorStack.top().getType() == TokenType::OpenRoundParenthesis);
            operatorStack.pop(); // consume "(" token
        }
    }

    while (!operatorStack.empty()) {
        assert(operatorStack.top().getType() != TokenType::OpenRoundParenthesis); // if this fails, parentheses mismatched
        outputQueue.push(operatorStack.top());
        operatorStack.pop();
    }

    assert(operatorStack.empty());
    return outputQueue;
}

std::shared_ptr<ExpressionNode> SPParser::parseExpression(std::queue<SPToken>& tokens) {
    std::queue<SPToken> postfixTokens = infixToPostfix(tokens);
    std::stack<std::shared_ptr<ExpressionNode>> expressionStack;

    while (!postfixTokens.empty()) {
        if (postfixTokens.front().getType() == TokenType::ArithmeticOperator) {
            assert(expressionStack.size() >= 2); // need 2 expressions for arithmetic expressions
            ArithmeticOperatorType operatorType =
                    ArithmeticExpressionNode::translateOperatorTypeString(postfixTokens.front().getValue());
            auto rightExpression = expressionStack.top();
            expressionStack.pop();
            auto leftExpression = expressionStack.top();
            expressionStack.pop();
            auto newExpression =
                    std::make_shared<ArithmeticExpressionNode>(operatorType, leftExpression, rightExpression);
            expressionStack.push(newExpression);
            postfixTokens.pop(); // consume token
        } else if (postfixTokens.front().getType() == TokenType::Integer) {
            expressionStack.push(parseConstant(postfixTokens)); // consumes token
        } else {
            assert(postfixTokens.front().getType() == TokenType::Name);
            expressionStack.push(parseVariable(postfixTokens)); // consumes token
        }
    }

    assert(expressionStack.size() == 1);
    return expressionStack.top();
}


std::shared_ptr<VariableNode> SPParser::parseVariable(std::queue<SPToken>& tokens) {
    assert(tokens.front().getType() == TokenType::Name);
    std::string varName = tokens.front().getValue();
    tokens.pop(); // consume variable name
    std::shared_ptr<VariableNode> variableNode = std::make_shared<VariableNode>(varName);
    return variableNode;
}

std::shared_ptr<ConstantNode> SPParser::parseConstant(std::queue<SPToken>& tokens) {
    assert(tokens.front().getType() == TokenType::Integer);
    std::string stringValue = tokens.front().getValue();
    assert(std::regex_match(stringValue, std::regex(AppConstants::STRING_INTEGER_REGEX)));
    int value = std::stoi(stringValue);
    tokens.pop(); // consume integer constant
    std::shared_ptr<ConstantNode> constantNode = std::make_shared<ConstantNode>(value);
    return constantNode;
}