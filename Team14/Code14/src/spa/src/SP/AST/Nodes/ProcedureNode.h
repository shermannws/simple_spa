#pragma once

#include <string>

#include "ASTNode.h"
#include "StatementListNode.h"

class ProcedureNode; // forward declaration
class ProcedureNodeVisitor {
public:
    virtual void visitProcedureNode(std::shared_ptr<ProcedureNode> node) const = 0;
};

class ProcedureNode : public ASTNode {
private:
    std::string procedureName;
    std::shared_ptr<StatementListNode> statementList;
public:
    explicit ProcedureNode(std::string procedureName, std::shared_ptr<StatementListNode> statementList);
    std::string getProcedureName();
    std::shared_ptr<StatementListNode> getStatementList();
    void accept(DesignExtractorVisitor& visitor) override;
    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
};
