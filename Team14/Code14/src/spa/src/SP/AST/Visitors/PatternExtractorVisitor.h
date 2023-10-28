#pragma once

#include "../../AST/Nodes/AssignNode.h"
#include "../../AST/Nodes/IfNode.h"
#include "../../AST/Nodes/WhileNode.h"
#include "DesignExtractorVisitor.h"
#include "SP/AST/Nodes/ConditionalExpressionNode.h"
#include "SP/AST/Nodes/RelativeExpressionNode.h"

class PatternExtractorVisitor : public DesignExtractorVisitor,
                                public AssignNodeVisitor,
                                public IfNodeVisitor,
                                public WhileNodeVisitor {

public:
    /**
     * Constructor for PatternExtractorVisitor.
     * @param pkbWriter A shared ptr to a concrete implementation of PkbWriter class
     */
    explicit PatternExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter);

    /**
     * Visits the AssignNode for design extraction.
     * @param node AssignNode to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitAssignNode(const std::shared_ptr<AssignNode> &node, std::vector<std::shared_ptr<Statement>> parents,
                         std::shared_ptr<Procedure> proc) const override;

    /**
     * Visits the IfNode and adds the pattern into the PKB.
     * @param node The node to be visited.
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitIfNode(const std::shared_ptr<IfNode> &node, std::vector<std::shared_ptr<Statement>> parents,
                     std::shared_ptr<Procedure> proc) const override;

    /**
     * Visits a WhileNode and adds the pattern into the PKB
     * @param node The node to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitWhileNode(const std::shared_ptr<WhileNode> &node, std::vector<std::shared_ptr<Statement>> parents,
                        std::shared_ptr<Procedure> proc) const override;

private:
    /**
     * Extracts all the variables from a conditional expression on both the LHS and RHS.
     * @param condExpr The conditional expression
     * @return A vector of variables
     */
    static std::shared_ptr<std::vector<std::shared_ptr<Variable>>>
    getVariablesFromCondExpr(const std::shared_ptr<ConditionalExpressionNode> &condExpr);
};