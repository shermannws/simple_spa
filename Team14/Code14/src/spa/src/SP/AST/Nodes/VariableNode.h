#pragma once

#include <string>

#include "ExpressionNode.h"

class VariableNode : public ExpressionNode {
public:
    std::string varName;

    explicit VariableNode(std::string& varName);

    void accept(DesignExtractorVisitor& visitor) override;
};
