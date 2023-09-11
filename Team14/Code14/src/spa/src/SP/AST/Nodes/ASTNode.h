#pragma once

#include "../Visitors/DesignExtractorVisitor.h"

// Interface for all ASTNodes
class ASTNode {
public:
    virtual void accept(DesignExtractorVisitor& visitor) = 0;
};
