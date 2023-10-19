#include <utility>

#include "VariableNode.h"

VariableNode::VariableNode(VariableName varName) : varName(std::move(varName)) {}

VariableName VariableNode::getVarName() { return varName; }

std::vector<std::shared_ptr<ASTNode>> VariableNode::getAllChildNodes() { return {}; }

void VariableNode::accept(std::shared_ptr<DesignExtractorVisitor> visitor,
                          std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) {
    if (auto variableVisitor = std::dynamic_pointer_cast<VariableNodeVisitor>(visitor)) {
        variableVisitor->visitVariableNode(std::enable_shared_from_this<VariableNode>::shared_from_this(), parents,
                                           proc);
    }
}

std::string VariableNode::toString() { return std::string("(").append(varName).append(")"); }