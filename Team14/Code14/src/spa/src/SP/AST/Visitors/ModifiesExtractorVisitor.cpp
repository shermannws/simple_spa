#include <functional>

#include "Commons/Entities/AssignStatement.h"
#include "Commons/Entities/ReadStatement.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "Commons/EntityFactory.h"
#include "ModifiesExtractorVisitor.h"
#include "VisitorUtility.h"

ModifiesExtractorVisitor::ModifiesExtractorVisitor(std::shared_ptr<PkbWriter> writer) {
    StmtVarFunc funcStmt = [this](std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) -> void {
        this->pkbWriter->addModifiesRelationship(s, v);
    };
    ProcVarFunc funcProc = [this](std::shared_ptr<Procedure> p, std::shared_ptr<Variable> v) -> void {
        this->pkbWriter->addModifiesProcRelationship(p, v);
    };

    this->pkbWriter = writer;
    this->visitorUtils = VisitorUtility(funcStmt, funcProc);
}

void ModifiesExtractorVisitor::visitAssignNode(const std::shared_ptr<AssignNode> &node,
                                               std::vector<std::shared_ptr<Statement>> parents,
                                               std::shared_ptr<Procedure> proc) const {
    VisitorUtilsParams params = VisitorUtilsParams(node->getVar());
    params.setStatement(EntityFactory::createStatementFromStatementNode(node));
    params.setParents(parents);
    params.setProcedure(proc);
    return this->visitorUtils.addAllVariableRelationship(params);
}

void ModifiesExtractorVisitor::visitReadNode(const std::shared_ptr<ReadNode> &node,
                                             std::vector<std::shared_ptr<Statement>> parents,
                                             std::shared_ptr<Procedure> proc) const {
    VisitorUtilsParams params = VisitorUtilsParams(node->getVar());
    params.setStatement(EntityFactory::createStatementFromStatementNode(node));
    params.setParents(parents);
    params.setProcedure(proc);
    return this->visitorUtils.addAllVariableRelationship(params);
}
