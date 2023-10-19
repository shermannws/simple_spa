#include "UsesExtractorVisitor.h"
#include "Commons/Entities/AssignStatement.h"
#include "Commons/Entities/IfStatement.h"
#include "Commons/Entities/PrintStatement.h"
#include "Commons/Entities/Procedure.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "Commons/Entities/WhileStatement.h"
#include "VisitorUtility.h"

UsesExtractorVisitor::UsesExtractorVisitor(std::shared_ptr<PkbWriter> writer) {
    this->pkbWriter = writer;
    this->funcStmt = [this](std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) -> void {
        this->pkbWriter->addUsesRelationship(s, v);
    };
    this->funcProc = [this](std::shared_ptr<Procedure> p, std::shared_ptr<Variable> v) -> void {
        this->pkbWriter->addUsesProcRelationship(p, v);
    };
}

void UsesExtractorVisitor::visitAssignNode(const std::shared_ptr<AssignNode> &node,
                                           std::vector<std::shared_ptr<ASTNode>> parents,
                                           std::shared_ptr<ASTNode> proc) const {
    return VisitorUtility::addAllVariableRelationshipFrom(node->getExpression(),
                                                          std::make_shared<AssignStatement>(node->getStatementNumber()),
                                                          parents, this->funcStmt, proc, this->funcProc);
}

void UsesExtractorVisitor::visitPrintNode(const std::shared_ptr<PrintNode> &node,
                                          std::vector<std::shared_ptr<ASTNode>> parents,
                                          std::shared_ptr<ASTNode> proc) const {
    return VisitorUtility::addAllVariableRelationshipFrom(
            node->getVar(), std::make_shared<PrintStatement>(node->getStatementNumber(), node->getVar()->getVarName()),
            parents, this->funcStmt, proc, this->funcProc);
}

void UsesExtractorVisitor::visitIfNode(const std::shared_ptr<IfNode> &node,
                                       std::vector<std::shared_ptr<ASTNode>> parents,
                                       std::shared_ptr<ASTNode> proc) const {
    return VisitorUtility::addAllVariableRelationshipFrom(node->getConditionalExpression(),
                                                          std::make_shared<IfStatement>(node->getStatementNumber()),
                                                          parents, this->funcStmt, proc, this->funcProc);
}

void UsesExtractorVisitor::visitWhileNode(const std::shared_ptr<WhileNode> &node,
                                          std::vector<std::shared_ptr<ASTNode>> parents,
                                          std::shared_ptr<ASTNode> proc) const {
    return VisitorUtility::addAllVariableRelationshipFrom(node->getConditionalExpression(),
                                                          std::make_shared<WhileStatement>(node->getStatementNumber()),
                                                          parents, this->funcStmt, proc, this->funcProc);
}