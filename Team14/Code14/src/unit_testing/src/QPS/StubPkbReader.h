#pragma once

#include "./PKB/PkbReader.h"

class StubPkbReader : public PkbReader {
private:
    std::shared_ptr<PkbReaderManager> readerManager;

public:
    StubPkbReader();

    EntitySet getAllVariables() const override;

    EntitySet getAllConstants() const override;

    EntitySet getAllProcedures() const override;

    EntitySet getAllStatements() const override;

    EntitySet getAllRead() const override;

    EntitySet getAllPrint() const override;

    EntitySet getAllWhile() const override;

    EntitySet getAllIf() const override;

    EntitySet getAllCall() const override;

    EntityPairSet getUsesStmtPair(StatementType type) const override;

    EntityPairSet getUsesProcPair() const override;

    EntitySet getUsesTypeIdent(StatementType type, Variable &var) const override;

    EntitySet getUsesProcIdent(Variable &var) const override;

    EntitySet getUsesStmt(StatementType type) const override;

    EntitySet getUsesProc() const override;

    EntitySet getUsesVar(Statement &stmt) const override;

    EntitySet getUsesVar(Procedure &proc) const override;

    bool isStmtUsesVar(Statement &stmt, Variable &var) const override;

    bool isProcUsesVar(Procedure &proc, Variable &var) const override;

    bool hasUses(Statement &stmt) const override;

    bool hasUses(Procedure &proc) const override;

    EntityPairSet getFollowsPair(StatementType formerType,
                                                           StatementType latterType) const override;

    EntityPairSet getFollowsStarPair(StatementType formerType,
                                                               StatementType latterType) const override;

    EntitySet getFollowsTypeStmt(StatementType type, Statement &statement) const override;

    EntitySet getFollowsStarTypeStmt(StatementType type, Statement &statement) const override;

    EntitySet getFollowsTypeWildcard(StatementType type) const override;

    EntitySet getFollowsStarTypeWildcard(StatementType type) const override;

    EntitySet getFollowsStmtType(Statement &statement, StatementType type) const override;

    EntitySet getFollowsStarStmtType(Statement &statement, StatementType type) const override;

    EntitySet getFollowsWildcardType(StatementType type) const override;

    EntitySet getFollowsStarWildcardType(StatementType type) const override;

    bool isFollows(Statement &statement1, Statement &statement2) const override;

    bool isFollowsStar(Statement &statement1, Statement &statement2) const override;

    bool hasFollows() const override;

    bool hasFollowsStar() const override;

    bool hasLatterStmt(Statement &statement) const override;

    bool hasFormerStmt(Statement &statement) const override;

    bool hasLatterStarStmt(Statement &statement) const override;

    bool hasFormerStarStmt(Statement &statement) const override;

    EntityPairSet getModifiesStmtPair(StatementType type) const override;

    EntityPairSet getModifiesProcPair() const override;

    EntitySet getModifiesTypeIdent(StatementType type, Variable &var) const override;

    EntitySet getModifiesProcIdent(Variable &var) const override;

    EntitySet getModifiesStmt(StatementType type) const override;

    EntitySet getModifiesProc() const override;

    EntitySet getModifiesVar(Statement &stmt) const override;

    EntitySet getModifiesVar(Procedure &proc) const override;

    bool isStmtModifiesVar(Statement &stmt, Variable &var) const override;

    bool isProcModifiesVar(Procedure &proc, Variable &var) const override;

    bool hasModifies(Statement &stmt) const override;

    bool hasModifies(Procedure &proc) const override;

    // pattern a (_,_)
    EntitySet getAllAssign() const override;

    // pattern a (_, "x")
    EntitySet getAssignStmtsByRhs(std::string &rhs, bool hasRhsWildCard) const override;

    // pattern a (v, _)
    EntityPairSet getAllAssignStmtVarPair() const override;

    // pattern a (v, "x")
    EntityPairSet getAssignStmtsVarPairByRhs(std::string &rhs,
                                                                       bool hasWildCard) const override;

