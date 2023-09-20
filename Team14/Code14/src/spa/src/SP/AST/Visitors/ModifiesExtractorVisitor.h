#pragma once

#include "DesignExtractorVisitor.h"
#include "../../AST/Nodes/AssignNode.h"
#include "../../AST/Nodes/ReadNode.h"

class ModifiesExtractorVisitor : public DesignExtractorVisitor,
    public AssignNodeVisitor,
    public ReadNodeVisitor
{
public:
    /*!
     * Constructor for UsesExtractorVisitor
     */
    ModifiesExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter);

    /*!
     * Visits an AssignNode and add variables used by the Assignment into PKB
     */
    void visitAssignNode(AssignNode* node) const override;

    /*!
     * Visits a ReadNode and add variable used into PKB
     */
    void visitReadNode(ReadNode* node) const override;
};
