#pragma once

#include "ExpressionNode.h"

class ConstantNode : public ExpressionNode {
private:
    // TODO: Wrap int type in typedef (ConstValue)
    int value;
public:
    explicit ConstantNode(int value);
    void accept(DesignExtractorVisitor& visitor) override;
};
