#include <utility>

#include "VariableNode.h"

VariableNode::VariableNode(VariableName varName) : varName(std::move(varName)) {}

VariableName VariableNode::getVarName() {
    return varName;
}

std::vector<std::shared_ptr<ASTNode>> VariableNode::getAllChildNodes() {
    return {};
}

void VariableNode::accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents) {
    if (auto variableVisitor = std::dynamic_pointer_cast<VariableNodeVisitor>(visitor)) {
        variableVisitor->visitVariableNode(this, parents);
    }
}

std::string VariableNode::toString() {
    return std::string ("(") .append(varName).append(")");
}