    // pattern a ("x", _)
    EntitySet getAssignStmtsByLhs(Variable &lhs) const override;

    // pattern a ("x", "x")
    EntitySet getAssignStmtsByLhsRhs(Variable &lhs, std::string &rhs,
                                                      bool hasRhsWildCard) const override;

    EntityPairSet getParentPair(StatementType formerType,
                                                          StatementType latterType) const override;

    EntityPairSet getParentStarPair(StatementType formerType,
                                                              StatementType latterType) const override;

    EntitySet getParentTypeStmt(StatementType type, Statement &statement) const override;

    EntitySet getParentStarTypeStmt(StatementType type, Statement &statement) const override;

    EntitySet getParentTypeWildcard(StatementType type) const override;

    EntitySet getParentStarTypeWildcard(StatementType type) const override;

    EntitySet getParentStmtType(Statement &statement, StatementType type) const override;

    EntitySet getParentStarStmtType(Statement &statement, StatementType type) const override;

    EntitySet getParentWildcardType(StatementType type) const override;

    EntitySet getParentStarWildcardType(StatementType type) const override;

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

    EntitySet getCallees() const override;

    EntitySet getCalleesStar() const override;

    EntitySet getCallers() const override;

    EntitySet getCallersStar() const override;

    EntityPairSet getCallsPair() const override;

    EntityPairSet getCallsStarPair() const override;

    EntitySet getCallers(Procedure &callee) const override;

    EntitySet getCallersStar(Procedure &callee) const override;

    EntitySet getCallees(Procedure &caller) const override;

    EntitySet getCalleesStar(Procedure &caller) const override;

    EntityPairSet getNextPair(StatementType formerType,
                                                        StatementType latterType) const override;

    EntityPairSet getNextStarPair(StatementType formerType,
                                                            StatementType latterType) const override;

    EntitySet getNextStarSameStmt(StatementType stmtType) const override;

    EntitySet getNextTypeStmt(StatementType type, Statement &statement) const override;

    EntitySet getNextStarTypeStmt(StatementType type, Statement &statement) const override;

    EntitySet getNextTypeWildcard(StatementType type) const override;

    EntitySet getNextStarTypeWildcard(StatementType type) const override;

    EntitySet getNextStmtType(Statement &statement, StatementType type) const override;

    EntitySet getNextStarStmtType(Statement &statement, StatementType type) const override;

    EntitySet getNextWildcardType(StatementType type) const override;

    EntitySet getNextStarWildcardType(StatementType type) const override;

    bool isNext(Statement &statement1, Statement &statement2) const override;

    bool isNextStar(Statement &statement1, Statement &statement2) const override;

    bool hasNext() const override;

    bool hasNextStar() const override;

    bool hasBeforeStmt(Statement &statement) const override;

    bool hasBeforeStarStmt(Statement &statement) const override;

    bool hasAfterStmt(Statement &statement) const override;

    bool hasAfterStarStmt(Statement &statement) const override;

    EntitySet getAllIfPatternStmts() const override;

    EntitySet getIfStmtsByVar(Variable &var) const override;

    EntityPairSet getAllIfStmtVarPair() const override;

    EntitySet getAllWhilePatternStmts() const override;

    EntitySet getWhileStmtsByVar(Variable &var) const override;

    EntityPairSet getAllWhileStmtVarPair() const override;

    EntityPairSet getAffectsPair(StatementType formerType,
                                                           StatementType latterType) const override;

    EntitySet getAffectsTypeStmt(StatementType type, Statement &statement) const override;

    EntitySet getAffectsSameStmt(StatementType stmtType) const override;

    EntitySet getAffectsTypeWildcard(StatementType type) const override;

    EntitySet getAffectsStmtType(Statement &statement, StatementType type) const override;

    EntitySet getAffectsWildcardType(StatementType type) const override;

    bool isAffects(Statement &statement1, Statement &statement2) const override;

    bool hasAffects() const override;

    bool hasAffectedStmt(Statement &statement) const override;

    bool hasAffectsStmt(Statement &statement) const override;
};