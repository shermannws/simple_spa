#pragma once

#include "ASTNode.h"

enum class StatementNodeType {
    Assign,
    Read,
    Print,
    Call,
    While,
    If
};


// Interface for all statement node types
class StatementNode : public ASTNode {
protected:
    int statementNumber;
public:
    explicit StatementNode(int statementNumber);
    int getStatementNumber();
    virtual StatementNodeType getStatementType() = 0;
};
