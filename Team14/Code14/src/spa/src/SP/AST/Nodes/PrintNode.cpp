#include "PrintNode.h"

PrintNode::PrintNode(int statementNumber) : StatementNode(statementNumber) {}

void PrintNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitPrintNode();
}
