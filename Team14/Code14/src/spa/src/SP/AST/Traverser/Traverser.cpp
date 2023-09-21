#pragma once

#include "Traverser.h"

Traverser::Traverser(std::vector<std::shared_ptr<DesignExtractorVisitor>> visitors) : visitors(visitors) {};

void Traverser::traverse(std::shared_ptr<ProgramNode> root) {
	//DFS Algorithm where frontier is a stack
	//Execute DFS search algorithm with the program node as the root node

	//Add the first node to the frontier
	frontier.push(root);
	while (!frontier.empty()) {
		//get from top of stack as the current node
		std::shared_ptr<ASTNode> current = frontier.top();

		//pop the current node that is being worked on in this loop
		frontier.pop();

		//current node to accept all the visitors and do its respective workr
		for (std::shared_ptr<DesignExtractorVisitor> v : visitors) {
			current->accept(v);
		}

		//add child of current node into the frontier
		std::vector<std::shared_ptr<ASTNode>> childrenOfCurrent = current->getAllChildNodes();
		//reverse iterator is used to add child from right to left
		for (auto it = childrenOfCurrent.rbegin(); it != childrenOfCurrent.rend(); it++) {
			frontier.push(*it);
		}
	}
};
