#include "UsesExtractorVisitor.h"
#include "Commons/Entities/AssignStatement.h"
#include "Commons/Entities/IfStatement.h"
#include "Commons/Entities/PrintStatement.h"
#include "Commons/Entities/Procedure.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "Commons/Entities/WhileStatement.h"
#include "Commons/EntityFactory.h"

UsesExtractorVisitor::UsesExtractorVisitor(std::shared_ptr<PkbWriter> writer) {
    StmtVarFunc funcStmt = [this](std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) -> void {
        this->pkbWriter->addUsesRelationship(s, v);
    };
    ProcVarFunc funcProc = [this](std::shared_ptr<Procedure> p, std::shared_ptr<Variable> v) -> void {
        this->pkbWriter->addUsesProcRelationship(p, v);
    };

    this->pkbWriter = writer;
    this->visitorUtils = VisitorUtility(funcStmt, funcProc);
}

void UsesExtractorVisitor::visitAssignNode(const std::shared_ptr<AssignNode> &node,
                                           std::vector<std::shared_ptr<Statement>> parents,
                                           std::shared_ptr<Procedure> proc) const {
    VisitorUtilsParams params = VisitorUtilsParams(node->getExpression());
    params.setStatement(EntityFactory::createStatementFromStatementNode(node));
    params.setParents(parents);
    params.setProcedure(proc);
    return this->visitorUtils.addAllVariableRelationshipFrom(params);
}

void UsesExtractorVisitor::visitPrintNode(const std::shared_ptr<PrintNode> &node,
                                          std::vector<std::shared_ptr<Statement>> parents,
                                          std::shared_ptr<Procedure> proc) const {
    VisitorUtilsParams params = VisitorUtilsParams(node->getVar());
    params.setStatement(EntityFactory::createStatementFromStatementNode(node));
    params.setParents(parents);
    params.setProcedure(proc);
    return this->visitorUtils.addAllVariableRelationshipFrom(params);
}

void UsesExtractorVisitor::visitIfNode(const std::shared_ptr<IfNode> &node,
                                       std::vector<std::shared_ptr<Statement>> parents,
                                       std::shared_ptr<Procedure> proc) const {
    VisitorUtilsParams params = VisitorUtilsParams(node->getConditionalExpression());
    params.setStatement(EntityFactory::createStatementFromStatementNode(node));
    params.setParents(parents);
    params.setProcedure(proc);
    return this->visitorUtils.addAllVariableRelationshipFrom(params);
}

void UsesExtractorVisitor::visitWhileNode(const std::shared_ptr<WhileNode> &node,
                                          std::vector<std::shared_ptr<Statement>> parents,
                                          std::shared_ptr<Procedure> proc) const {
    VisitorUtilsParams params = VisitorUtilsParams(node->getConditionalExpression());
    params.setStatement(EntityFactory::createStatementFromStatementNode(node));
    params.setParents(parents);
    params.setProcedure(proc);
    return this->visitorUtils.addAllVariableRelationshipFrom(params);
}