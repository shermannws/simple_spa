# pragma once

# include "./PKB/PkbReader.h"

class StubPkbReader : public PkbReader {
private:
    std::shared_ptr<PkbReaderManager> readerManager;
public:
    StubPkbReader();

    std::vector<Entity> getAllVariables() const override;

    std::vector<Entity> getAllConstants() const override;

    std::vector<Entity> getAllProcedures() const override;

    std::vector<Entity> getAllStatements() const override;

    std::vector<Entity> getAllRead() const override;

    std::vector<Entity> getAllPrint() const override;

    std::vector<Entity> getAllWhile() const override;

    std::vector<Entity> getAllIf() const override;

    std::vector<Entity> getAllCall() const override;

    std::vector<std::vector<Entity>> getUsesStmtPair(StatementType type) const override;

    std::vector<std::vector<Entity>> getUsesProcPair() const override;

    std::vector<Entity> getUsesTypeIdent(StatementType type, Variable& var) const override;

    std::vector<Entity> getUsesProcIdent(Variable& var) const override;

    std::vector<Entity> getUsesStmt(StatementType type) const override;

    std::vector<Entity> getUsesProc() const override;

    std::vector<Entity> getUsesVar(Statement& stmt) const override;

    std::vector<Entity> getUsesVar(Procedure& proc) const override;

    bool isStmtUsesVar(Statement& stmt, Variable& var) const override;

    bool isProcUsesVar(Procedure& proc, Variable& var) const override;

    bool hasUses(Statement& stmt) const override;

    bool hasUses(Procedure& proc) const override;

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

    bool hasFollowsStar() const override;

    bool hasLatterStmt(Statement& statement) const override;

    bool hasFormerStmt(Statement& statement) const override;

    bool hasLatterStarStmt(Statement& statement) const override;

    bool hasFormerStarStmt(Statement& statement) const override;

    std::vector<std::vector<Entity>> getModifiesStmtPair(StatementType type) const override;

    std::vector<std::vector<Entity>> getModifiesProcPair() const override;

    std::vector<Entity> getModifiesTypeIdent(StatementType type, Variable& var) const override;

    std::vector<Entity> getModifiesProcIdent(Variable& var) const override;

    std::vector<Entity> getModifiesStmt(StatementType type) const override;

    std::vector<Entity> getModifiesProc() const override;

    std::vector<Entity> getModifiesVar(Statement& stmt) const override;

    std::vector<Entity> getModifiesVar(Procedure& proc) const override;

    bool isStmtModifiesVar(Statement& stmt, Variable& var) const override;

    bool isProcModifiesVar(Procedure& proc, Variable& var) const override;

    bool hasModifies(Statement& stmt) const override;

    bool hasModifies(Procedure& proc) const override;

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

    bool hasParentStar() const override;

    bool hasParentStmt(Statement& statement) const override;

    bool hasParentStarStmt(Statement& statement) const override;

    bool hasChildStmt(Statement& statement) const override;

    bool hasChildStarStmt(Statement& statement) const override;

    bool hasCalls() const override;

    bool hasCallsStar() const override;

    bool isCallee(Procedure& proc) const override;

    bool isCalleeStar(Procedure& proc) const override;

    bool isCaller(Procedure& proc) const override;

    bool isCallerStar(Procedure& proc) const override;

    bool isCalls(Procedure& caller, Procedure& callee) const override;

    bool isCallsStar(Procedure& caller, Procedure& callee) const override;

    std::vector<Entity> getCallees() const override;

    std::vector<Entity> getCalleesStar() const override;

    std::vector<Entity> getCallers() const override;

    std::vector<Entity> getCallersStar() const override;

    std::vector<std::vector<Entity>> getCallsPair() const override;

    std::vector<std::vector<Entity>> getCallsStarPair() const override;

    std::vector<Entity> getCallers(Procedure& callee) const override;

    std::vector<Entity> getCallersStar(Procedure& callee) const override;

    std::vector<Entity> getCallees(Procedure& caller) const override;

    std::vector<Entity> getCalleesStar(Procedure& caller) const override;

    std::vector<std::vector<Entity>> getNextPair(StatementType formerType, StatementType latterType) const override;

    std::vector<std::vector<Entity>> getNextStarPair(StatementType formerType, StatementType latterType) const override;

    std::vector<Entity> getNextStarSameStmt(StatementType stmtType) const override;

    std::vector<Entity> getNextTypeStmt(StatementType type, Statement& statement) const override;

    std::vector<Entity> getNextStarTypeStmt(StatementType type, Statement& statement) const override;

    std::vector<Entity> getNextTypeWildcard(StatementType type) const override;

    std::vector<Entity> getNextStarTypeWildcard(StatementType type) const override;

    std::vector<Entity> getNextStmtType(Statement& statement, StatementType type) const override;

    std::vector<Entity> getNextStarStmtType(Statement& statement, StatementType type) const override;

    std::vector<Entity> getNextWildcardType(StatementType type) const override;

    std::vector<Entity> getNextStarWildcardType(StatementType type) const override;

    bool isNext(Statement& statement1, Statement& statement2) const override;

    bool isNextStar(Statement& statement1, Statement& statement2) const override;

    bool hasNext() const override;

    bool hasNextStar() const override;

    bool hasBeforeStmt(Statement& statement) const override;

    bool hasBeforeStarStmt(Statement& statement) const override;

    bool hasAfterStmt(Statement& statement) const override;

    bool hasAfterStarStmt(Statement& statement) const override;

    std::vector<Entity> getIfStmtsByVar(Variable& var) const override;

    std::vector<std::vector<Entity>> getAllIfStmtVarPair() const override;

    std::vector<Entity> getWhileStmtsByVar(Variable& var) const override;

    std::vector<std::vector<Entity>> getAllWhileStmtVarPair() const override;

};