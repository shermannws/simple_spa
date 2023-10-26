#pragma once

#include <memory>

#include "SP/AST/Nodes/ProgramNode.h"

class ASTGenerator {
public:
    // Helper method to generate AST from string source code
    static std::shared_ptr<ProgramNode> generate(std::string &s);
};