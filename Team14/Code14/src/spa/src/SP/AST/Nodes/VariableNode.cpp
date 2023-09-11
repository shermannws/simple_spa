#include <utility>

#include "VariableNode.h"

VariableNode::VariableNode(std::string varName) : varName(std::move(varName)) {}

std::string VariableNode::getVarName() {
    return varName;
}

void VariableNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitVariableNode(std::make_shared<VariableNode>(this));
}

std::vector<std::shared_ptr<ASTNode>> VariableNode::getAllChildNodes() {
    return {};
}