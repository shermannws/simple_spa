#pragma once

#include "ExpressionNode.h"

class ConstantNode; // forward declaration
class ConstantNodeVisitor {
public:
    virtual void visitConstantNode(std::shared_ptr<ConstantNode> node) const = 0;
};

class ConstantNode : public ExpressionNode {
private:
    // TODO: Wrap int type in typedef (ConstValue)
    int value;
public:
    explicit ConstantNode(int value);
    int getValue();
    void accept(std::shared_ptr<DesignExtractorVisitor> visitor) override;
    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
};
