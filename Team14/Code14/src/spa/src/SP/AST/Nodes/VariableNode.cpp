#include "VariableNode.h"

VariableNode::VariableNode(std::string& varName, int value) : varName(varName), value(value) {}

void VariableNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitVariableNode();
}
