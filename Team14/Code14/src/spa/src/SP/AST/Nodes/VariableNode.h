#pragma once

#include <string>

#include "ExpressionNode.h"

class VariableNode; // forward declaration
class VariableNodeVisitor {
public:
    virtual void visitVariableNode(VariableNode* node) const = 0;
};

class VariableNode : public ExpressionNode {
private:
    std::string varName;
public:
    explicit VariableNode(std::string varName);
    std::string getVarName();
    void accept(std::shared_ptr<DesignExtractorVisitor> visitor) override;
    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
    std::string toString() override;
};
