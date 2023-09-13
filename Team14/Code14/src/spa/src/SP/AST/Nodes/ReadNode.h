#pragma once

#include <memory>

#include "StatementNode.h"
#include "VariableNode.h"

class ReadNode; // forward declaration
class ReadNodeVisitor {
public:
    virtual void visitReadNode(ReadNode* node) const = 0;
};

class ReadNode : public StatementNode {
private:
    std::shared_ptr<VariableNode> var;
public:
    explicit ReadNode(int statementNumber, std::shared_ptr<VariableNode> var);
    std::shared_ptr<VariableNode> getVar();
    void accept(std::shared_ptr<DesignExtractorVisitor> visitor) override;
    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
    StatementNodeType getStatementType() override;
};
