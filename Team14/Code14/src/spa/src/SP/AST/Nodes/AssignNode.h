#pragma once

#include <memory>

#include "StatementNode.h"
#include "VariableNode.h"
#include "ExpressionNode.h"

class AssignNode : public StatementNode {
private:
    std::shared_ptr<VariableNode> var;
    std::shared_ptr<ExpressionNode> expression;
public:
    explicit AssignNode(int statementNumber,
                        std::shared_ptr<VariableNode> var,
                        std::shared_ptr<ExpressionNode> expression);
    std::shared_ptr<VariableNode> getVar();
    std::shared_ptr<ExpressionNode> getExpression();
    void accept(DesignExtractorVisitor& visitor) override;
};
