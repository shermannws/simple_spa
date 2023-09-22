#pragma once

#include <assert.h>
#include <memory>
#include <vector>

#include "../Visitors/DesignExtractorVisitor.h"

// Interface for all ASTNodes
class ASTNode {
public:
    virtual void accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents) = 0;
    virtual std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() = 0;
};
