#include <utility>

#include "StatementListNode.h"

StatementListNode::StatementListNode(std::vector<std::shared_ptr<StatementNode>> statements)
        : statements(std::move((statements))) {}

std::vector<std::shared_ptr<StatementNode>> StatementListNode::getStatements() {
    return statements;
}

void StatementListNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitStatementListNode(std::make_shared<StatementListNode>(this));
}

std::vector<std::shared_ptr<ASTNode>> StatementListNode::getAllChildNodes() {
    std::vector<std::shared_ptr<ASTNode>> children(statements.begin(), statements.end());
    return children;
}