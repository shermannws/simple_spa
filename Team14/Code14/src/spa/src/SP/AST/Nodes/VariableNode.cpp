#include <utility>

#include "VariableNode.h"

VariableNode::VariableNode(std::string varName) : varName(std::move(varName)) {}

void VariableNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitVariableNode();
}
