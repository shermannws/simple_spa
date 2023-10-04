#pragma once

#include <vector>

#include "ASTNode.h"
#include "ProcedureNode.h"

class ProgramNode; // forward declaration

/**
 * Visitor interface linked to ProgramNode, used to implement the Acyclic Visitor pattern.
 */
class ProgramNodeVisitor {
public:
    /**
     * Visits the ProgramNode for design extraction.
     * @param node ProgramNode to be visited
     * @param parents Parents of the ProgramNode
     * @param proc nullptr as ProgramNNode is not contained within a procedure
     */
    virtual void visitProgramNode(ProgramNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const = 0;
};

/**
 * ASTNode to represent a program.
 * This is the type of the root node of the AST.
 */
class ProgramNode : public ASTNode {
private:
    /**
     * The vector of procedures in the program.
     */
    std::vector<std::shared_ptr<ProcedureNode>> procedures;

public:
    /**
     * Creates and initializes a ProgramNode.
     * @param procedures The procedures in the program
     */
    explicit ProgramNode(std::vector<std::shared_ptr<ProcedureNode>> procedures);

    /**
     * Returns a vector of procedures in the program.
     * @return A vector of procedures in the program
     */
    std::vector<std::shared_ptr<ProcedureNode>> getProcedures();

    void accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) override;

    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
};
