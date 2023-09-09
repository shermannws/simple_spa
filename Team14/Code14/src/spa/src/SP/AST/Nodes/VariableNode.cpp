#include "VariableNode.h"

VariableNode::VariableNode(std::string& varName) : varName(varName) {}

void VariableNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitVariableNode();
}
