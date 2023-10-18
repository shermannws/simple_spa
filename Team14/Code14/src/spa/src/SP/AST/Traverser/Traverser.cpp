#include "Traverser.h"
#include "SP/AST/Nodes/IfNode.h"
#include "SP/AST/Nodes/ProcedureNode.h"
#include "SP/AST/Nodes/WhileNode.h"

Traverser::Traverser(std::vector<std::shared_ptr<DesignExtractorVisitor>> visitors) : visitors(visitors){};

void Traverser::traverse(std::shared_ptr<ProgramNode> root) {
    // DFS Algorithm where frontier is a stack
    // Execute DFS search algorithm with the program node as the root node

    // currentProcedure is used to keep track of the current procedure node
    std::shared_ptr<ProcedureNode> currentProcedure = nullptr;

    // Add the first node to the frontier
    frontier.push({root, {}});
    while (!frontier.empty()) {
        // get from top of stack as the current node
        std::shared_ptr<ASTNode> current = frontier.top().first;
        std::vector<std::shared_ptr<ASTNode>> parents = frontier.top().second;

        // pop the current node that is being worked on in this loop
        frontier.pop();

        if (auto currentCasted = std::dynamic_pointer_cast<ProcedureNode>(current)) {
            currentProcedure = currentCasted;
        }

        // current node to accept all the visitors and do its respective work
        for (std::shared_ptr<DesignExtractorVisitor> v: visitors) { current->accept(v, parents, currentProcedure); }

        // update parents vector if current node is a parent node
        std::vector<std::shared_ptr<ASTNode>> newParents = parents;
        if (auto currentCasted = std::dynamic_pointer_cast<IfNode>(current)) { newParents.emplace_back(currentCasted); }
        if (auto currentCasted = std::dynamic_pointer_cast<WhileNode>(current)) {
            newParents.emplace_back(currentCasted);
        }

        // add child of current node into the frontier
        std::vector<std::shared_ptr<ASTNode>> childrenOfCurrent = current->getAllChildNodes();
        // reverse iterator is used to add child from right to left
        for (auto it = childrenOfCurrent.rbegin(); it != childrenOfCurrent.rend(); it++) {
            frontier.push({*it, newParents});
        }
    }
};
