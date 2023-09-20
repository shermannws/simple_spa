#pragma once

#include "DesignExtractorVisitor.h"
#include "../../AST/Nodes/AssignNode.h"
#include "../../AST/Nodes/PrintNode.h"
#include "../../AST/Nodes/IfNode.h"
#include "../../AST/Nodes/WhileNode.h"

class UsesExtractorVisitor : public DesignExtractorVisitor,
    public AssignNodeVisitor,
    public PrintNodeVisitor,
    public IfNodeVisitor,
    public WhileNodeVisitor
{
public:
    /*!
     * Constructor for UsesExtractorVisitor
     */
    UsesExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter);

    /*!
     * Visits an AssignNode and add variables used by the Assignment into PKB
     */
    void visitAssignNode(AssignNode* node, std::vector<std::shared_ptr<ASTNode>> parents) const override;

    /*!
     * Visits a PrintNode and add variable used into PKB
     */
    void visitPrintNode(PrintNode* node, std::vector<std::shared_ptr<ASTNode>> parents) const override;

    /*!
     * Visits an IfNode and add variable used into PKB
     */
    void visitIfNode(IfNode* node, std::vector<std::shared_ptr<ASTNode>> parents) const override;

    /*!
     * Visits a PrintNode and add variable used into PKB
     */
    void visitWhileNode(WhileNode* node, std::vector<std::shared_ptr<ASTNode>> parents) const override;
};
