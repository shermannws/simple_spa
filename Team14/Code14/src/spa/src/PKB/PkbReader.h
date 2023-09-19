#pragma once

#include <memory>

#include "PKB/Managers/PkbReaderManager.h"

class PkbReader {
public:

    virtual std::vector<Entity> getAllVariables() const = 0;

    virtual std::vector<Entity> getAllConstants() const = 0;

    virtual std::vector<Entity> getAllProcedures() const = 0;

    virtual std::vector<Entity> getAllStatements() const = 0;

    virtual std::vector<std::vector<Entity>> getAllUsesAssignVariablePair() const = 0;

    virtual std::vector<Entity> getAllUsesAssignByVariable(Variable& variable) const = 0;

    virtual std::vector<std::vector<Entity>> getAllFollowsStatementPair() const = 0;

    // Returns statement followed by (ahead) given statement
    virtual std::vector<Entity> getFollowsByStatement(Statement& statement) const = 0;
    
    // Returns statement following (behind) given statement
    virtual std::vector<Entity> getFollowingStatement(Statement& statement) const = 0;

    // Returns true if statement1 follows statement2
    virtual bool getIsFollows(Statement& statement1, Statement& statement2) const = 0;

    // Pattern queries i.e. pattern a (...,...)
    // pattern a (_,_)
    virtual std::vector<Entity> getAllAssign() const = 0;

    // pattern a (_, "x")
    virtual std::vector<Entity> getAssignStmtsByRhs(std::string& rhs, bool hasRhsWildCard) const = 0;

    // pattern a (v, _)
    virtual std::vector<std::vector<Entity>> getAllAssignStmtVarPair() const = 0;

    // pattern a (v, "x")
    virtual std::vector<std::vector<Entity>> getAssignStmtsVarPairByRhs(std::string& rhs, bool hasWildCard) const = 0;

    // pattern a ("x", _)
    virtual std::vector<Entity> getAssignStmtsByLhs(Variable& lhs) const = 0;

    // pattern a ("x", "x")
    virtual std::vector<Entity> getAssignStmtsByLhsRhs(Variable& lhs, std::string& rhs, bool hasRhsWildCard) const = 0;
};