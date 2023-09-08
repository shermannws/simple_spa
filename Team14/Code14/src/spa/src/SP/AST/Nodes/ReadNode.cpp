#include "ReadNode.h"

ReadNode::ReadNode(int statementNumber) : StatementNode(statementNumber) {}

void ReadNode::accept(DesignExtractorVisitor &visitor) {
    visitor.visitReadNode();
}
