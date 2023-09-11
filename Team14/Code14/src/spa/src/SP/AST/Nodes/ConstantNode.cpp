#include <utility>

#include "ConstantNode.h"

ConstantNode::ConstantNode(int value) : value(value) {}

int ConstantNode::getValue() {
    return value;
}

void ConstantNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitConstantNode(std::make_shared<ConstantNode>(this));
}

std::vector<std::shared_ptr<ASTNode>> ConstantNode::getAllChildNodes() {
    return {};
}