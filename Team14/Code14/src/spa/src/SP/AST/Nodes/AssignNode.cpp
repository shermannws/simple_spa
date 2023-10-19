#include <iostream>
#include <utility>

#include "AssignNode.h"

AssignNode::AssignNode(StatementNumber statementNumber, std::shared_ptr<VariableNode> var,
                       std::shared_ptr<ExpressionNode> expression)
    : StatementNode(statementNumber), var(std::move(var)), expression(std::move(expression)) {}

std::shared_ptr<VariableNode> AssignNode::getVar() { return var; }

std::shared_ptr<ExpressionNode> AssignNode::getExpression() { return expression; }

std::vector<std::shared_ptr<ASTNode>> AssignNode::getAllChildNodes() {
    std::vector<std::shared_ptr<ASTNode>> children{var, expression};
    return children;
}

StatementNodeType AssignNode::getStatementType() { return StatementNodeType::Assign; }

void AssignNode::accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<Statement>> parents,
                        std::shared_ptr<Procedure> proc) {
    if (auto assignVisitor = std::dynamic_pointer_cast<AssignNodeVisitor>(visitor)) {
        assignVisitor->visitAssignNode(this, parents, proc);
    }
}