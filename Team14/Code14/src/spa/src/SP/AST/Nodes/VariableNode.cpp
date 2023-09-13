#include <utility>

#include "VariableNode.h"

VariableNode::VariableNode(std::string varName) : varName(std::move(varName)) {}

std::string VariableNode::getVarName() {
    return varName;
}

std::vector<std::shared_ptr<ASTNode>> VariableNode::getAllChildNodes() {
    return {};
}

void VariableNode::accept(std::shared_ptr<DesignExtractorVisitor> visitor) {
    if (auto variableVisitor = std::dynamic_pointer_cast<VariableNodeVisitor>(visitor)) {
        variableVisitor->visitVariableNode(this);
    }
}