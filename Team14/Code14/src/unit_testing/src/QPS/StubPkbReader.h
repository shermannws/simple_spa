#pragma once

#include "./PKB/PkbReader.h"

class StubPkbReader : public PkbReader {
private:
    std::shared_ptr<PkbReaderManager> readerManager;

public:
    StubPkbReader();

    std::unordered_set<Entity> getAllVariables() const override;

    std::unordered_set<Entity> getAllConstants() const override;

    std::unordered_set<Entity> getAllProcedures() const override;

    std::unordered_set<Entity> getAllStatements() const override;

    std::unordered_set<Entity> getAllRead() const override;

    std::unordered_set<Entity> getAllPrint() const override;

    std::unordered_set<Entity> getAllWhile() const override;

    std::unordered_set<Entity> getAllIf() const override;

    std::unordered_set<Entity> getAllCall() const override;

    std::unordered_set<std::vector<Entity>> getUsesStmtPair(StatementType type) const override;

    std::unordered_set<std::vector<Entity>> getUsesProcPair() const override;

    std::unordered_set<Entity> getUsesTypeIdent(StatementType type, Variable &var) const override;

    std::unordered_set<Entity> getUsesProcIdent(Variable &var) const override;

    std::unordered_set<Entity> getUsesStmt(StatementType type) const override;

    std::unordered_set<Entity> getUsesProc() const override;

    std::unordered_set<Entity> getUsesVar(Statement &stmt) const override;

    std::unordered_set<Entity> getUsesVar(Procedure &proc) const override;

    bool isStmtUsesVar(Statement &stmt, Variable &var) const override;

    bool isProcUsesVar(Procedure &proc, Variable &var) const override;

    bool hasUses(Statement &stmt) const override;

    bool hasUses(Procedure &proc) const override;

    std::unordered_set<std::vector<Entity>> getFollowsPair(StatementType formerType,
                                                           StatementType latterType) const override;

    std::unordered_set<std::vector<Entity>> getFollowsStarPair(StatementType formerType,
                                                               StatementType latterType) const override;

    std::unordered_set<Entity> getFollowsTypeStmt(StatementType type, Statement &statement) const override;

    std::unordered_set<Entity> getFollowsStarTypeStmt(StatementType type, Statement &statement) const override;

    std::unordered_set<Entity> getFollowsTypeWildcard(StatementType type) const override;

    std::unordered_set<Entity> getFollowsStarTypeWildcard(StatementType type) const override;

    std::unordered_set<Entity> getFollowsStmtType(Statement &statement, StatementType type) const override;

    std::unordered_set<Entity> getFollowsStarStmtType(Statement &statement, StatementType type) const override;

    std::unordered_set<Entity> getFollowsWildcardType(StatementType type) const override;

    std::unordered_set<Entity> getFollowsStarWildcardType(StatementType type) const override;

    bool isFollows(Statement &statement1, Statement &statement2) const override;

    bool isFollowsStar(Statement &statement1, Statement &statement2) const override;

    bool hasFollows() const override;

    bool hasFollowsStar() const override;

    bool hasLatterStmt(Statement &statement) const override;

    bool hasFormerStmt(Statement &statement) const override;

    bool hasLatterStarStmt(Statement &statement) const override;

    bool hasFormerStarStmt(Statement &statement) const override;

    std::unordered_set<std::vector<Entity>> getModifiesStmtPair(StatementType type) const override;

    std::unordered_set<std::vector<Entity>> getModifiesProcPair() const override;

    std::unordered_set<Entity> getModifiesTypeIdent(StatementType type, Variable &var) const override;

    std::unordered_set<Entity> getModifiesProcIdent(Variable &var) const override;

    std::unordered_set<Entity> getModifiesStmt(StatementType type) const override;

    std::unordered_set<Entity> getModifiesProc() const override;

    std::unordered_set<Entity> getModifiesVar(Statement &stmt) const override;

    std::unordered_set<Entity> getModifiesVar(Procedure &proc) const override;

    bool isStmtModifiesVar(Statement &stmt, Variable &var) const override;

    bool isProcModifiesVar(Procedure &proc, Variable &var) const override;

    bool hasModifies(Statement &stmt) const override;

    bool hasModifies(Procedure &proc) const override;

    // pattern a (_,_)
    std::unordered_set<Entity> getAllAssign() const override;

    // pattern a (_, "x")
    std::unordered_set<Entity> getAssignStmtsByRhs(std::string &rhs, bool hasRhsWildCard) const override;

    // pattern a (v, _)
    std::unordered_set<std::vector<Entity>> getAllAssignStmtVarPair() const override;

    // pattern a (v, "x")
    std::unordered_set<std::vector<Entity>> getAssignStmtsVarPairByRhs(std::string &rhs,
                                                                       bool hasWildCard) const override;

    // pattern a ("x", _)
    std::unordered_set<Entity> getAssignStmtsByLhs(Variable &lhs) const override;

