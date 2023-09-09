#pragma once

#include <memory>
#include <vector>
#include <deque>
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
#include "AST/Nodes/ExpressionNode.h"
#include "AST/Nodes/ArithmeticExpressionNode.h"
#include "AST/Nodes/VariableNode.h"
#include "AST/Nodes/ConstantNode.h"

class SPParser {
private:
//    // std::shared_ptr<ASTNode> : return type
//    // (SPParser::*) : all functions are part of SPParser
//    // (std::deque<SPToken>&) : function parameters
//    std::unordered_map<std::string, std::shared_ptr<ASTNode>(SPParser::*)(std::deque<SPToken>&)> statementToParserMap;

    // All methods below pass the deque by reference
    std::shared_ptr<ProcedureNode> parseProcedure(std::deque<SPToken>& tokens);
    std::shared_ptr<StatementListNode> parseStatementList(std::deque<SPToken>& tokens);
    std::shared_ptr<AssignNode> parseAssignStatement(std::deque<SPToken>& tokens);
    std::shared_ptr<ReadNode> parseReadStatement(std::deque<SPToken>& tokens);
    std::shared_ptr<PrintNode> parsePrintStatement(std::deque<SPToken>& tokens);
    std::shared_ptr<ExpressionNode> parseExpression(std::deque<SPToken>& tokens);
    std::shared_ptr<ArithmeticExpressionNode> parseArithmeticExpression(std::deque<SPToken>& tokens);
    std::shared_ptr<VariableNode> parseVariable(std::deque<SPToken>& tokens);
    std::shared_ptr<ConstantNode> parseConstant(std::deque<SPToken>& tokens);

public:
    SPParser();

    std::shared_ptr<ProgramNode> parse(std::vector<SPToken> tokens);
};