#pragma once

#include "SP/AST/Visitors/DesignExtractorVisitor.h"
#include "SP/AST/Nodes/ProgramNode.h"
#include "SP/AST/Nodes/ProcedureNode.h"
#include "SP/AST/Nodes/StatementListNode.h"
#include "SP/AST/Nodes/AssignNode.h"
#include "SP/AST/Nodes/ReadNode.h"
#include "SP/AST/Nodes/PrintNode.h"
#include "SP/AST/Nodes/CallNode.h"
#include "SP/AST/Nodes/IfNode.h"
#include "SP/AST/Nodes/WhileNode.h"
#include "SP/AST/Nodes/ArithmeticExpressionNode.h"
#include "SP/AST/Nodes/BinaryConditionalExpressionNode.h"
#include "SP/AST/Nodes/UnaryConditionalExpressionNode.h"
#include "SP/AST/Nodes/RelativeExpressionNode.h"
#include "SP/AST/Nodes/VariableNode.h"
#include "SP/AST/Nodes/ConstantNode.h"

class ASTPrinterVisitor : public DesignExtractorVisitor,
        public ProgramNodeVisitor,
        public ProcedureNodeVisitor,
        public StatementListNodeVisitor,
        public AssignNodeVisitor,
        public ReadNodeVisitor,
        public PrintNodeVisitor,
        public VariableNodeVisitor,
        public ConstantNodeVisitor,
        public CallNodeVisitor,
        public IfNodeVisitor,
        public WhileNodeVisitor,
        public ArithmeticExpressionNodeVisitor,
        public BinaryConditionalExpressionNodeVisitor,
        public UnaryConditionalExpressionNodeVisitor,
        public RelativeExpressionNodeVisitor {
public:
    /*!
     * Constructor for ASTPrinterVisitor.
     * @param pkbWriter A shared ptr to a concrete implementation of PkbWriter class
     */
    ASTPrinterVisitor(std::shared_ptr<PkbWriter> pkbWriter);

    void visitProgramNode(ProgramNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    /*!
     * Visits a ProcedureNode and adds Procedure to the PKB.
     * @param node The node to be visited
     * @param parents A vector of parent nodes for this node
     */
    void visitProcedureNode(ProcedureNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    void visitStatementListNode(StatementListNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    void visitAssignNode(AssignNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    void visitReadNode(ReadNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    void visitPrintNode(PrintNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    void visitVariableNode(VariableNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    void visitConstantNode(ConstantNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    void visitCallNode(CallNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    void visitIfNode(IfNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    void visitWhileNode(WhileNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    void visitArithmeticExpressionNode(ArithmeticExpressionNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    void visitBinaryConditionalExpressionNode(BinaryConditionalExpressionNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    void visitUnaryConditionalExpressionNode(UnaryConditionalExpressionNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    void visitRelativeExpressionNode(RelativeExpressionNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

};
