#include <string>

#include "Commons/Entities/AssignStatement.h"
#include "Commons/Entities/CallStatement.h"
#include "Commons/Entities/Constant.h"
#include "Commons/Entities/IfStatement.h"
#include "Commons/Entities/PrintStatement.h"
#include "Commons/Entities/Procedure.h"
#include "Commons/Entities/ReadStatement.h"
#include "Commons/Entities/Variable.h"
#include "Commons/Entities/WhileStatement.h"
#include "EntityExtractorVisitor.h"

EntityExtractorVisitor::EntityExtractorVisitor(std::shared_ptr<PkbWriter> writer) { this->pkbWriter = writer; }

void EntityExtractorVisitor::visitProcedureNode(const std::shared_ptr<ProcedureNode> &node,
                                                std::vector<std::shared_ptr<ASTNode>> parents,
                                                std::shared_ptr<ASTNode> proc) const {
    this->pkbWriter->addProcedure(std::make_shared<Procedure>(node->getProcedureName()));
}

void EntityExtractorVisitor::visitAssignNode(const std::shared_ptr<AssignNode> &node,
                                             std::vector<std::shared_ptr<ASTNode>> parents,
                                             std::shared_ptr<ASTNode> proc) const {
    auto currentStmt = std::make_shared<AssignStatement>(node->getStatementNumber());

    this->pkbWriter->addAssignStatement(currentStmt);
}

void EntityExtractorVisitor::visitReadNode(const std::shared_ptr<ReadNode> &node,
                                           std::vector<std::shared_ptr<ASTNode>> parents,
                                           std::shared_ptr<ASTNode> proc) const {
    this->pkbWriter->addReadStatement(
            std::make_shared<ReadStatement>(node->getStatementNumber(), node->getVar()->getVarName()));
}

void EntityExtractorVisitor::visitPrintNode(const std::shared_ptr<PrintNode> &node,
                                            std::vector<std::shared_ptr<ASTNode>> parents,
                                            std::shared_ptr<ASTNode> proc) const {
    this->pkbWriter->addPrintStatement(
            std::make_shared<PrintStatement>(node->getStatementNumber(), node->getVar()->getVarName()));
}

void EntityExtractorVisitor::visitVariableNode(const std::shared_ptr<VariableNode> &node,
                                               std::vector<std::shared_ptr<ASTNode>> parents,
                                               std::shared_ptr<ASTNode> proc) const {
    this->pkbWriter->addVariable(std::make_shared<Variable>(node->getVarName()));
}

void EntityExtractorVisitor::visitConstantNode(const std::shared_ptr<ConstantNode> &node,
                                               std::vector<std::shared_ptr<ASTNode>> parents,
                                               std::shared_ptr<ASTNode> proc) const {
    this->pkbWriter->addConstant(std::make_shared<Constant>(node->getValue()));
}

void EntityExtractorVisitor::visitCallNode(const std::shared_ptr<CallNode> &node,
                                           std::vector<std::shared_ptr<ASTNode>> parents,
                                           std::shared_ptr<ASTNode> proc) const {
    this->pkbWriter->addCallStatement(
            std::make_shared<CallStatement>(node->getStatementNumber(), node->getProcedureName()));
}

void EntityExtractorVisitor::visitIfNode(const std::shared_ptr<IfNode> &node,
                                         std::vector<std::shared_ptr<ASTNode>> parents,
                                         std::shared_ptr<ASTNode> proc) const {
    this->pkbWriter->addIfStatement(std::make_shared<IfStatement>(node->getStatementNumber()));
}

void EntityExtractorVisitor::visitWhileNode(const std::shared_ptr<WhileNode> &node,
                                            std::vector<std::shared_ptr<ASTNode>> parents,
                                            std::shared_ptr<ASTNode> proc) const {
    this->pkbWriter->addWhileStatement(std::make_shared<WhileStatement>(node->getStatementNumber()));
}
