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

void ProcedureNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitProcedureNode();
}
