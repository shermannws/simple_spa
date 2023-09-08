#pragma once

#include <vector>

#include "ASTNode.h"
#include "StatementNode.h"

class StatementListNode : public ASTNode {
public:
    std::vector<std::shared_ptr<StatementNode>> statements;

    void accept(DesignExtractorVisitor& visitor) override;
};
