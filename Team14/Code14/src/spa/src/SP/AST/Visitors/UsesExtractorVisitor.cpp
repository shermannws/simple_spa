#include <stack>

#include "UsesExtractorVisitor.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"

UsesExtractorVisitor::UsesExtractorVisitor(std::shared_ptr<PkbWriter> writer) {
	this->pkbWriter = writer;
}

void UsesExtractorVisitor::visitProgramNode(std::shared_ptr<ProgramNode> node) {}

void UsesExtractorVisitor::visitProcedureNode(std::shared_ptr<ProcedureNode> node) {}

void UsesExtractorVisitor::visitStatementListNode(std::shared_ptr<StatementListNode> node) {}

void UsesExtractorVisitor::visitAssignNode(std::shared_ptr<AssignNode> node) {
	std::shared_ptr<ExpressionNode> root = node->getExpression();
	std::stack<std::shared_ptr<ASTNode>> frontier;
	frontier.push(root);

	while (!frontier.empty()) {
		std::shared_ptr<ASTNode> current = frontier.top();

		//main logic
		VariableNode* ptr = dynamic_cast<VariableNode*>(current.get());
		if (ptr) {
			this->pkbWriter->addUsesRelalationship(
				std::make_shared<Statement>(node->getStatementNumber(), StatementType::Assign),
				std::make_shared<Variable>(ptr->getVarName()));
		}

		std::vector<std::shared_ptr<ASTNode>> childreOfCurrent = current->getAllChildNodes();
		for (auto it = childreOfCurrent.rbegin(); it != childreOfCurrent.rend(); it++) {
			frontier.push(*it);
		}

		frontier.pop();
	}
}

void UsesExtractorVisitor::visitReadNode(std::shared_ptr<ReadNode> node) {}

void UsesExtractorVisitor::visitPrintNode(std::shared_ptr<PrintNode> node) {
	this->pkbWriter->addUsesRelalationship(
		std::make_shared<Statement>(node->getStatementNumber(), StatementType::Print),
		std::make_shared<Variable>(node->getVar())
	);
}

void UsesExtractorVisitor::visitArithmeticExpressionNode(std::shared_ptr<ArithmeticExpressionNode> node) {}

void UsesExtractorVisitor::visitVariableNode(std::shared_ptr<VariableNode> node) {}

void UsesExtractorVisitor::visitConstantNode(std::shared_ptr<ConstantNode> node) {}