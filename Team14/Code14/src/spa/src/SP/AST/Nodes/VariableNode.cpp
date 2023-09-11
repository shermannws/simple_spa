#include <utility>

#include "VariableNode.h"

VariableNode::VariableNode(std::string varName) : varName(std::move(varName)) {}

std::string VariableNode::getVarName() {
    return varName;
}

void VariableNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitVariableNode();
}
