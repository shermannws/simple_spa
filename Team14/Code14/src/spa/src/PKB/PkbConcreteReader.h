#pragma once

#include <memory>

#include "PKB/Managers/PkbReaderManager.h"
#include "PkbReader.h"

class PkbConcreteReader : public PkbReader {
private:
    std::shared_ptr<PkbReaderManager> readerManager;
public:
    PkbConcreteReader(std::shared_ptr<PkbReaderManager> readerManager);

    // GET ENTITIES
    std::vector<Entity> getAllVariables() const override;

    std::vector<Entity> getAllConstants() const override;

    std::vector<Entity> getAllProcedures() const override;

    std::vector<Entity> getAllStatements() const override;

    std::vector<Entity> getAllRead() const override;

    std::vector<Entity> getAllPrint() const override;

    std::vector<Entity> getAllWhile() const override;

    std::vector<Entity> getAllIf() const override;

    // USES QUERY
    std::vector<std::vector<Entity>> getUsesStmtPair(StatementType type) const override;

    std::vector<Entity> getUsesTypeIdent(StatementType type, Variable& var) const override;

    std::vector<Entity> getUsesStmt(StatementType type) const override;

    std::vector<Entity> getUsesVar(Statement& stmt) const override;

    bool isStmtUsesVar(Statement& stmt, Variable& var) const override;

    bool hasUses(Statement& stmt) const override;

    // FOLLOWS QUERY
    std::vector<std::vector<Entity>> getFollowsPair(StatementType formerType, StatementType latterType) const override;

    std::vector<std::vector<Entity>> getFollowsStarPair(StatementType formerType, StatementType latterType) const override;

    std::vector<Entity> getFollowsTypeStmt(StatementType type, Statement& statement) const override;

    std::vector<Entity> getFollowsStarTypeStmt(StatementType type, Statement& statement) const override;

    std::vector<Entity> getFollowsTypeWildcard(StatementType type) const override;

    std::vector<Entity> getFollowsStarTypeWildcard(StatementType type) const override;

    std::vector<Entity> getFollowsStmtType(Statement& statement, StatementType type) const override;

    std::vector<Entity> getFollowsStarStmtType(Statement& statement, StatementType type) const override;

    std::vector<Entity> getFollowsWildcardType(StatementType type) const override;

    std::vector<Entity> getFollowsStarWildcardType(StatementType type) const override;

    bool isFollows(Statement& statement1, Statement& statement2) const override;

    bool isFollowsStar(Statement& statement1, Statement& statement2) const override;

    bool hasFollows() const override;

    bool hasFollowingStmt(Statement& statement) const override;

    bool hasFollowedStmt(Statement& statement) const override;

    bool hasFollowingStarStmt(Statement& statement) const override;

    bool hasFollowedStarStmt(Statement& statement) const override;

    // MODIFIES QUERY

    std::vector<std::vector<Entity>> getModifiesStmtPair(StatementType type) const override;

    std::vector<Entity> getModifiesTypeIdent(StatementType type, Variable& var) const override;

    std::vector<Entity> getModifiesStmt(StatementType type) const override;

    std::vector<Entity> getModifiesVar(Statement& stmt) const override;

    bool isStmtModifiesVar(Statement& stmt, Variable& var) const override;

    bool hasModifies(Statement& stmt) const override;

    // ASSIGN PATTERN QUERY
    // pattern a (_,_)
    std::vector<Entity> getAllAssign() const override;

    // pattern a (_, "x")
    std::vector<Entity> getAssignStmtsByRhs(std::string& rhs, bool hasRhsWildCard) const override;

    // pattern a (v, _)
    std::vector<std::vector<Entity>> getAllAssignStmtVarPair() const override;

    // pattern a (v, "x")
    std::vector<std::vector<Entity>> getAssignStmtsVarPairByRhs(std::string& rhs, bool hasWildCard) const override;

    // pattern a ("x", _)
    std::vector<Entity> getAssignStmtsByLhs(Variable& lhs) const override;

    // pattern a ("x", "x")
    std::vector<Entity> getAssignStmtsByLhsRhs(Variable& lhs, std::string& rhs, bool hasRhsWildCard) const override;

    // PARENT QUERY
    // FOLLOWS QUERY
    std::vector<std::vector<Entity>> getParentPair(StatementType formerType, StatementType latterType) const override;

    std::vector<std::vector<Entity>> getParentStarPair(StatementType formerType, StatementType latterType) const override;

    std::vector<Entity> getParentTypeStmt(StatementType type, Statement& statement) const override;

    std::vector<Entity> getParentStarTypeStmt(StatementType type, Statement& statement) const override;

    std::vector<Entity> getParentTypeWildcard(StatementType type) const override;

    std::vector<Entity> getParentStarTypeWildcard(StatementType type) const override;

    std::vector<Entity> getParentStmtType(Statement& statement, StatementType type) const override;

    std::vector<Entity> getParentStarStmtType(Statement& statement, StatementType type) const override;

    std::vector<Entity> getParentWildcardType(StatementType type) const override;

    std::vector<Entity> getParentStarWildcardType(StatementType type) const override;

    bool isParent(Statement& statement1, Statement& statement2) const override;

    bool isParentStar(Statement& statement1, Statement& statement2) const override;

    bool hasParent() const override;

    bool hasParentStmt(Statement& statement) const override;

    bool hasParentStarStmt(Statement& statement) const override;

    bool hasChildStmt(Statement& statement) const override;

    bool hasChildStarStmt(Statement& statement) const override;
};