# pragma once

# include "./PKB/PkbReader.h"

class StubPkbReader : public PkbReader {
private:
    std::shared_ptr<PkbReaderManager> readerManager;
public:
    StubPkbReader();

    std::vector<Entity> getAllAssign() const override;

    std::vector<Entity> getAllVariables() const override;

    std::vector<Entity> getAllConstants() const override;

    std::vector<Entity> getAllProcedures() const override;

    std::vector<Entity> getAllStatements() const override;

    std::vector<std::vector<Entity>> getUsesStmtPair(StatementType type) const override;

    std::vector<Entity> getUsesTypeIdent(StatementType type, Variable& var) const override;

    std::vector<Entity> getUsesStmt(StatementType type) const override;

    std::vector<Entity> getUsesVar(Statement& stmt) const override;

    bool isStmtUsesVar(Statement& stmt, Variable& var) const override;

    bool hasUses(Statement& stmt) const override;

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

    std::vector<std::vector<Entity>> getModifiesStmtPair(StatementType type) const override;

    std::vector<Entity> getModifiesTypeIdent(StatementType type, Variable& var) const override;

    std::vector<Entity> getModifiesStmt(StatementType type) const override;

    std::vector<Entity> getModifiesVar(Statement& stmt) const override;

    bool isStmtModifiesVar(Statement& stmt, Variable& var) const override;

    bool hasModifies(Statement& stmt) const override;
};