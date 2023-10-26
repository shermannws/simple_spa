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
#include "Commons/EntityFactory.h"
#include "EntityExtractorVisitor.h"

EntityExtractorVisitor::EntityExtractorVisitor(std::shared_ptr<PkbWriter> writer) { this->pkbWriter = writer; }

void EntityExtractorVisitor::visitProcedureNode(const std::shared_ptr<ProcedureNode> &node,
                                                std::vector<std::shared_ptr<Statement>> parents,
                                                std::shared_ptr<Procedure> proc) const {
    this->pkbWriter->addProcedure(EntityFactory::createProcedure(node->getProcedureName()));
}

void EntityExtractorVisitor::visitAssignNode(const std::shared_ptr<AssignNode> &node,
                                             std::vector<std::shared_ptr<Statement>> parents,
                                             std::shared_ptr<Procedure> proc) const {
    auto currentStmt = EntityFactory::createStatementFromStatementNode(node);

    this->pkbWriter->addAssignStatement(currentStmt);
}

void EntityExtractorVisitor::visitReadNode(const std::shared_ptr<ReadNode> &node,
                                           std::vector<std::shared_ptr<Statement>> parents,
                                           std::shared_ptr<Procedure> proc) const {
    this->pkbWriter->addReadStatement(EntityFactory::createStatementFromStatementNode(node));
}

void EntityExtractorVisitor::visitPrintNode(const std::shared_ptr<PrintNode> &node,
                                            std::vector<std::shared_ptr<Statement>> parents,
                                            std::shared_ptr<Procedure> proc) const {
    this->pkbWriter->addPrintStatement(EntityFactory::createStatementFromStatementNode(node));
}

void EntityExtractorVisitor::visitVariableNode(const std::shared_ptr<VariableNode> &node,
                                               std::vector<std::shared_ptr<Statement>> parents,
                                               std::shared_ptr<Procedure> proc) const {
    this->pkbWriter->addVariable(EntityFactory::createVariable(node->getVarName()));
}

void EntityExtractorVisitor::visitConstantNode(const std::shared_ptr<ConstantNode> &node,
                                               std::vector<std::shared_ptr<Statement>> parents,
                                               std::shared_ptr<Procedure> proc) const {
    this->pkbWriter->addConstant(EntityFactory::createConstant(node->getValue()));
}

void EntityExtractorVisitor::visitCallNode(const std::shared_ptr<CallNode> &node,
                                           std::vector<std::shared_ptr<Statement>> parents,
                                           std::shared_ptr<Procedure> proc) const {
    this->pkbWriter->addCallStatement(EntityFactory::createStatementFromStatementNode(node));
}

void EntityExtractorVisitor::visitIfNode(const std::shared_ptr<IfNode> &node,
                                         std::vector<std::shared_ptr<Statement>> parents,
                                         std::shared_ptr<Procedure> proc) const {
    this->pkbWriter->addIfStatement(EntityFactory::createStatementFromStatementNode(node));
}

void EntityExtractorVisitor::visitWhileNode(const std::shared_ptr<WhileNode> &node,
                                            std::vector<std::shared_ptr<Statement>> parents,
                                            std::shared_ptr<Procedure> proc) const {
    this->pkbWriter->addWhileStatement(EntityFactory::createStatementFromStatementNode(node));
}
