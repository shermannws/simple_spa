#include <stack>

#include "Commons/StatementFactory.h"
#include "SP/AST/Nodes/StatementNode.h"
#include "SP/AST/Nodes/VariableNode.h"
#include "VisitorUtility.h"

void VisitorUtility::addAllVariableRelationshipFrom(
        const std::shared_ptr<ASTNode> &root, const std::shared_ptr<Statement> &s,
        const std::vector<std::shared_ptr<Statement>> &parents,
        const std::function<void(std::shared_ptr<Statement>, std::shared_ptr<Variable>)> &funcStmt,
        const std::shared_ptr<Procedure> &proc,
        const std::function<void(std::shared_ptr<Procedure>, std::shared_ptr<Variable>)> &funcProc) {
    std::stack<std::shared_ptr<ASTNode>> frontier;
    frontier.push(root);

    while (!frontier.empty()) {
        std::shared_ptr<ASTNode> current = frontier.top();
        frontier.pop();

        auto ptr = std::dynamic_pointer_cast<VariableNode>(current);
        if (ptr) {
            // Add stmt-var relationships
            // Add direct relationship
            auto variable = std::make_shared<Variable>(ptr->getVarName());
            funcStmt(s, variable);
            // Add indirect relationships between parent and variable
            for (const auto &parent: parents) { funcStmt(parent, variable); }

            // Add proc-var relationships
            funcProc(proc, variable);
        }

        std::vector<std::shared_ptr<ASTNode>> childrenOfCurrent = current->getAllChildNodes();
        for (auto it = childrenOfCurrent.rbegin(); it != childrenOfCurrent.rend(); it++) { frontier.push(*it); }
    }
}