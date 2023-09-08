#pragma once

#include <memory>

#include "StatementNode.h"
#include "VariableNode.h"

class ReadNode : public StatementNode {
public:
    std::shared_ptr<VariableNode> var;

    explicit ReadNode(int statementNumber);

    void accept(DesignExtractorVisitor& visitor) override;
};
