#include <string>

#include "Commons/AppConstants.h"
#include "EntityExtractorVisitor.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Constant.h"
#include "Commons/Entities/Variable.h"
#include "Commons/Entities/Procedure.h"

EntityExtractorVisitor::EntityExtractorVisitor(std::shared_ptr<PkbWriter> writer) {
	this->pkbWriter = writer;
}

void EntityExtractorVisitor::visitProcedureNode(ProcedureNode *node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const {
	this->pkbWriter->addProcedure(std::make_shared<Procedure>(node->getProcedureName()));
}

void EntityExtractorVisitor::visitAssignNode(AssignNode *node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const {
	this->pkbWriter->addAssignStatement(
			std::make_shared<Statement>(node->getStatementNumber(), StatementType::Assign),
			std::make_shared<Variable>(node->getVar()->getVarName()),
			std::make_shared<FormattedExpression>(node->getExpression()->toString()));
}

void EntityExtractorVisitor::visitReadNode(ReadNode *node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const {
	this->pkbWriter->addReadStatement(std::make_shared<Statement>(node->getStatementNumber(), StatementType::Read));
}

void EntityExtractorVisitor::visitPrintNode(PrintNode *node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const {
	this->pkbWriter->addPrintStatement(std::make_shared<Statement>(node->getStatementNumber(), StatementType::Print));
}

void EntityExtractorVisitor::visitVariableNode(VariableNode *node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const {
	this->pkbWriter->addVariable(std::make_shared<Variable>(node->getVarName()));
}

void EntityExtractorVisitor::visitConstantNode(ConstantNode *node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const {
	this->pkbWriter->addConstant(std::make_shared<Constant>(node->getValue()));
}

void EntityExtractorVisitor::visitCallNode(CallNode *node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const {
	this->pkbWriter->addCallStatement(std::make_shared<Statement>(node->getStatementNumber(), StatementType::Call));
}

void EntityExtractorVisitor::visitIfNode(IfNode *node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const {
	this->pkbWriter->addIfStatement(std::make_shared<Statement>(node->getStatementNumber(), StatementType::If));
}

void EntityExtractorVisitor::visitWhileNode(WhileNode *node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const {
	this->pkbWriter->addWhileStatement(std::make_shared<Statement>(node->getStatementNumber(), StatementType::While));
}
