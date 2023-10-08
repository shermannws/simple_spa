#include "SPParser.h"

SPParser::SPParser() : runningStatementNumber(AppConstants::INITIAL_STATEMENT_NUMBER) {}

std::shared_ptr<ProgramNode> SPParser::parse(std::vector<SPToken> tokens) {
    runningStatementNumber = AppConstants::INITIAL_STATEMENT_NUMBER;
    // std::deque is an adapter that wraps the underlying std::deque container
    std::deque<SPToken> tokensQueue(tokens.begin(), tokens.end());
    std::vector<std::shared_ptr<ProcedureNode>> procedures;
    while (!tokensQueue.empty()) {
        procedures.push_back(parseProcedure(tokensQueue));
    }
    std::shared_ptr<ProgramNode> programNode = std::make_shared<ProgramNode>(procedures);
    return programNode;
}

std::shared_ptr<ProcedureNode> SPParser::parseProcedure(std::deque<SPToken>& tokens) {
    assert(tokens.front().getValue() == AppConstants::STRING_PROCEDURE && tokens.front().getType() == TokenType::Name);
    tokens.pop_front(); // consume "procedure" keyword

    assert(tokens.front().getType() == TokenType::Name);
    std::string procedureName = tokens.front().getValue();
    tokens.pop_front();

    assert(tokens.front().getType() == TokenType::OpenCurlyParenthesis);
    tokens.pop_front(); // consume "{"
    std::shared_ptr<StatementListNode> statementList = parseStatementList(tokens);
    assert(tokens.front().getType() == TokenType::CloseCurlyParenthesis);
    tokens.pop_front(); // consume "}"

    std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(procedureName, statementList);
    return procedureNode;
}

std::shared_ptr<StatementListNode> SPParser::parseStatementList(std::deque<SPToken>& tokens) {
    std::unordered_map<std::string, std::function<std::shared_ptr<StatementNode>(std::deque<SPToken>&)>> parseFunctionMap;
    parseFunctionMap["read"] = [&] (std::deque<SPToken>& tokens) -> std::shared_ptr<ReadNode> { return parseReadStatement(tokens); };
    parseFunctionMap["print"] = [&] (std::deque<SPToken>& tokens) -> std::shared_ptr<PrintNode> { return parsePrintStatement(tokens); };
    parseFunctionMap["call"] = [&] (std::deque<SPToken>& tokens) -> std::shared_ptr<CallNode> { return parseCallStatement(tokens); };;
    parseFunctionMap["if"] = [&] (std::deque<SPToken>& tokens) -> std::shared_ptr<IfNode> { return parseIfStatement(tokens); };;
    parseFunctionMap["while"] = [&] (std::deque<SPToken>& tokens) -> std::shared_ptr<WhileNode> { return parseWhileStatement(tokens); };;

    std::vector<std::shared_ptr<StatementNode>> statements;
    while (tokens.front().getType() != TokenType::CloseCurlyParenthesis) {
        assert(tokens.front().getType() == TokenType::Name);
        SPToken firstToken = tokens.front();
        tokens.pop_front();
        SPToken secondToken = tokens.front();
        tokens.push_front(firstToken);
        if (secondToken.getType() == TokenType::Equals) {  // handle assign statements
            statements.push_back(parseAssignStatement(tokens));
        } else {
            statements.push_back(parseFunctionMap[tokens.front().getValue()](tokens));
        }
    }
    std::shared_ptr<StatementListNode> statementListNode = std::make_shared<StatementListNode>(statements);
    return statementListNode;
}

std::shared_ptr<AssignNode> SPParser::parseAssignStatement(std::deque<SPToken>& tokens) {
    assert(tokens.front().getType() == TokenType::Name);
    std::shared_ptr<VariableNode> var = parseVariable(tokens);

    assert(tokens.front().getType() == TokenType::Equals);
    tokens.pop_front(); // consume equals symbol

    std::shared_ptr<ExpressionNode> expression = parseExpression(tokens);

    assert(tokens.front().getType() == TokenType::Semicolon);
    tokens.pop_front(); // consume semicolon

    std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(runningStatementNumber, var, expression);
    runningStatementNumber++;
    return assignNode;
}

