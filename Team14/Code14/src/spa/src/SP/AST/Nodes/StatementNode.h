#pragma once

#include "ASTNode.h"

// Interface for all statement node types
class StatementNode : public ASTNode {
protected:
    int statementNumber;
public:
    explicit StatementNode(int statementNumber);
};
