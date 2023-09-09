#include "AssignNode.h"

AssignNode::AssignNode(int statementNumber) : StatementNode(statementNumber){}

void AssignNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitAssignNode();
}
