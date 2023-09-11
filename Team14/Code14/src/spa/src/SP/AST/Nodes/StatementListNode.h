#pragma once

#include <vector>

#include "ASTNode.h"
#include "StatementNode.h"

class StatementListNode : public ASTNode {
private:
    std::vector<std::shared_ptr<StatementNode>> statements;
public:
    explicit StatementListNode(std::vector<std::shared_ptr<StatementNode>> statements);
    std::vector<std::shared_ptr<StatementNode>> getStatements();
    void accept(DesignExtractorVisitor& visitor) override;
};
