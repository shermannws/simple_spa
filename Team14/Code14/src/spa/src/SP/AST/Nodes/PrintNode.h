#pragma once

#include <memory>

#include "StatementNode.h"
#include "VariableNode.h"

class PrintNode: public StatementNode {
public:
    std::shared_ptr<VariableNode> var;

    explicit PrintNode(int statementNumber);

    void accept(DesignExtractorVisitor& visitor) override;
};
