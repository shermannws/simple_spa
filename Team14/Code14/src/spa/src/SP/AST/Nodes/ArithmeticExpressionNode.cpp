#include "ArithmeticExpressionNode.h"

void ArithmeticExpressionNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitArithmeticExpressionNode();
}