std::shared_ptr<ReadNode> SPParser::parseReadStatement(std::deque<SPToken>& tokens) {
    assert(tokens.front().getType() == TokenType::Name && tokens.front().getValue() == AppConstants::STRING_READ);
    tokens.pop_front(); // consume "read" keyword

    std::shared_ptr<VariableNode> var = parseVariable(tokens);

    assert(tokens.front().getType() == TokenType::Semicolon);
    tokens.pop_front(); // consume semicolon

    std::shared_ptr<ReadNode> readNode = std::make_shared<ReadNode>(runningStatementNumber, var);
    runningStatementNumber++;
    return readNode;
}

std::shared_ptr<PrintNode> SPParser::parsePrintStatement(std::deque<SPToken>& tokens) {
    assert(tokens.front().getType() == TokenType::Name && tokens.front().getValue() == AppConstants::STRING_PRINT);
    tokens.pop_front(); // consume "print" keyword

    std::shared_ptr<VariableNode> var = parseVariable(tokens);

    assert(tokens.front().getType() == TokenType::Semicolon);
    tokens.pop_front(); // consume semicolon

    std::shared_ptr<PrintNode> printNode = std::make_shared<PrintNode>(runningStatementNumber, var);
    runningStatementNumber++;
    return printNode;
}

std::shared_ptr<CallNode> SPParser::parseCallStatement(std::deque<SPToken> &tokens) {
    assert(tokens.front().getType() == TokenType::Name && tokens.front().getValue() == AppConstants::STRING_CALL);
    tokens.pop_front(); // consume "call" keyword

    assert(tokens.front().getType() == TokenType::Name);
    std::string procedureName = tokens.front().getValue();
    tokens.pop_front(); // consume procName

    assert(tokens.front().getType() == TokenType::Semicolon);
    tokens.pop_front(); // consume ";" token
    std::shared_ptr<CallNode> callNode = std::make_shared<CallNode>(runningStatementNumber, procedureName);
    runningStatementNumber++;
    return callNode;
}

std::shared_ptr<IfNode> SPParser::parseIfStatement(std::deque<SPToken> &tokens) {
    auto currentStatementNumber = runningStatementNumber;
    runningStatementNumber++;

    assert(tokens.front().getType() == TokenType::Name && tokens.front().getValue() == AppConstants::STRING_IF);
    tokens.pop_front(); // consume "if" keyword

    assert(tokens.front().getType() == TokenType::OpenRoundParenthesis);
    tokens.pop_front(); // consume "("
    auto conditionalExpression = parseConditionalExpression(tokens);
    assert(tokens.front().getType() == TokenType::CloseRoundParenthesis);
    tokens.pop_front(); // consume ")"

    assert(tokens.front().getType() == TokenType::Name && tokens.front().getValue() == AppConstants::STRING_THEN);
    tokens.pop_front(); // consume "then" keyword

    assert(tokens.front().getType() == TokenType::OpenCurlyParenthesis);
    tokens.pop_front(); // consume "{" token
    auto thenStatementList = parseStatementList(tokens);
    assert(tokens.front().getType() == TokenType::CloseCurlyParenthesis);
    tokens.pop_front(); // consume "}" token

    assert(tokens.front().getType() == TokenType::Name && tokens.front().getValue() == AppConstants::STRING_ELSE);
    tokens.pop_front(); // consume "else" keyword

    assert(tokens.front().getType() == TokenType::OpenCurlyParenthesis);
    tokens.pop_front(); // consume "{" token
    auto elseStatementList = parseStatementList(tokens);
    assert(tokens.front().getType() == TokenType::CloseCurlyParenthesis);
    tokens.pop_front(); // consume "}" token

    std::shared_ptr<IfNode> ifNode = std::make_shared<IfNode>(
        currentStatementNumber, conditionalExpression, thenStatementList, elseStatementList);

    return ifNode;
}

std::shared_ptr<WhileNode> SPParser::parseWhileStatement(std::deque<SPToken> &tokens) {
    auto currentStatementNumber = runningStatementNumber;
    runningStatementNumber++;

    assert(tokens.front().getType() == TokenType::Name && tokens.front().getValue() == AppConstants::STRING_WHILE);
    tokens.pop_front(); // consume "while" keyword

    assert(tokens.front().getType() == TokenType::OpenRoundParenthesis);
    tokens.pop_front(); // consume "("
    auto conditionalExpression = parseConditionalExpression(tokens);
    assert(tokens.front().getType() == TokenType::CloseRoundParenthesis);
    tokens.pop_front(); // consume ")"

    assert(tokens.front().getType() == TokenType::OpenCurlyParenthesis);
    tokens.pop_front(); // consume "{" token
    auto statementList = parseStatementList(tokens);
    assert(tokens.front().getType() == TokenType::CloseCurlyParenthesis);
    tokens.pop_front(); // consume "}" token

    std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(
        currentStatementNumber, conditionalExpression, statementList);

    return whileNode;
}

