#pragma once

#include "ExpressionNode.h"

class ConstantNode : public ExpressionNode {
private:
    // TODO: Wrap int type in typedef (ConstValue)
    int value;
public:
    explicit ConstantNode(int value);
    int getValue();
    void accept(DesignExtractorVisitor& visitor) override;
    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
};
