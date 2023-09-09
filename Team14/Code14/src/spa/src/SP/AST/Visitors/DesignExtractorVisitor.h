#pragma once

// interface for all design extractors
class DesignExtractorVisitor {
public:
    virtual void visitProgramNode() = 0;
    virtual void visitProcedureNode() = 0;
    virtual void visitStatementListNode() = 0;
    virtual void visitAssignNode() = 0;
    virtual void visitReadNode() = 0;
    virtual void visitPrintNode() = 0;
    virtual void visitArithmeticExpressionNode() = 0;
    virtual void visitVariableNode() = 0;
    virtual void visitConstantNode() = 0;
};
