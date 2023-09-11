#include <stack>

#include "UsesExtractorVisitor.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"

UsesExtractorVisitor::UsesExtractorVisitor(std::shared_ptr<PkbWriter> writer) {
	this->pkbWriter = writer;
}

void UsesExtractorVisitor::visitAssignNode(std::shared_ptr<AssignNode> node) const {
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

void UsesExtractorVisitor::visitPrintNode(std::shared_ptr<PrintNode> node) const {
	this->pkbWriter->addUsesRelalationship(
		std::make_shared<Statement>(node->getStatementNumber(), StatementType::Print),
		std::make_shared<Variable>(node->getVar())
	);
}