#pragma once

#include <memory>

#include "StatementNode.h"

class CallNode; // forward declaration
class CallNodeVisitor {
public:
    virtual void visitCallNode(CallNode* node, std::vector<std::shared_ptr<ASTNode>> parents) const = 0;
};

class CallNode: public StatementNode {
private:
    std::string procedureName;
public:
    explicit CallNode(int statementNumber, std::string procedureName);
    std::string getProcedureName();
    void accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents) override;
    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
    StatementNodeType getStatementType() override;
};
