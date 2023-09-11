#include <utility>

#include "VariableNode.h"

VariableNode::VariableNode(std::string varName) : varName(std::move(varName)) {}

std::string VariableNode::getVarName() {
    return varName;
}

std::vector<std::shared_ptr<ASTNode>> VariableNode::getAllChildNodes() {
    return {};
}

void VariableNode::accept(DesignExtractorVisitor& visitor) {
    if (auto variableVisitor = dynamic_cast<VariableNodeVisitor*>(&visitor)) {
        std::shared_ptr<VariableNode> self(this);
        variableVisitor->visitVariableNode(self);
    }
}