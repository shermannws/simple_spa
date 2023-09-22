#pragma once

#include <memory>

#include "PKB/Managers/PkbReaderManager.h"
#include "PkbTypes.h"

class PkbReader {
public:
    // GET ENTITIES
    virtual std::vector<Entity> getAllVariables() const = 0;

    virtual std::vector<Entity> getAllConstants() const = 0;

    virtual std::vector<Entity> getAllProcedures() const = 0;

    virtual std::vector<Entity> getAllStatements() const = 0;

    virtual std::vector<Entity> getAllRead() const = 0;

    virtual std::vector<Entity> getAllPrint() const = 0;

    virtual std::vector<Entity> getAllWhile() const = 0;

    virtual std::vector<Entity> getAllIf() const = 0;

    // USES QUERY
    virtual std::vector<std::vector<Entity>> getUsesStmtPair(StatementType type) const = 0;

    virtual std::vector<Entity> getUsesTypeIdent(StatementType type, Variable& var) const = 0;

    virtual std::vector<Entity> getUsesStmt(StatementType type) const = 0;

    virtual  std::vector<Entity> getUsesVar(Statement& stmt) const = 0;

    virtual bool isStmtUsesVar(Statement& stmt, Variable& var) const = 0;

    virtual bool hasUses(Statement& stmt) const = 0;

    // FOLLOWS & FOLLOWS* QUERY
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

    virtual bool hasLatterStmt(Statement& statement) const = 0;

    virtual bool hasFormerStmt(Statement& statement) const = 0;

    virtual bool hasLatterStarStmt(Statement& statement) const = 0;

    virtual bool hasFormerStarStmt(Statement& statement) const = 0;

    // MODIFIES QUERY
    virtual std::vector<std::vector<Entity>> getModifiesStmtPair(StatementType type) const = 0;

    virtual std::vector<Entity> getModifiesTypeIdent(StatementType type, Variable& var) const = 0;

    virtual std::vector<Entity> getModifiesStmt(StatementType type) const = 0;

    virtual std::vector<Entity> getModifiesVar(Statement& stmt) const = 0;

    virtual bool isStmtModifiesVar(Statement& stmt, Variable& var) const = 0;

    virtual bool hasModifies(Statement& stmt) const = 0;

    // ASSIGN PATTERN QUERY
    // pattern a (_,_)
    virtual std::vector<Entity> getAllAssign() const = 0;

    // pattern a (_, "x")
    virtual std::vector<Entity> getAssignStmtsByRhs(Expression& rhs, bool hasRhsWildCard) const = 0;

    // pattern a (v, _)
    virtual std::vector<std::vector<Entity>> getAllAssignStmtVarPair() const = 0;

    // pattern a (v, "x")
    virtual std::vector<std::vector<Entity>> getAssignStmtsVarPairByRhs(Expression& rhs, bool hasWildCard) const = 0;

    // pattern a ("x", _)
    virtual std::vector<Entity> getAssignStmtsByLhs(Variable& lhs) const = 0;

    // pattern a ("x", "x")
    virtual std::vector<Entity> getAssignStmtsByLhsRhs(Variable& lhs, Expression& rhs, bool hasRhsWildCard) const = 0;

    // PARENT & PARENT* QUERY
    virtual std::vector<std::vector<Entity>> getParentPair(StatementType formerType, StatementType latterType) const = 0;

    virtual std::vector<std::vector<Entity>> getParentStarPair(StatementType formerType, StatementType latterType) const = 0;

    virtual std::vector<Entity> getParentTypeStmt(StatementType type, Statement& statement) const = 0;

    virtual std::vector<Entity> getParentStarTypeStmt(StatementType type, Statement& statement) const = 0;

    virtual std::vector<Entity> getParentTypeWildcard(StatementType type) const = 0;

    virtual std::vector<Entity> getParentStarTypeWildcard(StatementType type) const = 0;

    virtual std::vector<Entity> getParentStmtType(Statement& statement, StatementType type) const = 0;

    virtual std::vector<Entity> getParentStarStmtType(Statement& statement, StatementType type) const = 0;

    virtual std::vector<Entity> getParentWildcardType(StatementType type) const = 0;

    virtual std::vector<Entity> getParentStarWildcardType(StatementType type) const = 0;

    virtual bool isParent(Statement& statement1, Statement& statement2) const = 0;

    virtual bool isParentStar(Statement& statement1, Statement& statement2) const = 0;

    virtual bool hasParent() const = 0;

    virtual bool hasParentStmt(Statement& statement) const = 0;

    virtual bool hasParentStarStmt(Statement& statement) const = 0;

    virtual bool hasChildStmt(Statement& statement) const = 0;

    virtual bool hasChildStarStmt(Statement& statement) const = 0;
};