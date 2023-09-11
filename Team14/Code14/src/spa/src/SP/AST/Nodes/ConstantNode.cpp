#include <utility>

#include "ConstantNode.h"

ConstantNode::ConstantNode(int value) : value(value) {}

int ConstantNode::getValue() {
    return value;
}

std::vector<std::shared_ptr<ASTNode>> ConstantNode::getAllChildNodes() {
    return {};
}

void ConstantNode::accept(DesignExtractorVisitor& visitor) {
    if (auto constantVisitor = dynamic_cast<ConstantNodeVisitor*>(&visitor)) {
        std::shared_ptr<ConstantNode> self(this);
        constantVisitor->visitConstantNode(self);
    }
}