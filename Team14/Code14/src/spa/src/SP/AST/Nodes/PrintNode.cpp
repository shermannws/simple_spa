#include <utility>

#include "PrintNode.h"

PrintNode::PrintNode(StatementNumber statementNumber, std::shared_ptr<VariableNode> var)
        : StatementNode(statementNumber), var(std::move(var)) {}

std::shared_ptr<VariableNode> PrintNode::getVar() {
    return var;
}

std::vector<std::shared_ptr<ASTNode>> PrintNode::getAllChildNodes() {
    std::vector<std::shared_ptr<ASTNode>> children { var };
    return children;
}

StatementNodeType PrintNode::getStatementType() {
    return StatementNodeType::Print;
}

void PrintNode::accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) {
    if (auto printVisitor = std::dynamic_pointer_cast<PrintNodeVisitor>(visitor)) {
        printVisitor->visitPrintNode(this, parents, proc);
    }
}