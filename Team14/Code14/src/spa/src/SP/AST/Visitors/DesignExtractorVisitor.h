#pragma once

#include <memory>

#include "PKB/PkbWriter.h"
#include "../../AST/Nodes/ProgramNode.h"
#include "../../AST/Nodes/ProcedureNode.h"
#include "../../AST/Nodes/StatementListNode.h"
#include "../../AST/Nodes/AssignNode.h"
#include "../../AST/Nodes/ReadNode.h"
#include "../../AST/Nodes/PrintNode.h"
#include "../../AST/Nodes/ArithmeticExpressionNode.h"
#include "../../AST/Nodes/VariableNode.h"
#include "../../AST/Nodes/ConstantNode.h"

// interface for all design extractors
class DesignExtractorVisitor {
protected:
    std::shared_ptr<PkbWriter> pkbWriter;

public:
    virtual void visitProgramNode(std::shared_ptr<ProgramNode> node) = 0;
    virtual void visitProcedureNode(std::shared_ptr<ProcedureNode> node) = 0;
    virtual void visitStatementListNode(std::shared_ptr<StatementListNode> node) = 0;
    virtual void visitAssignNode(std::shared_ptr<AssignNode> node) = 0;
    virtual void visitReadNode(std::shared_ptr<ReadNode> node) = 0;
    virtual void visitPrintNode(std::shared_ptr<PrintNode> node) = 0;
    virtual void visitArithmeticExpressionNode(std::shared_ptr<ArithmeticExpressionNode> node) = 0;
    virtual void visitVariableNode(std::shared_ptr<VariableNode> node) = 0;
    virtual void visitConstantNode(std::shared_ptr<ConstantNode> node) = 0;
};