    // pattern a ("x", "x")
    std::unordered_set<Entity> getAssignStmtsByLhsRhs(Variable &lhs, std::string &rhs,
                                                      bool hasRhsWildCard) const override;

    std::unordered_set<std::vector<Entity>> getParentPair(StatementType formerType,
                                                          StatementType latterType) const override;

    std::unordered_set<std::vector<Entity>> getParentStarPair(StatementType formerType,
                                                              StatementType latterType) const override;

    std::unordered_set<Entity> getParentTypeStmt(StatementType type, Statement &statement) const override;

    std::unordered_set<Entity> getParentStarTypeStmt(StatementType type, Statement &statement) const override;

    std::unordered_set<Entity> getParentTypeWildcard(StatementType type) const override;

    std::unordered_set<Entity> getParentStarTypeWildcard(StatementType type) const override;

    std::unordered_set<Entity> getParentStmtType(Statement &statement, StatementType type) const override;

    std::unordered_set<Entity> getParentStarStmtType(Statement &statement, StatementType type) const override;

    std::unordered_set<Entity> getParentWildcardType(StatementType type) const override;

    std::unordered_set<Entity> getParentStarWildcardType(StatementType type) const override;

    bool isParent(Statement &statement1, Statement &statement2) const override;

    bool isParentStar(Statement &statement1, Statement &statement2) const override;

    bool hasParent() const override;

    bool hasParentStar() const override;

    bool hasParentStmt(Statement &statement) const override;

    bool hasParentStarStmt(Statement &statement) const override;

    bool hasChildStmt(Statement &statement) const override;

    bool hasChildStarStmt(Statement &statement) const override;

    bool hasCalls() const override;

    bool hasCallsStar() const override;

    bool isCallee(Procedure &proc) const override;

    bool isCalleeStar(Procedure &proc) const override;

    bool isCaller(Procedure &proc) const override;

    bool isCallerStar(Procedure &proc) const override;

    bool isCalls(Procedure &caller, Procedure &callee) const override;

    bool isCallsStar(Procedure &caller, Procedure &callee) const override;

    std::unordered_set<Entity> getCallees() const override;

    std::unordered_set<Entity> getCalleesStar() const override;

    std::unordered_set<Entity> getCallers() const override;

    std::unordered_set<Entity> getCallersStar() const override;

    std::unordered_set<std::vector<Entity>> getCallsPair() const override;

    std::unordered_set<std::vector<Entity>> getCallsStarPair() const override;

    std::unordered_set<Entity> getCallers(Procedure &callee) const override;

    std::unordered_set<Entity> getCallersStar(Procedure &callee) const override;

    std::unordered_set<Entity> getCallees(Procedure &caller) const override;

    std::unordered_set<Entity> getCalleesStar(Procedure &caller) const override;

    std::unordered_set<std::vector<Entity>> getNextPair(StatementType formerType,
                                                        StatementType latterType) const override;

    std::unordered_set<std::vector<Entity>> getNextStarPair(StatementType formerType,
                                                            StatementType latterType) const override;

    std::unordered_set<Entity> getNextStarSameStmt(StatementType stmtType) const override;

    std::unordered_set<Entity> getNextTypeStmt(StatementType type, Statement &statement) const override;

    std::unordered_set<Entity> getNextStarTypeStmt(StatementType type, Statement &statement) const override;

    std::unordered_set<Entity> getNextTypeWildcard(StatementType type) const override;

    std::unordered_set<Entity> getNextStarTypeWildcard(StatementType type) const override;

    std::unordered_set<Entity> getNextStmtType(Statement &statement, StatementType type) const override;

    std::unordered_set<Entity> getNextStarStmtType(Statement &statement, StatementType type) const override;

    std::unordered_set<Entity> getNextWildcardType(StatementType type) const override;

    std::unordered_set<Entity> getNextStarWildcardType(StatementType type) const override;

    bool isNext(Statement &statement1, Statement &statement2) const override;

    bool isNextStar(Statement &statement1, Statement &statement2) const override;

    bool hasNext() const override;

    bool hasNextStar() const override;

    bool hasBeforeStmt(Statement &statement) const override;

    bool hasBeforeStarStmt(Statement &statement) const override;

    bool hasAfterStmt(Statement &statement) const override;

    bool hasAfterStarStmt(Statement &statement) const override;

    std::unordered_set<Entity> getAllIfPatternStmts() const override;

    std::unordered_set<Entity> getIfStmtsByVar(Variable &var) const override;

    std::unordered_set<std::vector<Entity>> getAllIfStmtVarPair() const override;

    std::unordered_set<Entity> getAllWhilePatternStmts() const override;

    std::unordered_set<Entity> getWhileStmtsByVar(Variable &var) const override;

    std::unordered_set<std::vector<Entity>> getAllWhileStmtVarPair() const override;
};