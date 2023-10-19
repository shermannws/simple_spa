#pragma once

#include <memory>

#include "Commons/AppConstants.h"
#include "ConditionalExpressionNode.h"
#include "StatementListNode.h"
#include "StatementNode.h"

class WhileNode;// forward declaration

/**
 * Visitor interface linked to WhileNode, used to implement the Acyclic Visitor pattern.
 */
class WhileNodeVisitor {
public:
    /**
     * Visits the WhileNode for design extraction.
     * @param node WhileNode to be visited
     * @param parents Parents of the WhileNode
     * @param proc Procedure containing the WhileNode
     */
    virtual void visitWhileNode(const std::shared_ptr<WhileNode> &node, std::vector<std::shared_ptr<ASTNode>> parents,
                                std::shared_ptr<ASTNode> proc) const = 0;
};

/**
 * ASTNode to represent a while statement.
 * Inherits from the StatementNode abstract class.
 */
class WhileNode : public StatementNode, public std::enable_shared_from_this<WhileNode> {
private:
    /**
     * The conditional expression of the while statement.
     */
    std::shared_ptr<ConditionalExpressionNode> conditionalExpression;

    /**
     * The statement list for the while statement.
     */
    std::shared_ptr<StatementListNode> statementList;

public:
    /**
     * Creates and initializes a WhileNode.
     * @param statementNumber The statement number of this statement
     * @param conditionalExpression The conditional expression of the while statement
     * @param statementList The statement list of the while statement
     */
    explicit WhileNode(StatementNumber statementNumber,
                       std::shared_ptr<ConditionalExpressionNode> conditionalExpression,
                       std::shared_ptr<StatementListNode> statementList);

    /**
     * Returns the conditional expression of the while statement.
     * @return The conditional expression of the while statement
     */
    std::shared_ptr<ConditionalExpressionNode> getConditionalExpression();

    /**
     * Returns the statement list for the while statement.
     * @return The statement list for the while statement
     */
    std::shared_ptr<StatementListNode> getStatementList();

    void accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents,
                std::shared_ptr<ASTNode> proc) override;

    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;

    StatementNodeType getStatementType() override;
};
