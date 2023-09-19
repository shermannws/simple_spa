#include <stack>

#include "UsesExtractorVisitor.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"

UsesExtractorVisitor::UsesExtractorVisitor(std::shared_ptr<PkbWriter> writer) {
	this->pkbWriter = writer;
}

void UsesExtractorVisitor::visitAssignNode(AssignNode* node) const {
	std::shared_ptr<ExpressionNode> root = node->getExpression();
	std::stack<std::shared_ptr<ASTNode>> frontier;
	frontier.push(root);

	while (!frontier.empty()) {
		std::shared_ptr<ASTNode> current = frontier.top();
		frontier.pop();

		VariableNode* ptr = dynamic_cast<VariableNode*>(current.get());
		if (ptr) {
			this->pkbWriter->addUsesRelationship(
				std::make_shared<Statement>(node->getStatementNumber(), StatementType::Assign),
				std::make_shared<Variable>(ptr->getVarName()));
		}

		std::vector<std::shared_ptr<ASTNode>> childrenOfCurrent = current->getAllChildNodes();
		for (auto it = childrenOfCurrent.rbegin(); it != childrenOfCurrent.rend(); it++) {
			frontier.push(*it);
		}
	}
}

void UsesExtractorVisitor::visitPrintNode(PrintNode* node) const {
	this->pkbWriter->addUsesRelationship(
		std::make_shared<Statement>(node->getStatementNumber(), StatementType::Print),
		std::make_shared<Variable>(node->getVar()->getVarName())
	);
}