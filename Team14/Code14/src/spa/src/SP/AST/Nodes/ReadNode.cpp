#include <utility>

#include "ReadNode.h"

ReadNode::ReadNode(int statementNumber, std::shared_ptr<VariableNode> var)
        : StatementNode(statementNumber), var(std::move(var)) {}

std::shared_ptr<VariableNode> ReadNode::getVar() {
    return var;
}

std::vector<std::shared_ptr<ASTNode>> ReadNode::getAllChildNodes() {
    std::vector<std::shared_ptr<ASTNode>> children { var };
    return children;
}

StatementNodeType ReadNode::getStatementType() {
    return StatementNodeType::Read;
}

void ReadNode::accept(DesignExtractorVisitor& visitor) {
    if (auto readVisitor = dynamic_cast<ReadNodeVisitor*>(&visitor)) {
        std::shared_ptr<ReadNode> self(this);
        readVisitor->visitReadNode(self);
    }
}