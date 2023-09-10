#pragma once

#include <memory>

#include "StatementNode.h"
#include "VariableNode.h"

class ReadNode : public StatementNode {
private:
    std::shared_ptr<VariableNode> var;
public:
    explicit ReadNode(int statementNumber, std::shared_ptr<VariableNode> var);
    void accept(DesignExtractorVisitor& visitor) override;
};
