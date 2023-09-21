#pragma once

#include "ExpressionNode.h"

class ConstantNode; // forward declaration
class ConstantNodeVisitor {
public:
    virtual void visitConstantNode(ConstantNode* node, std::vector<std::shared_ptr<ASTNode>> parents) const = 0;
};

class ConstantNode : public ExpressionNode {
private:
    // TODO: Wrap int type in typedef (ConstValue)
    int value;
public:
    explicit ConstantNode(int value);
    int getValue();
    void accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents) override;
    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
    std::string toString() override;
};
