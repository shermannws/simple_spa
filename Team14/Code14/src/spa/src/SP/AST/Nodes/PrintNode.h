#pragma once

#include <memory>

#include "StatementNode.h"
#include "VariableNode.h"

class PrintNode: public StatementNode {
private:
    std::shared_ptr<VariableNode> var;
public:
    explicit PrintNode(int statementNumber, std::shared_ptr<VariableNode> var);
    std::shared_ptr<VariableNode> getVar();
    void accept(DesignExtractorVisitor& visitor) override;
};