std::shared_ptr<ConditionalExpressionNode> SPParser::parseConditionalExpression(std::deque<SPToken> &tokens) {
    if (tokens.front().getType() == TokenType::ConditionalOperator && tokens.front().getValue() == AppConstants::STRING_NOT) {
        // case: '!' '(' cond_expr ')'
        tokens.pop_front(); // consume "!" token

        assert(tokens.front().getType() == TokenType::OpenRoundParenthesis);
        tokens.pop_front(); // consume "("
        auto conditionalExpression = parseConditionalExpression(tokens);
        assert(tokens.front().getType() == TokenType::CloseRoundParenthesis);
        tokens.pop_front(); // consume ")"

        auto unaryConditionalExpression =
                std::make_shared<UnaryConditionalExpressionNode>(conditionalExpression);
        return unaryConditionalExpression;
    } else if (tokens.front().getType() == TokenType::OpenRoundParenthesis) {
        // case 1: rel_expr with parentheses around rel_factor
        // Check for relational operator on LHS
        // If present, means the LHS is a rel_expr within parentheses, which can only mean a binary cond_expr
        // If not present, means whatever is in the parentheses must be a rel_factor, so call parseRelativeExpression
        int index = 1;
        int stack = 1;
        bool hasRelationalOperator = false;
        while (stack != 0) {
            if (tokens.at(index).getType() == TokenType::OpenRoundParenthesis) {
                stack++;
            } else if (tokens.at(index).getType() == TokenType::CloseRoundParenthesis) {
                stack--;
            } else if (tokens.at(index).getType() == TokenType::RelationalOperator) {
                hasRelationalOperator = true;
                break;
            }
            index++;
        }
        if (!hasRelationalOperator) {
            return parseRelativeExpression(tokens);
        }

        // case 2: '(' cond_expr ')' '&&' '(' cond_expr ')'
        // case 3: '(' cond_expr ')' '||' '(' cond_expr ')'
        return parseBinaryConditionalExpression(tokens);
    } else {
        // case: rel_expr
        auto relativeExpression = parseRelativeExpression(tokens);
        return relativeExpression;
    }
}

std::shared_ptr<BinaryConditionalExpressionNode> SPParser::parseBinaryConditionalExpression(std::deque<SPToken> &tokens) {
    assert(tokens.front().getType() == TokenType::OpenRoundParenthesis);
    tokens.pop_front(); // consume "("
    auto leftConditionalExpression = parseConditionalExpression(tokens);
    assert(tokens.front().getType() == TokenType::CloseRoundParenthesis);
    tokens.pop_front(); // consume ")"

    assert(tokens.front().getType() == TokenType::ConditionalOperator);
    assert(tokens.front().getValue() == AppConstants::STRING_AND || tokens.front().getValue() == AppConstants::STRING_OR);
    std::string conditionalOperator = tokens.front().getValue();
    tokens.pop_front(); // consume "&&" or "||" token

    assert(tokens.front().getType() == TokenType::OpenRoundParenthesis);
    tokens.pop_front(); // consume "("
    auto rightConditionalExpression = parseConditionalExpression(tokens);
    assert(tokens.front().getType() == TokenType::CloseRoundParenthesis);
    tokens.pop_front(); // consume ")"

    auto binaryConditionalExpressionType =
            BinaryConditionalExpressionNode::translateBinaryConditionalExpressionTypeString(conditionalOperator);
    auto binaryConditionalExpression = std::make_shared<BinaryConditionalExpressionNode>(
            binaryConditionalExpressionType , leftConditionalExpression, rightConditionalExpression);
    return binaryConditionalExpression;
}

std::shared_ptr<RelativeExpressionNode> SPParser::parseRelativeExpression(std::deque<SPToken> &tokens) {
    auto leftExpression = parseRelativeFactor(tokens);

    assert(tokens.front().getType() == TokenType::RelationalOperator);
    std::string relationalOperatorString = tokens.front().getValue();
    ComparisonOperatorType relationalOperator =
            RelativeExpressionNode::translateComparisonOperatorType(relationalOperatorString);
    tokens.pop_front(); // consume relational operator e.g. ">", ">=", "!=", etc

    auto rightExpression = parseRelativeFactor(tokens);
    assert(tokens.front().getType() == TokenType::CloseRoundParenthesis);

    auto relativeExpression = std::make_shared<RelativeExpressionNode>(
            relationalOperator, leftExpression, rightExpression);
    return relativeExpression;
}

