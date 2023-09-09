#include "ConstantNode.h"

ConstantNode::ConstantNode(int value) : value(value) {}

void ConstantNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitConstantNode();
}
