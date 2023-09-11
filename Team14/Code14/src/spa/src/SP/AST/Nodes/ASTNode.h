#pragma once

#include <assert.h>
#include <memory>
#include <vector>

#include "../Visitors/DesignExtractorVisitor.h"

// Interface for all ASTNodes
class ASTNode {
public:
    virtual void accept(DesignExtractorVisitor& visitor) = 0;
    virtual std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() = 0;
};
