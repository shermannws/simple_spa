#pragma once

#include <string>

#include "ExpressionNode.h"

class VariableNode : public ExpressionNode {
private:
    std::string varName;
public:
    explicit VariableNode(std::string varName);
    std::string getVarName();
    void accept(DesignExtractorVisitor& visitor) override;
    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
};