std::shared_ptr<ExpressionNode> SPParser::parseRelativeFactor(std::deque<SPToken> &tokens) {
    // Relative expressions are all in the form ( ... <rel_operator> ... ), so we can use relational
    // operators and closing parenthesis to demarcate the end of a relative factor
    if (tokens.at(1).getType() == TokenType::RelationalOperator ||
        tokens.at(1).getType() == TokenType::CloseRoundParenthesis) {
        if (tokens.front().getType() == TokenType::Name) {
            return parseVariable(tokens);
        } else {
            assert(tokens.front().getType() == TokenType::Integer);
            return parseConstant(tokens);
        }
    } else {
        return parseExpression(tokens);
    }
}

std::shared_ptr<ExpressionNode> SPParser::parseExpression(std::deque<SPToken> &tokens) {
    // parse leftmost term, then parse next term from left to right
    auto leftExpression = parseTerm(tokens);
    // repeat while next token is "+" or "-"
    while (tokens.front().getType() == TokenType::ArithmeticOperator &&
           AppConstants::EXPR_ARITHMETIC_OPERATOR_STRING_SET.count(tokens.front().getValue()) != 0) {
        ArithmeticOperatorType arithmeticOperator =
                ArithmeticExpressionNode::translateOperatorTypeString(tokens.front().getValue());
        tokens.pop_front(); // consume "+" or "-"
        auto nextExpression = parseTerm(tokens);
        leftExpression =
                std::make_shared<ArithmeticExpressionNode>(
                        arithmeticOperator, leftExpression, nextExpression);
    }
    return leftExpression;
}

std::shared_ptr<ExpressionNode> SPParser::parseTerm(std::deque<SPToken>& tokens) {
    // parse leftmost factor, then parse next factor from left to right
    auto leftExpression = parseFactor(tokens);
    // repeat while next token is "*", "/" or "%"
    while (tokens.front().getType() == TokenType::ArithmeticOperator &&
            AppConstants::TERM_ARITHMETIC_OPERATOR_STRING_SET.count(tokens.front().getValue()) != 0) {
        ArithmeticOperatorType arithmeticOperator =
                ArithmeticExpressionNode::translateOperatorTypeString(tokens.front().getValue());
        tokens.pop_front(); // consume "*", "/" or "%"
        auto nextExpression = parseFactor(tokens);
        leftExpression =
                std::make_shared<ArithmeticExpressionNode>(
                        arithmeticOperator, leftExpression, nextExpression);
    }
    return leftExpression;
}

std::shared_ptr<ExpressionNode> SPParser::parseFactor(std::deque<SPToken>& tokens) {
    if (tokens.front().getType() == TokenType::OpenRoundParenthesis) {
        tokens.pop_front(); // consume "("
        auto expression = parseExpression(tokens);
        assert(tokens.front().getType() == TokenType::CloseRoundParenthesis);
        tokens.pop_front(); // consume ")"
        return expression;
    } else if (tokens.front().getType() == TokenType::Name) {
        return parseVariable(tokens);
    } else {
        assert(tokens.front().getType() == TokenType::Integer);
        return parseConstant(tokens);
    }
}

std::shared_ptr<VariableNode> SPParser::parseVariable(std::deque<SPToken>& tokens) {
    assert(tokens.front().getType() == TokenType::Name);
    std::string varName = tokens.front().getValue();
    tokens.pop_front(); // consume variable name
    std::shared_ptr<VariableNode> variableNode = std::make_shared<VariableNode>(varName);
    return variableNode;
}

std::shared_ptr<ConstantNode> SPParser::parseConstant(std::deque<SPToken>& tokens) {
    assert(tokens.front().getType() == TokenType::Integer);
    std::string stringValue = tokens.front().getValue();
    assert(std::regex_match(stringValue, std::regex(AppConstants::STRING_INTEGER_REGEX)));
    tokens.pop_front(); // consume integer constant
    std::shared_ptr<ConstantNode> constantNode = std::make_shared<ConstantNode>(stringValue);
    return constantNode;
}
