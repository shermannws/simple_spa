#pragma once

#include <string>

#include "ASTNode.h"
#include "StatementListNode.h"

class ProcedureNode; // forward declaration
class ProcedureNodeVisitor {
public:
    virtual void visitProcedureNode(ProcedureNode* node, std::vector<std::shared_ptr<ASTNode>> parents) const = 0;
};

class ProcedureNode : public ASTNode {
private:
    std::string procedureName;
    std::shared_ptr<StatementListNode> statementList;
public:
    explicit ProcedureNode(std::string procedureName, std::shared_ptr<StatementListNode> statementList);
    std::string getProcedureName();
    std::shared_ptr<StatementListNode> getStatementList();
    void accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents) override;
    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
};
