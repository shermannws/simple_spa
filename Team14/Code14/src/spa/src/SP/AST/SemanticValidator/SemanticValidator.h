#pragma once

#include <memory>
#include <stack>
#include <set>

#include "SP/AST/Nodes/ASTNode.h"
#include "SP/AST/Nodes/ProgramNode.h"

class SemanticValidator {
private:
    std::stack<std::shared_ptr<ASTNode>> frontier;

public:
    SemanticValidator();
    void validate(std::shared_ptr<ProgramNode> root);
};
