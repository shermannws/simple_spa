#include <utility>

#include "StatementListNode.h"

StatementListNode::StatementListNode(std::vector<std::shared_ptr<StatementNode>> statements)
        : statements(std::move((statements))) {}

std::vector<std::shared_ptr<StatementNode>> StatementListNode::getStatements() {
    return statements;
}

std::vector<std::shared_ptr<ASTNode>> StatementListNode::getAllChildNodes() {
    std::vector<std::shared_ptr<ASTNode>> children(statements.begin(), statements.end());
    return children;
}

void StatementListNode::accept(DesignExtractorVisitor& visitor) {
    if (auto statementListVisitor = dynamic_cast<StatementListNodeVisitor*>(&visitor)) {
        std::shared_ptr<StatementListNode> self(this);
        statementListVisitor->visitStatementListNode(self);
    }
}