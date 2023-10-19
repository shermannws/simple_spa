#pragma once

#include "SP/AST/Nodes/ArithmeticExpressionNode.h"
#include "SP/AST/Nodes/AssignNode.h"
#include "SP/AST/Nodes/BinaryConditionalExpressionNode.h"
#include "SP/AST/Nodes/CallNode.h"
#include "SP/AST/Nodes/ConstantNode.h"
#include "SP/AST/Nodes/IfNode.h"
#include "SP/AST/Nodes/PrintNode.h"
#include "SP/AST/Nodes/ProcedureNode.h"
#include "SP/AST/Nodes/ProgramNode.h"
#include "SP/AST/Nodes/ReadNode.h"
#include "SP/AST/Nodes/RelativeExpressionNode.h"
#include "SP/AST/Nodes/StatementListNode.h"
#include "SP/AST/Nodes/UnaryConditionalExpressionNode.h"
#include "SP/AST/Nodes/VariableNode.h"
#include "SP/AST/Nodes/WhileNode.h"
#include "SP/AST/Visitors/DesignExtractorVisitor.h"

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

    void visitProgramNode(const std::shared_ptr<ProgramNode> &node, std::vector<std::shared_ptr<ASTNode>> parents,
                          std::shared_ptr<ASTNode> proc) const override;

    /*!
     * Visits a ProcedureNode and adds Procedure to the PKB.
     * @param node The node to be visited
     * @param parents A vector of parent nodes for this node
     */
    void visitProcedureNode(const std::shared_ptr<ProcedureNode> &node, std::vector<std::shared_ptr<ASTNode>> parents,
                            std::shared_ptr<ASTNode> proc) const override;

    void visitStatementListNode(const std::shared_ptr<StatementListNode> &node,
                                std::vector<std::shared_ptr<ASTNode>> parents,
                                std::shared_ptr<ASTNode> proc) const override;

    void visitAssignNode(const std::shared_ptr<AssignNode> &node, std::vector<std::shared_ptr<ASTNode>> parents,
                         std::shared_ptr<ASTNode> proc) const override;

    void visitReadNode(const std::shared_ptr<ReadNode> &node, std::vector<std::shared_ptr<ASTNode>> parents,
                       std::shared_ptr<ASTNode> proc) const override;

    void visitPrintNode(const std::shared_ptr<PrintNode> &node, std::vector<std::shared_ptr<ASTNode>> parents,
                        std::shared_ptr<ASTNode> proc) const override;

    void visitVariableNode(const std::shared_ptr<VariableNode> &node, std::vector<std::shared_ptr<ASTNode>> parents,
                           std::shared_ptr<ASTNode> proc) const override;

    void visitConstantNode(const std::shared_ptr<ConstantNode> &node, std::vector<std::shared_ptr<ASTNode>> parents,
                           std::shared_ptr<ASTNode> proc) const override;

    void visitCallNode(const std::shared_ptr<CallNode> &node, std::vector<std::shared_ptr<ASTNode>> parents,
                       std::shared_ptr<ASTNode> proc) const override;

    void visitIfNode(const std::shared_ptr<IfNode> &node, std::vector<std::shared_ptr<ASTNode>> parents,
                     std::shared_ptr<ASTNode> proc) const override;

    void visitWhileNode(const std::shared_ptr<WhileNode> &node, std::vector<std::shared_ptr<ASTNode>> parents,
                        std::shared_ptr<ASTNode> proc) const override;

    void visitArithmeticExpressionNode(const std::shared_ptr<ArithmeticExpressionNode> &node,
                                       std::vector<std::shared_ptr<ASTNode>> parents,
                                       std::shared_ptr<ASTNode> proc) const override;

    void visitBinaryConditionalExpressionNode(const std::shared_ptr<BinaryConditionalExpressionNode> &node,
                                              std::vector<std::shared_ptr<ASTNode>> parents,
                                              std::shared_ptr<ASTNode> proc) const override;

    void visitUnaryConditionalExpressionNode(const std::shared_ptr<UnaryConditionalExpressionNode> &node,
                                             std::vector<std::shared_ptr<ASTNode>> parents,
                                             std::shared_ptr<ASTNode> proc) const override;

    void visitRelativeExpressionNode(const std::shared_ptr<RelativeExpressionNode> &node,
                                     std::vector<std::shared_ptr<ASTNode>> parents,
                                     std::shared_ptr<ASTNode> proc) const override;
};
