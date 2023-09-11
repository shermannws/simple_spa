#include <utility>

#include "PrintNode.h"

PrintNode::PrintNode(int statementNumber, std::shared_ptr<VariableNode> var)
        : StatementNode(statementNumber), var(std::move(var)) {}

std::shared_ptr<VariableNode> PrintNode::getVar() {
    return var;
}

void PrintNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitPrintNode();
}
