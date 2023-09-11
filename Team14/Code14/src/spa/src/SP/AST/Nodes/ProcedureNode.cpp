#include <utility>

#include "ProcedureNode.h"

ProcedureNode::ProcedureNode(std::string procedureName, std::shared_ptr<StatementListNode> statementList)
        : procedureName(std::move(procedureName)), statementList(std::move(statementList)) {}

std::string ProcedureNode::getProcedureName() {
    return procedureName;
}

std::shared_ptr<StatementListNode> ProcedureNode::getStatementList() {
    return statementList;
}

std::vector<std::shared_ptr<ASTNode>> ProcedureNode::getAllChildNodes() {
    std::vector<std::shared_ptr<ASTNode>> children { statementList };
    return children;
}

void ProcedureNode::accept(std::shared_ptr<DesignExtractorVisitor> visitor) {
    if (auto procedureVisitor = std::dynamic_pointer_cast<ProcedureNodeVisitor>(visitor)) {
        std::shared_ptr<ProcedureNode> self(this);
        procedureVisitor->visitProcedureNode(self);
    }
}