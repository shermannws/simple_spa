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
#include "AST/Nodes/ExpressionNode.h"
#include "AST/Nodes/ArithmeticExpressionNode.h"
#include "AST/Nodes/VariableNode.h"
#include "AST/Nodes/ConstantNode.h"

class SPParser {
private:
    int runningStatementNumber;

    // All methods below pass the queue by reference
    std::shared_ptr<ProcedureNode> parseProcedure(std::queue<SPToken>& tokens);
    std::shared_ptr<StatementListNode> parseStatementList(std::queue<SPToken>& tokens);
    std::shared_ptr<AssignNode> parseAssignStatement(std::queue<SPToken>& tokens);
    std::shared_ptr<ReadNode> parseReadStatement(std::queue<SPToken>& tokens);
    std::shared_ptr<PrintNode> parsePrintStatement(std::queue<SPToken>& tokens);
    std::shared_ptr<ExpressionNode> parseExpression(std::queue<SPToken>& tokens);
    std::shared_ptr<ArithmeticExpressionNode> parseArithmeticExpression(std::queue<SPToken>& tokens);
    std::shared_ptr<VariableNode> parseVariable(std::queue<SPToken>& tokens);
    std::shared_ptr<ConstantNode> parseConstant(std::queue<SPToken>& tokens);

public:
    SPParser();

    std::shared_ptr<ProgramNode> parse(std::vector<SPToken> tokens);
};