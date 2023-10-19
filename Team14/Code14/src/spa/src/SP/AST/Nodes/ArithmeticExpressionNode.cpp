#include <utility>

#include "ArithmeticExpressionNode.h"

ArithmeticExpressionNode::ArithmeticExpressionNode(ArithmeticOperatorType operatorType,
                                                   std::shared_ptr<ExpressionNode> leftExpression,
                                                   std::shared_ptr<ExpressionNode> rightExpression)
    : operatorType(operatorType), leftExpression(std::move(leftExpression)),
      rightExpression(std::move(rightExpression)) {}

ArithmeticOperatorType ArithmeticExpressionNode::getOperatorType() { return operatorType; }

std::shared_ptr<ExpressionNode> ArithmeticExpressionNode::getLeftExpression() { return leftExpression; }

std::shared_ptr<ExpressionNode> ArithmeticExpressionNode::getRightExpression() { return rightExpression; }

ArithmeticOperatorType ArithmeticExpressionNode::translateOperatorTypeString(const std::string &operatorTypeString) {
    assert(stringToOperatorTypeMap.find(operatorTypeString) != stringToOperatorTypeMap.end());
    return stringToOperatorTypeMap.at(operatorTypeString);
}

std::vector<std::shared_ptr<ASTNode>> ArithmeticExpressionNode::getAllChildNodes() {
    std::vector<std::shared_ptr<ASTNode>> children{leftExpression, rightExpression};
    return children;
    return children;
}

void ArithmeticExpressionNode::accept(std::shared_ptr<DesignExtractorVisitor> visitor,
                                      std::vector<std::shared_ptr<Statement>> parents,
                                      std::shared_ptr<Procedure> proc) {
    if (auto aenVisitor = std::dynamic_pointer_cast<ArithmeticExpressionNodeVisitor>(visitor)) {
        aenVisitor->visitArithmeticExpressionNode(this, parents, proc);
    }
}

std::string ArithmeticExpressionNode::toString() {
    return "(" + this->getLeftExpression()->toString() + operatorTypeToStringMap.at(operatorType) +
           this->getRightExpression()->toString() + ")";
}