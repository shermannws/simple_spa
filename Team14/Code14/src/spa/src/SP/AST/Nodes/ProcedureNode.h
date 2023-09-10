#pragma once

#include <string>

#include "ASTNode.h"
#include "StatementListNode.h"

class ProcedureNode : public ASTNode {
private:
    std::string procedureName;
    std::shared_ptr<StatementListNode> statementList;
public:
    explicit ProcedureNode(std::string procedureName, std::shared_ptr<StatementListNode> statementList);
    void accept(DesignExtractorVisitor& visitor) override;
};
