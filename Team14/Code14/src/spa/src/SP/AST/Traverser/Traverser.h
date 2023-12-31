#pragma once

#include <memory>
#include <stack>

#include "SP/AST/Nodes/ASTNode.h"
#include "SP/AST/Nodes/ProgramNode.h"
#include "SP/AST/Visitors/DesignExtractorVisitor.h"

class Traverser {
private:
    std::vector<std::shared_ptr<DesignExtractorVisitor>> visitors;

    /*!
     * Keeps a reference of pair of children nodes and their parents in a stack
     */
    std::stack<std::pair<std::shared_ptr<ASTNode>, std::vector<std::shared_ptr<Statement>>>> frontier;

public:
    /*!
     * Constructor for Traverser which takes in a vector of Visitor Object.
     * @param visitors A vector of DesignExtractorVisitor that will each visit the AST Node as it is being traversed
     */
    Traverser(std::vector<std::shared_ptr<DesignExtractorVisitor>> visitors);

    /*!
     * Traverses the AST from the root ProgramNode.
     * @param root The root ProgramNode to start traversal from
     */
    void traverse(std::shared_ptr<ProgramNode> root);
};