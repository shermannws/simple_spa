#pragma once

#include <functional>
#include <memory>

#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "SP/AST/Nodes/ASTNode.h"

class VisitorUtility {
public:
    /*!
     * Adds all Statement-Variable Relationship where the Variable is child of subtree,
     * also adds all Statement-Variable Relationship between all parent statement and variable
     * @param subtree The node to traverse down to find variable node
     * @param s The statement to store that is in direct relationship with the variable
     * @param parents A vector of parent ASTNode that has indirect Statement-Variable relationship
     * @param funcStmt The function to call to store the Statement-Variable relationship
     * @param proc The procedure node that the subtree is in
     * @param funcProc The function to call to store the Procedure-Variable relationship
     */
    static void
    addAllVariableRelationshipFrom(std::shared_ptr<ASTNode> subtree, Statement s,
                                   std::vector<std::shared_ptr<ASTNode>> parents,
                                   std::function<void(std::shared_ptr<Statement>, std::shared_ptr<Variable>)> funcStmt,
                                   std::shared_ptr<ASTNode> proc,
                                   std::function<void(std::shared_ptr<Procedure>, std::shared_ptr<Variable>)> funcProc);
};