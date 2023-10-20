#include "CallNode.h"

CallNode::CallNode(StatementNumber statementNumber, ProcedureName procedureName)
    : StatementNode(statementNumber), procedureName(std::move(procedureName)) {}

ProcedureName CallNode::getProcedureName() { return procedureName; }

std::vector<std::shared_ptr<ASTNode>> CallNode::getAllChildNodes() { return {}; }

StatementNodeType CallNode::getStatementType() { return StatementNodeType::Call; }

void CallNode::accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<Statement>> parents,
                      std::shared_ptr<Procedure> proc) {
    if (auto callVisitor = std::dynamic_pointer_cast<CallNodeVisitor>(visitor)) {
        callVisitor->visitCallNode(this, parents, proc);
    }
}