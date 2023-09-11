#include <utility>

#include "ReadNode.h"

ReadNode::ReadNode(int statementNumber, std::shared_ptr<VariableNode> var)
        : StatementNode(statementNumber), var(std::move(var)) {}

std::shared_ptr<VariableNode> ReadNode::getVar() {
    return var;
}

void ReadNode::accept(DesignExtractorVisitor &visitor) {
    visitor.visitReadNode(std::make_shared<ReadNode>(this));
}

std::vector<std::shared_ptr<ASTNode>> ReadNode::getAllChildNodes() {
    std::vector<std::shared_ptr<ASTNode>> children { var };
    return children;
}