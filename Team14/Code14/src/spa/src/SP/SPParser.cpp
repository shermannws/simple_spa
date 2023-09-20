#include <regex>
#include <stack>
#include <deque>
#include <functional>

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
    std::unordered_map<std::string, std::function<std::shared_ptr<StatementNode>(std::queue<SPToken>&)>> parseFunctionMap;
    parseFunctionMap["read"] = [&] (std::queue<SPToken>& tokens) -> std::shared_ptr<ReadNode> { return parseReadStatement(tokens); };
    parseFunctionMap["print"] = [&] (std::queue<SPToken>& tokens) -> std::shared_ptr<PrintNode> { return parsePrintStatement(tokens); };
    parseFunctionMap["call"] = [&] (std::queue<SPToken>& tokens) -> std::shared_ptr<CallNode> { return parseCallStatement(tokens); };;
    parseFunctionMap["if"] = [&] (std::queue<SPToken>& tokens) -> std::shared_ptr<IfNode> { return parseIfStatement(tokens); };;
    parseFunctionMap["while"] = [&] (std::queue<SPToken>& tokens) -> std::shared_ptr<WhileNode> { return parseWhileStatement(tokens); };;

    std::vector<std::shared_ptr<StatementNode>> statements;
    while (tokens.front().getType() != TokenType::CloseCurlyParenthesis) {
        assert(tokens.front().getType() == TokenType::Name);
        if (parseFunctionMap.find(tokens.front().getValue()) == parseFunctionMap.end()) { // handle assign statements
            statements.push_back(parseAssignStatement(tokens));
        } else {
            statements.push_back(parseFunctionMap[tokens.front().getValue()](tokens));
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

    std::shared_ptr<ExpressionNode> expression = parseExpression(tokens, TokenType::Semicolon);

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

std::shared_ptr<CallNode> SPParser::parseCallStatement(std::queue<SPToken> &tokens) {
    assert(tokens.front().getType() == TokenType::Name && tokens.front().getValue() == AppConstants::STRING_CALL);
    tokens.pop(); // consume "call" keyword

    assert(tokens.front().getType() == TokenType::Name);
    std::string procedureName = tokens.front().getValue();
    tokens.pop(); // consume procName

    assert(tokens.front().getType() == TokenType::Semicolon);
    tokens.pop(); // consume ";" token
    std::shared_ptr<CallNode> callNode = std::make_shared<CallNode>(runningStatementNumber, procedureName);
    runningStatementNumber++;
    return callNode;
}

std::shared_ptr<IfNode> SPParser::parseIfStatement(std::queue<SPToken> &tokens) {
    auto currentStatementNumber = runningStatementNumber++;

    assert(tokens.front().getType() == TokenType::Name && tokens.front().getValue() == AppConstants::STRING_IF);
    tokens.pop(); // consume "if" keyword

    assert(tokens.front().getType() == TokenType::OpenRoundParenthesis);
    tokens.pop(); // consume "(" token
    auto conditionalExpression = parseConditionalExpression(tokens);
    assert(tokens.front().getType() == TokenType::CloseRoundParenthesis);
    tokens.pop(); // consume ")" token

    assert(tokens.front().getType() == TokenType::Name && tokens.front().getValue() == AppConstants::STRING_THEN);
    tokens.pop(); // consume "then" keyword

    assert(tokens.front().getType() == TokenType::OpenCurlyParenthesis);
    tokens.pop(); // consume "{" token
    auto thenStatementList = parseStatementList(tokens);
    assert(tokens.front().getType() == TokenType::CloseCurlyParenthesis);
    tokens.pop(); // consume "}" token

    assert(tokens.front().getType() == TokenType::Name && tokens.front().getValue() == AppConstants::STRING_ELSE);
    tokens.pop(); // consume "else" keyword

    assert(tokens.front().getType() == TokenType::OpenCurlyParenthesis);
    tokens.pop(); // consume "{" token
    auto elseStatementList = parseStatementList(tokens);
    assert(tokens.front().getType() == TokenType::CloseCurlyParenthesis);
    tokens.pop(); // consume "}" token

    std::shared_ptr<IfNode> ifNode = std::make_shared<IfNode>(
        currentStatementNumber, conditionalExpression, thenStatementList, elseStatementList);

    return ifNode;
}

std::shared_ptr<WhileNode> SPParser::parseWhileStatement(std::queue<SPToken> &tokens) {
    auto currentStatementNumber = runningStatementNumber++;

    assert(tokens.front().getType() == TokenType::Name && tokens.front().getValue() == AppConstants::STRING_WHILE);
    tokens.pop(); // consume "while" keyword

    assert(tokens.front().getType() == TokenType::OpenRoundParenthesis);
    tokens.pop(); // consume "(" token
    auto conditionalExpression = parseConditionalExpression(tokens);
    assert(tokens.front().getType() == TokenType::CloseRoundParenthesis);
    tokens.pop(); // consume ")" token

    assert(tokens.front().getType() == TokenType::OpenCurlyParenthesis);
    tokens.pop(); // consume "{" token
    auto statementList = parseStatementList(tokens);
    assert(tokens.front().getType() == TokenType::CloseCurlyParenthesis);
    tokens.pop(); // consume "}" token

    std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(
        currentStatementNumber, conditionalExpression, statementList);

    return whileNode;
}

int SPParser::getOperatorPrecedence(SPToken &operatorToken) {
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

std::queue<SPToken> SPParser::infixToPostfix(std::queue<SPToken> &tokens, TokenType endDelimiter) {
    std::queue<SPToken> outputQueue;
    std::stack<SPToken> operatorStack;

    while (tokens.front().getType() != endDelimiter) {
        SPToken nextToken = tokens.front();
        tokens.pop(); // consume token from queue

        if (nextToken.getType() == TokenType::Name) { // variable
            outputQueue.push(nextToken);
        } else if (nextToken.getType() == TokenType::Integer) { // constant
            outputQueue.push(nextToken);
        } else if (nextToken.getType() == TokenType::ArithmeticOperator) {
            while (!operatorStack.empty()
                   && operatorStack.top().getType() != TokenType::OpenRoundParenthesis
                   && (getOperatorPrecedence(operatorStack.top()) >= getOperatorPrecedence(nextToken))
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

std::shared_ptr<ExpressionNode> SPParser::parseExpression(std::queue<SPToken>& tokens, TokenType endDelimiter) {
    std::queue<SPToken> postfixTokens = infixToPostfix(tokens, endDelimiter);
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

std::shared_ptr<ConditionalExpressionNode> SPParser::parseConditionalExpression(std::queue<SPToken> &tokens) {
    if (tokens.front().getType() == TokenType::ConditionalOperator && tokens.front().getValue() == AppConstants::STRING_NOT) {
        // case: '!' '(' cond_expr ')'
        tokens.pop(); // consume "!" token

        assert(tokens.front().getType() == TokenType::OpenRoundParenthesis);
        tokens.pop(); // consume "(" token
        auto conditionalExpression = parseConditionalExpression(tokens);
        assert(tokens.front().getType() == TokenType::CloseRoundParenthesis);
        tokens.pop(); // consume ")" token

        auto unaryConditionalExpression =
                std::make_shared<UnaryConditionalExpressionNode>(conditionalExpression);
        return unaryConditionalExpression;
    } else if (tokens.front().getType() == TokenType::OpenRoundParenthesis) {
        // case: '(' cond_expr ')' '&&' '(' cond_expr ')'
        // case: '(' cond_expr ')' '||' '(' cond_expr ')'
        tokens.pop(); // consume "(" token
        auto leftConditionalExpression = parseConditionalExpression(tokens);
        assert(tokens.front().getType() == TokenType::CloseRoundParenthesis);
        tokens.pop(); // consume ")" token

        assert(tokens.front().getType() == TokenType::ConditionalOperator);
        assert(tokens.front().getValue() == AppConstants::STRING_AND || tokens.front().getValue() == AppConstants::STRING_OR);
        std::string conditionalOperator = tokens.front().getValue();
        tokens.pop(); // consume "&&" or "||" token

        assert(tokens.front().getType() == TokenType::OpenRoundParenthesis);
        tokens.pop(); // consume "(" token
        auto rightConditionalExpression = parseConditionalExpression(tokens);
        assert(tokens.front().getType() == TokenType::CloseRoundParenthesis);
        tokens.pop();

        auto binaryConditionalExpressionType =
                BinaryConditionalExpressionNode::translateBinaryConditionalExpressionTypeString(conditionalOperator);
        auto binaryConditionalExpression = std::make_shared<BinaryConditionalExpressionNode>(
                binaryConditionalExpressionType , leftConditionalExpression, rightConditionalExpression);
        return binaryConditionalExpression;
    } else {
        // case: rel_expr
        auto relativeExpression = parseRelativeExpression(tokens);
        return relativeExpression;
    }
}

std::shared_ptr<RelativeExpressionNode> SPParser::parseRelativeExpression(std::queue<SPToken> &tokens) {
    // end when encounter ")"
    auto leftExpression = parseExpression(tokens, TokenType::RelationalOperator);

    assert(tokens.front().getType() == TokenType::RelationalOperator);
    std::string relationalOperatorString = tokens.front().getValue();
    ComparisonOperatorType relationalOperator =
            RelativeExpressionNode::translateComparisonOperatorType(relationalOperatorString);
    tokens.pop(); // consume comparison/relational operator e.g. ">", ">=", "!=", etc

    auto rightExpression = parseExpression(tokens, TokenType::CloseRoundParenthesis);
    assert(tokens.front().getType() == TokenType::CloseRoundParenthesis);

    auto relativeExpression = std::make_shared<RelativeExpressionNode>(relationalOperator, leftExpression, rightExpression);
    return relativeExpression;
}