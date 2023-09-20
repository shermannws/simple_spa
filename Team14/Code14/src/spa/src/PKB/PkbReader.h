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

    virtual std::vector<std::vector<Entity>> getUsesStmtPair(StatementType type) const = 0;

    virtual std::vector<Entity> getUsesTypeIdent(StatementType type, Variable& var) const = 0;

    virtual std::vector<Entity> getUsesStmt(StatementType type) const = 0;

    virtual  std::vector<Entity> getUsesVar(Statement& stmt) const = 0;

    virtual bool isStmtUsesVar(Statement& stmt, Variable& var) const = 0;

    virtual bool hasUses(Statement& stmt) const = 0;

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

    virtual std::vector<std::vector<Entity>> getModifiesStmtPair(StatementType type) const = 0;

    virtual std::vector<Entity> getModifiesTypeIdent(StatementType type, Variable& var) const = 0;

    virtual std::vector<Entity> getModifiesStmt(StatementType type) const = 0;

    virtual std::vector<Entity> getModifiesVar(Statement& stmt) const = 0;

    virtual bool isStmtModifiesVar(Statement& stmt, Variable& var) const = 0;

    virtual bool hasModifies(Statement& stmt) const = 0;
};