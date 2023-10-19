#include <utility>

#include "StatementListNode.h"

StatementListNode::StatementListNode(std::vector<std::shared_ptr<StatementNode>> statements)
    : statements(std::move(statements)) {}

std::vector<std::shared_ptr<StatementNode>> StatementListNode::getStatements() { return statements; }

std::vector<std::shared_ptr<ASTNode>> StatementListNode::getAllChildNodes() {
    std::vector<std::shared_ptr<ASTNode>> children(statements.begin(), statements.end());
    return children;
}

void StatementListNode::accept(std::shared_ptr<DesignExtractorVisitor> visitor,
                               std::vector<std::shared_ptr<Statement>> parents, std::shared_ptr<ASTNode> proc) {
    if (auto statementListVisitor = std::dynamic_pointer_cast<StatementListNodeVisitor>(visitor)) {
        statementListVisitor->visitStatementListNode(this, parents, proc);
    }
}