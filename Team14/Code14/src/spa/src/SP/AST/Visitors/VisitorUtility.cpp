#include <stack>

#include "VisitorUtility.h"
#include "SP/AST/Nodes/VariableNode.h"

void VisitorUtility::addAllStatementVariableRelationshipFrom(
	std::shared_ptr<ASTNode> root,
	Statement s,
	std::function<void(std::shared_ptr<Statement>, std::shared_ptr<Variable>)> func
) {
	std::stack<std::shared_ptr<ASTNode>> frontier;
	frontier.push(root);

	while (!frontier.empty()) {
		std::shared_ptr<ASTNode> current = frontier.top();
		frontier.pop();

		VariableNode* ptr = dynamic_cast<VariableNode*>(current.get());
		if (ptr) {
			func(std::make_shared<Statement>(s), std::make_shared<Variable>(ptr->getVarName()));
		}

		std::vector<std::shared_ptr<ASTNode>> childrenOfCurrent = current->getAllChildNodes();
		for (auto it = childrenOfCurrent.rbegin(); it != childrenOfCurrent.rend(); it++) {
			frontier.push(*it);
		}
	}
}