#include <utility>

#include "ConstantNode.h"

ConstantNode::ConstantNode(ConstantValue value) : value(value) {}

ConstantValue ConstantNode::getValue() { return value; }

std::vector<std::shared_ptr<ASTNode>> ConstantNode::getAllChildNodes() {
    return {};
}

void ConstantNode::accept(std::shared_ptr<DesignExtractorVisitor> visitor,
                          std::vector<std::shared_ptr<ASTNode>> parents,
                          std::shared_ptr<ASTNode> proc) {
    if (auto constantVisitor =
                std::dynamic_pointer_cast<ConstantNodeVisitor>(visitor)) {
        constantVisitor->visitConstantNode(this, parents, proc);
    }
}
std::string ConstantNode::toString() {
    return std::string("(").append(this->getValue()).append(")");
}