#pragma once

#include "ExpressionNode.h"

class ConstantNode : public ExpressionNode {
public:
    // TODO: Wrap int type in typedef (ConstValue)
    int value;

    explicit ConstantNode(int);

    void accept(DesignExtractorVisitor& visitor) override;
};
