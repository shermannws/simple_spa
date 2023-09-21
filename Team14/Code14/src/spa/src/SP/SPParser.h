#pragma once

#include <memory>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>

#include "SPToken.h"
#include "AST/Nodes/ASTNode.h"
#include "AST/Nodes/ProgramNode.h"
#include "AST/Nodes/ProcedureNode.h"
#include "AST/Nodes/StatementListNode.h"
#include "AST/Nodes/StatementNode.h"
#include "AST/Nodes/AssignNode.h"
#include "AST/Nodes/ReadNode.h"
#include "AST/Nodes/PrintNode.h"
#include "AST/Nodes/CallNode.h"
#include "AST/Nodes/IfNode.h"
#include "AST/Nodes/WhileNode.h"
#include "AST/Nodes/ExpressionNode.h"
#include "AST/Nodes/ArithmeticExpressionNode.h"
#include "AST/Nodes/VariableNode.h"
#include "AST/Nodes/ConstantNode.h"
#include "AST/Nodes/ConditionalExpressionNode.h"
#include "AST/Nodes/UnaryConditionalExpressionNode.h"
#include "AST/Nodes/BinaryConditionalExpressionNode.h"
#include "AST/Nodes/RelativeExpressionNode.h"

class SPParser {
private:
    int runningStatementNumber;

    std::shared_ptr<ProcedureNode> parseProcedure(std::queue<SPToken>& tokens);
    std::shared_ptr<StatementListNode> parseStatementList(std::queue<SPToken>& tokens);
    std::shared_ptr<AssignNode> parseAssignStatement(std::queue<SPToken>& tokens);
    std::shared_ptr<ReadNode> parseReadStatement(std::queue<SPToken>& tokens);
    std::shared_ptr<PrintNode> parsePrintStatement(std::queue<SPToken>& tokens);
    std::shared_ptr<CallNode> parseCallStatement(std::queue<SPToken>& tokens);
    std::shared_ptr<IfNode> parseIfStatement(std::queue<SPToken>& tokens);
    std::shared_ptr<WhileNode> parseWhileStatement(std::queue<SPToken>& tokens);
    std::shared_ptr<ExpressionNode> parseExpression(std::queue<SPToken>& tokens, TokenType endDelimiter);
    std::shared_ptr<VariableNode> parseVariable(std::queue<SPToken>& tokens);
    std::shared_ptr<ConstantNode> parseConstant(std::queue<SPToken>& tokens);
    std::shared_ptr<ConditionalExpressionNode> parseConditionalExpression(std::queue<SPToken>& tokens);
    std::shared_ptr<RelativeExpressionNode> parseRelativeExpression(std::queue<SPToken>& tokens);

    /**
     * Returns an int representing the precedence value of the given operator,
     * used for relative comparison with other operators
     * @param operatorToken Operator token to obtain precedence value
     * @return Int representing precedence value of given operator
     */
    static int getOperatorPrecedence(SPToken& operatorToken);

    /**
     * Helper function for SPParser::parseExpression
     * See shunting yard algorithm: https://en.wikipedia.org/wiki/Shunting_yard_algorithm
     * @param tokens Queue of tokens passed by reference
     * @param endDelimiter TokenType of token after the last token to be converted to postfix
     * @return Sorted queue of tokens
     */
    static std::queue<SPToken> infixToPostfix(std::queue<SPToken>& tokens, TokenType endDelimiter);
public:
    SPParser();

    std::shared_ptr<ProgramNode> parse(std::vector<SPToken> tokens);
};