#pragma once

#include <memory>

#include "StatementNode.h"
#include "VariableNode.h"
#include "ExpressionNode.h"

class AssignNode : public StatementNode {
public:
    std::shared_ptr<VariableNode> var;
    std::shared_ptr<ExpressionNode> expression;

    explicit AssignNode(int statementNumber);

    void accept(DesignExtractorVisitor& visitor) override;
};
