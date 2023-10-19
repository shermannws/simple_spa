#include <utility>

#include "ProcedureNode.h"

ProcedureNode::ProcedureNode(ProcedureName procedureName, std::shared_ptr<StatementListNode> statementList)
    : procedureName(std::move(procedureName)), statementList(std::move(statementList)) {}

ProcedureName ProcedureNode::getProcedureName() { return procedureName; }

std::shared_ptr<StatementListNode> ProcedureNode::getStatementList() { return statementList; }

std::vector<std::shared_ptr<ASTNode>> ProcedureNode::getAllChildNodes() {
    std::vector<std::shared_ptr<ASTNode>> children{statementList};
    return children;
}

void ProcedureNode::accept(std::shared_ptr<DesignExtractorVisitor> visitor,
                           std::vector<std::shared_ptr<Statement>> parents, std::shared_ptr<Procedure> proc) {
    if (auto procedureVisitor = std::dynamic_pointer_cast<ProcedureNodeVisitor>(visitor)) {
        procedureVisitor->visitProcedureNode(this, parents, proc);
    }
}