#pragma once

#include <string>

#include "ExpressionNode.h"

class VariableNode : public ExpressionNode {
public:
    std::string varName;
    // TODO: Wrap int type in typedef (VarValue)
    int value;

    explicit VariableNode(std::string& varName, int value);

    void accept(DesignExtractorVisitor& visitor) override;
};
