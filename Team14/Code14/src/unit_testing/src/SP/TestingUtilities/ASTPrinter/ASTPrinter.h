#pragma once
#pragma once

#include <memory>
#include <stack>

#include "Commons/Entities/Statement.h"
#include "SP/AST/Nodes/ASTNode.h"
#include "SP/AST/Nodes/ProgramNode.h"

class ASTPrinter {
private:
    /*!
     * Keeps a reference of pair of children nodes and their parents in a stack
     */
    std::stack<std::pair<std::shared_ptr<ASTNode>, std::vector<std::shared_ptr<Statement>>>> frontier;

public:
    /*!
     * Constructor for ASTPrinter.
     */
    ASTPrinter();

    /*!
     * Traverses the AST from the root ProgramNode.
     * @param root The root ProgramNode to start traversal from
     */
    void traverseAndPrint(std::shared_ptr<ProgramNode> root);
};