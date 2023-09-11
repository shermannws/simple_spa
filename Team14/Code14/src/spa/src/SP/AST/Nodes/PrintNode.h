#pragma once

#include <memory>

#include "StatementNode.h"
#include "VariableNode.h"

class PrintNode; // forward declaration
class PrintNodeVisitor {
public:
    virtual void visitPrintNode(std::shared_ptr<PrintNode> node) const = 0;
};

class PrintNode: public StatementNode {
private:
    std::shared_ptr<VariableNode> var;
public:
    explicit PrintNode(int statementNumber, std::shared_ptr<VariableNode> var);
    std::shared_ptr<VariableNode> getVar();
    void accept(std::shared_ptr<DesignExtractorVisitor> visitor) override;
    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
    StatementNodeType getStatementType() override;
};
