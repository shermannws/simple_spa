#include <utility>

#include "StatementListNode.h"

StatementListNode::StatementListNode(std::vector<std::shared_ptr<StatementNode>> statements)
        : statements(std::move((statements))) {}

void StatementListNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitStatementListNode();
}
