#pragma once

#include "ASTNode.h"

// Interface for all statement node types
class StatementNode : public ASTNode {
public:
    int statementNumber;

    explicit StatementNode(int statementNumber);
};
