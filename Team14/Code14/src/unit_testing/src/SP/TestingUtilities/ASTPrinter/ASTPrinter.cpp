#include <iostream>

#include "ASTPrinter.h"
#include "ASTPrinterVisitor.h"
#include "PKB/PkbWriter.h"

ASTPrinter::ASTPrinter() {}

void ASTPrinter::traverseAndPrint(std::shared_ptr<ProgramNode> root) {
    std::shared_ptr<PkbWriter> writer;
    std::shared_ptr<ASTPrinterVisitor> visitor = std::make_shared<ASTPrinterVisitor>(writer);
    // DFS Algorithm where frontier is a stack
    // Execute DFS search algorithm with the program node as the root node

    // Add the first node to the frontier
    frontier.push({root, {}});
    while (!frontier.empty()) {
        // get from top of stack as the current node
        auto [current, parents] = frontier.top();

        // pop the current node that is being worked on in this loop
        frontier.pop();

        int indentLevel = parents.size();
        for (int i = 0; i < indentLevel; i++) { std::cout << "│  "; }

        std::string endSymbol = (!frontier.empty() && indentLevel <= frontier.top().second.size()) ? "├──" : "└──";
        std::cout << endSymbol;
        // current node to accept visitor
        current->accept(visitor, parents, nullptr);

        std::vector<std::shared_ptr<ASTNode>> newParents = parents;
        newParents.emplace_back(current);

        // add child of current node into the frontier
        std::vector<std::shared_ptr<ASTNode>> childrenOfCurrent = current->getAllChildNodes();
        // reverse iterator is used to add child from right to left
        for (auto it = childrenOfCurrent.rbegin(); it != childrenOfCurrent.rend(); it++) {
            frontier.emplace(*it, newParents);
        }
    }
};
