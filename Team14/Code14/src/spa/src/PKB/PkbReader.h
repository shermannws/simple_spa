#pragma once

#include <memory>

#include "PKB/Managers/PkbReaderManager.h"

class PkbReader {
public:
    virtual std::vector<Entity> getAllAssign() const = 0;

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

    virtual std::vector<std::vector<Entity>> getFollowsPair(StatementType formerType, StatementType latterType) const = 0;

    virtual std::vector<std::vector<Entity>> getFollowsStarPair(StatementType formerType, StatementType latterType) const = 0;

    virtual std::vector<Entity> getFollowsTypeStmt(StatementType type, Statement& statement) const = 0;

    virtual std::vector<Entity> getFollowsStarTypeStmt(StatementType type, Statement& statement) const = 0;

    virtual std::vector<Entity> getFollowsTypeWildcard(StatementType type) const = 0;

    virtual std::vector<Entity> getFollowsStarTypeWildcard(StatementType type) const = 0;

    virtual std::vector<Entity> getFollowsStmtType(Statement& statement, StatementType type) const = 0;

    virtual std::vector<Entity> getFollowsStarStmtType(Statement& statement, StatementType type) const = 0;

    virtual std::vector<Entity> getFollowsWildcardType(StatementType type) const = 0;

    virtual std::vector<Entity> getFollowsStarWildcardType(StatementType type) const = 0;

    virtual bool isFollows(Statement& statement1, Statement& statement2) const = 0;

    virtual bool isFollowsStar(Statement& statement1, Statement& statement2) const = 0;

    virtual bool hasFollows() const = 0;
};