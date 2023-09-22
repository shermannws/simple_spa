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


// Abstract parent class for all statement node types
class StatementNode : public ASTNode {
protected:
    /**
     * The statement number of the statement, used for identification.
     */
    int statementNumber;

public:
    /**
     * Creates and initializes a statement.
     * @param statementNumber The statement number of the statement
     */
    explicit StatementNode(int statementNumber);

    /**
     * Returns the statement number.
     * @return The statement number of the statement
     */
    int getStatementNumber();

    /**
     * Returns the specific type of the statement.
     * @return The StatementNodeType of this statement
     */
    virtual StatementNodeType getStatementType() = 0;
};
