#pragma once

#include <memory>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>
#include <regex>
#include <stack>
#include <deque>
#include <functional>

#include "Commons/AppConstants.h"
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

/**
 * An SP subcomponent to parse the tokenized source program.
 */
class SPParser {
private:
    /**
     * Running number used to label consecutive statements in the source program.
     */
    StatementNumber runningStatementNumber;

    /**
     * Consumes tokens, creates a ProcedureNode and returns a pointer to it.
     * Calls the parser method for StatementList.
     * @param tokens Deque of tokens passed by reference
     * @return A pointer to the created ProcedureNode
     */
    std::shared_ptr<ProcedureNode> parseProcedure(std::deque<SPToken>& tokens);

    /**
     * Consumes tokens, creates a StatementListNode and returns a pointer to it.
     * Calls the correct parser methods for each statement in the StatementList.
     * @param tokens Deque of tokens passed by reference
     * @return A pointer to the created StatementListNode
     */
    std::shared_ptr<StatementListNode> parseStatementList(std::deque<SPToken>& tokens);

    /**
     * Consumes tokens, creates an AssignNode and returns a pointer to it.
     * Calls the parser methods for Variable and Expression.
     * @param tokens Deque of tokens passed by reference
     * @return A pointer to the created AssignNode
     */
    std::shared_ptr<AssignNode> parseAssignStatement(std::deque<SPToken>& tokens);

    /**
     * Consumes tokens, creates a ReadNode and returns a pointer to it.
     * Calls the parser method for Variable.
     * @param tokens Deque of tokens passed by reference
     * @return A pointer to the created ReadNode
     */
    std::shared_ptr<ReadNode> parseReadStatement(std::deque<SPToken>& tokens);

    /**
     * Consumes tokens, creates a PrintNode and returns a pointer to it.
     * Calls the parser method for Variable.
     * @param tokens Deque of tokens passed by reference
     * @return A pointer to the created PrintNode
     */
    std::shared_ptr<PrintNode> parsePrintStatement(std::deque<SPToken>& tokens);

    /**
     * Consumes tokens, creates a CallNode and returns a pointer to it.
     * @param tokens Deque of tokens passed by reference
     * @return A pointer to the created CallNode
     */
    std::shared_ptr<CallNode> parseCallStatement(std::deque<SPToken>& tokens);

    /**
     * Consumes tokens, creates an IfNode and returns a pointer to it.
     * Calls the parser methods for ConditionalExpression and StatementList.
     * @param tokens Deque of tokens passed by reference
     * @return A pointer to the created IfNode
     */
    std::shared_ptr<IfNode> parseIfStatement(std::deque<SPToken>& tokens);

    /**
     * Consumes tokens, creates a WhileNode and returns a pointer to it.
     * Calls the parser methods for ConditionalExpression and StatementList.
     * @param tokens Deque of tokens passed by reference
     * @return A pointer to the created WhileNode
     */
    std::shared_ptr<WhileNode> parseWhileStatement(std::deque<SPToken>& tokens);

    /**
     * Recursively creates RelativeExpressionNodes, UnaryConditionalExpressionNodes and
     * BinaryConditionalExpressionNodes to form one final ConditionalExpressionNode.
     * Calls the parser methods for RelativeExpression and BinaryConditionalExpression.
     * @param tokens Deque of tokens passed by reference
     * @return A pointer to the final ConditionalExpressionNode
     */
    std::shared_ptr<ConditionalExpressionNode> parseConditionalExpression(std::deque<SPToken>& tokens);

    /**
     * Recursively creates left and right conditional expressions and combines them into one final
     * BinaryConditionalExpressionNode.
     * Calls the parser methods of ConditionalExpression.
     * @param tokens Deque of tokens passed by reference
     * @return A pointer to the final BinaryConditionalExpressionNode
     */
    std::shared_ptr<BinaryConditionalExpressionNode> parseBinaryConditionalExpression(std::deque<SPToken>& tokens);

    /**
     * Consumes tokens, creates a RelativeExpressionNode and returns a pointer to it.
     * Calls the parser methods for Expression.
     * @param tokens Deque of tokens passed by reference
     * @return A pointer to the created RelativeExpressionNode
     */
    std::shared_ptr<RelativeExpressionNode> parseRelativeExpression(std::deque<SPToken>& tokens);

    /**
     * Creates a VariableNode, ConstantNode, or parses the nested expression.
     * Returns an ExpressionNode representing a relative factor.
     * @param tokens Deque of tokens passed by reference
     * @return A pointer to the final ExpressionNode (variable, constant or expr)
     */
    std::shared_ptr<ExpressionNode> parseRelativeFactor(std::deque<SPToken>& tokens);

    /**
     * Creates and combines exprs in pairs from left to right.
     * Returns an ExpressionNode representing an expr.
     * @param tokens Deque of tokens passed by reference
     * @return A pointer to the final ExpressionNode (expr)
     */
    std::shared_ptr<ExpressionNode> parseExpression(std::deque<SPToken>& tokens);

    /**
     * Creates and combines terms in pairs from left to right.
     * Returns an ExpressionNode representing a term.
     * @param tokens Deque of tokens passed by reference
     * @return A pointer to the final ExpressionNode (term)
     */
    std::shared_ptr<ExpressionNode> parseTerm(std::deque<SPToken>& tokens);

    /**
     * Creates a VariableNode, ConstantNode or parses the nested expression.
     * Returns an ExpressionNode representing a factor.
     * @param tokens Deque of tokens passed by reference
     * @return A pointer to the final ExpressionNode (factor)
     */
    std::shared_ptr<ExpressionNode> parseFactor(std::deque<SPToken>& tokens);

    /**
     * Consumes tokens, creates an VariableNode and returns a pointer to it.
     * @param tokens Deque of tokens passed by reference
     * @return A pointer to the created VariableNode
     */
    std::shared_ptr<VariableNode> parseVariable(std::deque<SPToken>& tokens);

    /**
     * Consumes tokens, creates a ConstantNode and returns a pointer to it.
     * @param tokens Deque of tokens passed by reference
     * @return A pointer to the created ConstantNode
     */
    std::shared_ptr<ConstantNode> parseConstant(std::deque<SPToken>& tokens);

    /**
     * Map of statement keyword ("assign", "print", etc) to statement parser function
     */
    std::unordered_map<std::string, std::function<std::shared_ptr<StatementNode>(std::deque<SPToken>&)>> parseFunctionMap;
public:
    /**
     * Creates and initiates an SPParser.
     */
    SPParser();

    /**
     * Parses the program tokens into an AST and returns a pointer to the root ProgramNode of the AST.
     * @param tokens Tokens to be parsed
     * @return A pointer to the root ProgramNode of the AST
     */
    std::shared_ptr<ProgramNode> parse(std::vector<SPToken> tokens);
};