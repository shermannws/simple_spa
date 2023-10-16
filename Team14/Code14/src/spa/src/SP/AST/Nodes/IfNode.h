#pragma once

#include <memory>

#include "Commons/AppConstants.h"
#include "ConditionalExpressionNode.h"
#include "StatementListNode.h"
#include "StatementNode.h"

class IfNode;// forward declaration

/**
 * Visitor interface linked to IfNode, used to implement the Acyclic Visitor
 * pattern.
 */
class IfNodeVisitor {
public:
    /**
     * Visits the IfNode for design extraction.
     * @param node IfNode to be visited
     * @param parents Parents of the IfNode
     * @param proc The procedure that the IfNode is in
     */
    virtual void visitIfNode(IfNode *node,
                             std::vector<std::shared_ptr<ASTNode>> parents,
                             std::shared_ptr<ASTNode> proc) const = 0;
};

/**
 * ASTNode to represent an if statement.
 * Inherits from the StatementNode abstract class.
 */
class IfNode : public StatementNode {
private:
    /**
     * The conditional expression of the if statement.
     */
    std::shared_ptr<ConditionalExpressionNode> conditionalExpression;

    /**
     * The statement list for then branch.
     */
    std::shared_ptr<StatementListNode> thenStatementList;

    /**
     * The statement list for else branch.
     */
    std::shared_ptr<StatementListNode> elseStatementList;

public:
    /**
     * Creates and initializes an IfNode.
     * @param statementNumber The statement number of this statement
     * @param conditionalExpression The conditional expression of the if
     * statement
     * @param thenStatementList The statement list for then branch
     * @param elseStatementList The statement list for else branch
     */
    explicit IfNode(
            StatementNumber statementNumber,
            std::shared_ptr<ConditionalExpressionNode> conditionalExpression,
            std::shared_ptr<StatementListNode> thenStatementList,
            std::shared_ptr<StatementListNode> elseStatementList);

    /**
     * Returns the conditional expression of the if statement.
     * @return The conditional expression of the if statement
     */
    std::shared_ptr<ConditionalExpressionNode> getConditionalExpression();

    /**
     * Returns the statement list for the "then" branch.
     * This statement list will be run if the conditional expression returns
     * true.
     * @return The statement list for the "then" branch
     */
    std::shared_ptr<StatementListNode> getThenStatementList();

    /**
     * Returns the statement list for the "else" branch.
     * This statement list will be run if the conditional expression returns
     * false.
     * @return The statement list for the "else" branch
     */
    std::shared_ptr<StatementListNode> getElseStatementList();

    void accept(std::shared_ptr<DesignExtractorVisitor> visitor,
                std::vector<std::shared_ptr<ASTNode>> parents,
                std::shared_ptr<ASTNode> proc) override;

    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;

    StatementNodeType getStatementType() override;
};
