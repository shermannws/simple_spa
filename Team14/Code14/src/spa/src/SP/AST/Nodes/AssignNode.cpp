#include <utility>

#include "AssignNode.h"

AssignNode::AssignNode(int statementNumber,
                       std::shared_ptr<VariableNode> var,
                       std::shared_ptr<ExpressionNode> expression)
                       : StatementNode(statementNumber),
                       var(std::move(var)),
                       expression(std::move(expression)) {}

std::shared_ptr<VariableNode> AssignNode::getVar() {
    return var;
}

std::shared_ptr<ExpressionNode> AssignNode::getExpression() {
    return expression;
}

void AssignNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitAssignNode(std::make_shared<AssignNode>(this));
}

std::vector<std::shared_ptr<ASTNode>> AssignNode::getAllChildNodes() {
    std::vector<std::shared_ptr<ASTNode>> children { var, expression };
    return children;
}