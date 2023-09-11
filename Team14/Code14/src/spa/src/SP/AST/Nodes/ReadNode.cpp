#include <utility>

#include "ReadNode.h"

ReadNode::ReadNode(int statementNumber, std::shared_ptr<VariableNode> var)
        : StatementNode(statementNumber), var(std::move(var)) {}

std::shared_ptr<VariableNode> ReadNode::getVar() {
    return var;
}

void ReadNode::accept(DesignExtractorVisitor &visitor) {
    visitor.visitReadNode();
}
