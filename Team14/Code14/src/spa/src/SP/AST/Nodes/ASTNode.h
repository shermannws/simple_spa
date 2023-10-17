#pragma once

#include <assert.h>
#include <memory>
#include <vector>

#include "../Visitors/DesignExtractorVisitor.h"

/**
 * Interface for all ASTNodes.
 */
class ASTNode {
public:
    /**
     * Accepts the DesignExtractorVisitor and calls the visit method for this ASTNode.
     * @param visitor A design extractor visitor which implements the DesignExtractorVisitor interface
     * @param parents The parent nodes of this ASTNode
     * @param proc The procedure node which this ASTNode belongs to
     */
    virtual void accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents,
                        std::shared_ptr<ASTNode> proc) = 0;

    /**
     * Returns all immediate child nodes of this ASTNode.
     * @return The immediate child nodes
     */
    virtual std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() = 0;
};
