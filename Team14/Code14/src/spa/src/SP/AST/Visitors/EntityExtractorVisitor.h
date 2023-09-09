#pragma once

#include "DesignExtractorVisitor.h"

class EntityExtractorVisitor : public DesignExtractorVisitor {
public:
    void visitProgramNode() override;

    void visitProcedureNode() override;

    void visitStatementListNode() override;

    void visitAssignNode() override;

    void visitReadNode() override;

    void visitPrintNode() override;

    void visitArithmeticExpressionNode() override;

    void visitVariableNode() override;

    void visitConstantNode() override;
};
