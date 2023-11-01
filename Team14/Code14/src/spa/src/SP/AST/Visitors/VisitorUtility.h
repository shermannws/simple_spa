#pragma once

#include <functional>
#include <memory>

#include "Commons/Entities/Procedure.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "SP/AST/Nodes/ASTNode.h"

typedef std::function<void(std::shared_ptr<Statement>, std::shared_ptr<Variable>)> StmtVarFunc;
typedef std::function<void(std::shared_ptr<Procedure>, std::shared_ptr<Variable>)> ProcVarFunc;

struct VisitorUtilsParams {
private:
    /*!
     * The node to begin traversing down to find all variable node
     */
    std::shared_ptr<ASTNode> subtree;

    /*!
     * The statement to store direct relationship with all variable under subtree
     */
    std::shared_ptr<Statement> statement;

    /*!
     * A vector of parent statements that has indirect Statement-Variable relationship with all variable under subtree
     */
    std::vector<std::shared_ptr<Statement>> parents;

    /*!
     * The procedure that has direct Procedure-Variable relationship with all variable under subtree
     */
    std::shared_ptr<Procedure> procedure;

public:
    /**
     * Constructor for VisitorUtilsParams
     * @param subtree The node to begin traversing down to find all variable node
     */
    VisitorUtilsParams(std::shared_ptr<ASTNode> subtree);

    /**
     * Sets the statement to store direct relationship with all variable under subtree
     * @param statement The statement to store direct relationship with all variable under subtree
     */
    void setStatement(std::shared_ptr<Statement> statement);

    /**
     * Sets the vector of parent statements that has indirect Statement-Variable relationship with all variable under
     * subtree
     * @param parents A vector of parent statements that has indirect Statement-Variable relationship with all variable
     * under subtree
     */
    void setParents(std::vector<std::shared_ptr<Statement>> parents);

    /**
     * Sets the procedure that has direct Procedure-Variable relationship with all variable under subtree
     * @param procedure The procedure that has direct Procedure-Variable relationship with all variable under subtree
     */
    void setProcedure(std::shared_ptr<Procedure> procedure);

    /**
     * Gets the node to begin traversing down to find all variable node
     * @return The node to begin traversing down to find all variable node
     */
    std::shared_ptr<ASTNode> getSubtree() const;

    /**
     * Gets the statement to store direct relationship with all variable under subtree
     * @return The statement to store direct relationship with all variable under subtree
     */
    std::shared_ptr<Statement> getStatement() const;

    /**
     * Gets the vector of parent statements that has indirect Statement-Variable relationship with all variable under
     * subtree
     * @return A vector of parent statements that has indirect Statement-Variable relationship with all variable under
     * subtree
     */
    std::vector<std::shared_ptr<Statement>> getParents() const;

    /**
     * Gets the procedure that has direct Procedure-Variable relationship with all variable under subtree
     * @return The procedure that has direct Procedure-Variable relationship with all variable under subtree
     */
    std::shared_ptr<Procedure> getProcedure() const;
};

class VisitorUtility {
private:
    /**
     * The function to call to store the Statement-Variable relationship
     */
    StmtVarFunc funcStmt;

    /**
     * The function to call to store the Procedure-Variable relationship
     */
    ProcVarFunc funcProc;

public:
    /**
     * Default constructor for VisitorUtility
     */
    VisitorUtility() = default;

    /**
     * Constructor for VisitorUtility
     * @param funcStmt The function to call to store the Statement-Variable relationship
     * @param funcProc The function to call to store the Procedure-Variable relationship
     */
    VisitorUtility(StmtVarFunc &funcStmt, ProcVarFunc &funcProc);

    /*!
     * Adds all Statement-Variable Relationship and Procedure-Variable Relationship for variables within the subtree
     * @param params A VisitorUtilsParams struct containing all the necessary parameters to add direct and indirect
     * relationships with variables
     */
    void addAllVariableRelationship(VisitorUtilsParams &params) const;
};