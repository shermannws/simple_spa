#include <utility>

#include "ReadNode.h"

ReadNode::ReadNode(int statementNumber, std::shared_ptr<VariableNode> var)
        : StatementNode(statementNumber), var(std::move(var)) {}

void ReadNode::accept(DesignExtractorVisitor &visitor) {
    visitor.visitReadNode();
}
