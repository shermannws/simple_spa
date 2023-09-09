#include "StatementListNode.h"

void StatementListNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitStatementListNode();
}
