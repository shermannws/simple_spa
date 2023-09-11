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
    visitor.visitProcedureNode(std::make_shared<ProcedureNode>(this));
}

std::vector<std::shared_ptr<ASTNode>> ProcedureNode::getAllChildNodes() {
    std::vector<std::shared_ptr<ASTNode>> children { statementList };
    return children;
}