#include <utility>

#include "ProcedureNode.h"

ProcedureNode::ProcedureNode(std::string procedureName, std::shared_ptr<StatementListNode> statementList)
        : procedureName(std::move(procedureName)), statementList(std::move(statementList)) {}

void ProcedureNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitProcedureNode();
}
