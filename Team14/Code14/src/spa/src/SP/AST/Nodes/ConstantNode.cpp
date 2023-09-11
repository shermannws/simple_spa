#include "ConstantNode.h"

ConstantNode::ConstantNode(int value) : value(value) {}

int ConstantNode::getValue() {
    return value;
}

void ConstantNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitConstantNode();
}
