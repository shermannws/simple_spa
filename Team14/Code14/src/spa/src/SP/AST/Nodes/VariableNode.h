#pragma once

#include <string>

#include "ExpressionNode.h"

class VariableNode : public ExpressionNode {
private:
    std::string varName;
public:
    explicit VariableNode(std::string varName);
    void accept(DesignExtractorVisitor& visitor) override;
};
