#pragma once

#include <memory>
#include <stack>

#include "SP/AST/Visitors/DesignExtractorVisitor.h"
#include "SP/AST/Nodes/ASTNode.h"
#include "SP/AST/Nodes/ProgramNode.h"

class Traverser {
private:
	std::vector<std::shared_ptr<DesignExtractorVisitor>> visitors;
	std::stack<std::shared_ptr<ASTNode>> frontier;

public:
	Traverser(std::vector<std::shared_ptr<DesignExtractorVisitor>> visitors);
	void traverse(std::shared_ptr<ProgramNode> root);
};