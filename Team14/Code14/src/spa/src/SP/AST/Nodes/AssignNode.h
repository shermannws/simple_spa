#pragma once

#include <memory>

#include "StatementNode.h"
#include "VariableNode.h"
#include "ExpressionNode.h"

class AssignNode; // forward declaration
class AssignNodeVisitor {
public:
    virtual void visitAssignNode(std::shared_ptr<AssignNode> node) const = 0;
};

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
    void accept(std::shared_ptr<DesignExtractorVisitor> visitor) override;
    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
    StatementNodeType getStatementType() override;
};
