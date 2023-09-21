#include "CallNode.h"

CallNode::CallNode(int statementNumber, std::string procedureName)
        : StatementNode(statementNumber), procedureName(std::move(procedureName)) {}

std::string CallNode::getProcedureName() {
    return procedureName;
}

std::vector<std::shared_ptr<ASTNode>> CallNode::getAllChildNodes() {
    return {};
}

StatementNodeType CallNode::getStatementType() {
    return StatementNodeType::Call;
}

void CallNode::accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents) {
    if (auto callVisitor = std::dynamic_pointer_cast<CallNodeVisitor>(visitor)) {
        callVisitor->visitCallNode(this, parents);
    }
}