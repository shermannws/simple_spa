#include "PkbConcreteReader.h"

PkbConcreteReader::PkbConcreteReader(
    std::shared_ptr<PkbReaderManager> readerManager
) {
    this->readerManager = readerManager;
}

std::vector<Entity> PkbConcreteReader::getAllVariables() const {
    return this->readerManager->getAllVariables();
}

std::vector<Entity> PkbConcreteReader::getAllConstants() const {
    return this->readerManager->getAllConstants();
}

std::vector<Entity> PkbConcreteReader::getAllProcedures() const {
    return this->readerManager->getAllProcedures();
}

std::vector<Entity> PkbConcreteReader::getAllStatements() const {
    return this->readerManager->getAllStatements();
}

std::vector<Entity> PkbConcreteReader::getAllRead() const {
    return this->readerManager->getAllRead();
}

std::vector<Entity> PkbConcreteReader::getAllPrint() const {
    return this->readerManager->getAllPrint();
}

std::vector<Entity> PkbConcreteReader::getAllWhile() const {
    return this->readerManager->getAllWhile();
}

std::vector<Entity> PkbConcreteReader::getAllIf() const {
    return this->readerManager->getAllIf();
}

std::vector<std::vector<Entity>> PkbConcreteReader::getUsesStmtPair(StatementType type) const {
    return this->readerManager->getUsesStmtPair(type);
}

std::vector<Entity> PkbConcreteReader::getUsesTypeIdent(StatementType type, Variable& var) const {
    return this->readerManager->getUsesTypeIdent(type, var);
}

std::vector<Entity> PkbConcreteReader::getUsesStmt(StatementType type) const {
    return this->readerManager->getUsesStmt(type);
}

std::vector<Entity> PkbConcreteReader::getUsesVar(Statement& stmt) const {
    return this->readerManager->getUsesVar(stmt);
}

bool PkbConcreteReader::isStmtUsesVar(Statement& stmt, Variable& var) const {
    return this->readerManager->isStmtUsesVar(stmt, var);
}

bool PkbConcreteReader::hasUses(Statement& stmt) const {
    return this->readerManager->hasUses(stmt);
}

std::vector<std::vector<Entity>> PkbConcreteReader::getFollowsPair(StatementType formerType, StatementType latterType) const {
    return this->readerManager->getFollowsPair(formerType, latterType);
}

std::vector<std::vector<Entity>> PkbConcreteReader::getFollowsStarPair(StatementType formerType, StatementType latterType) const {
    return this->readerManager->getFollowsStarPair(formerType, latterType);
}

std::vector<Entity> PkbConcreteReader::getFollowsTypeStmt(StatementType type, Statement& statement) const {
    return this->readerManager->getFollowsTypeStmt(type, statement);
}

std::vector<Entity> PkbConcreteReader::getFollowsStarTypeStmt(StatementType type, Statement& statement) const {
    return this->readerManager->getFollowsStarTypeStmt(type, statement);
}

std::vector<Entity> PkbConcreteReader::getFollowsTypeWildcard(StatementType type) const {
    return this->readerManager->getFollowsTypeWildcard(type);
}

std::vector<Entity> PkbConcreteReader::getFollowsStarTypeWildcard(StatementType type) const {
    return this->readerManager->getFollowsStarTypeWildcard(type);
}

std::vector<Entity> PkbConcreteReader::getFollowsStmtType(Statement& statement, StatementType type) const {
    return this->readerManager->getFollowsStmtType(statement, type);
}

std::vector<Entity> PkbConcreteReader::getFollowsStarStmtType(Statement& statement, StatementType type) const {
    return this->readerManager->getFollowsStarStmtType(statement, type);
}

std::vector<Entity> PkbConcreteReader::getFollowsWildcardType(StatementType type) const {
    return this->readerManager->getFollowsWildcardType(type);
}

std::vector<Entity> PkbConcreteReader::getFollowsStarWildcardType(StatementType type) const {
    return this->readerManager->getFollowsStarWildcardType(type);
}

bool PkbConcreteReader::isFollows(Statement& statement1, Statement& statement2) const {
    return this->readerManager->isFollows(statement1, statement2);
}

bool PkbConcreteReader::isFollowsStar(Statement& statement1, Statement& statement2) const {
    return this->readerManager->isFollowsStar(statement1, statement2);
}

bool PkbConcreteReader::hasFollows() const {
    return this->readerManager->hasFollows();
}

bool PkbConcreteReader::hasLatterStmt(Statement& statement) const {
    return this->readerManager->hasLatterStmt(statement);
}

bool PkbConcreteReader::hasFormerStmt(Statement& statement) const {
    return this->readerManager->hasFormerStmt(statement);
}

bool PkbConcreteReader::hasLatterStarStmt(Statement& statement) const {
    return this->readerManager->hasLatterStarStmt(statement);
}

bool PkbConcreteReader::hasFormerStarStmt(Statement& statement) const {
    return this->readerManager->hasFormerStarStmt(statement);
}

std::vector<std::vector<Entity>> PkbConcreteReader::getModifiesStmtPair(StatementType type) const {
    return this->readerManager->getModifiesStmtPair(type);
}

std::vector<Entity> PkbConcreteReader::getModifiesTypeIdent(StatementType type, Variable& var) const {
    return this->readerManager->getModifiesTypeIdent(type, var);
}

std::vector<Entity> PkbConcreteReader::getModifiesStmt(StatementType type) const {
    return this->readerManager->getModifiesStmt(type);
}

std::vector<Entity> PkbConcreteReader::getModifiesVar(Statement& stmt) const {
    return this->readerManager->getModifiesVar(stmt);
}

bool PkbConcreteReader::isStmtModifiesVar(Statement& stmt, Variable& var) const {
    return this->readerManager->isStmtModifiesVar(stmt, var);
}

bool PkbConcreteReader::hasModifies(Statement& stmt) const {
    return this->readerManager->hasModifies(stmt);
}

// pattern a (_,_)
std::vector<Entity> PkbConcreteReader::getAllAssign() const {
    return this->readerManager->getAllAssign();
}

// pattern a (_, "x")
std::vector<Entity> PkbConcreteReader::getAssignStmtsByRhs(std::string& rhs, bool hasRhsWildCard) const {
    return this->readerManager->getAssignStmtsByRhs(rhs, hasRhsWildCard);
}

// pattern a (v, _)
std::vector<std::vector<Entity>> PkbConcreteReader::getAllAssignStmtVarPair() const {
    return this->readerManager->getAllAssignStmtVarPair();
}

// pattern a (v, "x")
std::vector<std::vector<Entity>> PkbConcreteReader::getAssignStmtsVarPairByRhs(std::string& rhs, bool hasWildCard) const {
    return this->readerManager->getAssignStmtsVarPairByRhs(rhs, hasWildCard);
}

// pattern a ("x", _)
std::vector<Entity> PkbConcreteReader::getAssignStmtsByLhs(Variable& lhs) const {
    return this->readerManager->getAssignStmtsByLhs(lhs);
}

// pattern a ("x", "x")
std::vector<Entity> PkbConcreteReader::getAssignStmtsByLhsRhs(Variable& lhs, std::string& rhs, bool hasRhsWildCard) const {
    return this->readerManager->getAssignStmtsByLhsRhs(lhs, rhs, hasRhsWildCard);
}

std::vector<std::vector<Entity>> PkbConcreteReader::getParentPair(StatementType formerType, StatementType latterType) const {
    return this->readerManager->getParentPair(formerType, latterType);
}

std::vector<std::vector<Entity>> PkbConcreteReader::getParentStarPair(StatementType formerType, StatementType latterType) const {
    return this->readerManager->getParentStarPair(formerType, latterType);
}

std::vector<Entity> PkbConcreteReader::getParentTypeStmt(StatementType type, Statement& statement) const {
    return this->readerManager->getParentTypeStmt(type, statement);
}

std::vector<Entity> PkbConcreteReader::getParentStarTypeStmt(StatementType type, Statement& statement) const {
    return this->readerManager->getParentStarTypeStmt(type, statement);
}

std::vector<Entity> PkbConcreteReader::getParentTypeWildcard(StatementType type) const {
    return this->readerManager->getParentTypeWildcard(type);
}

std::vector<Entity> PkbConcreteReader::getParentStarTypeWildcard(StatementType type) const {
    return this->readerManager->getParentStarTypeWildcard(type);
}

std::vector<Entity> PkbConcreteReader::getParentStmtType(Statement& statement, StatementType type) const {
    return this->readerManager->getParentStmtType(statement, type);
}

std::vector<Entity> PkbConcreteReader::getParentStarStmtType(Statement& statement, StatementType type) const {
    return this->readerManager->getParentStarStmtType(statement, type);
}

std::vector<Entity> PkbConcreteReader::getParentWildcardType(StatementType type) const {
    return this->readerManager->getParentWildcardType(type);
}

std::vector<Entity> PkbConcreteReader::getParentStarWildcardType(StatementType type) const {
    return this->readerManager->getParentStarWildcardType(type);
}

bool PkbConcreteReader::isParent(Statement& statement1, Statement& statement2) const {
    return this->readerManager->isParent(statement1, statement2);
}

bool PkbConcreteReader::isParentStar(Statement& statement1, Statement& statement2) const {
    return this->readerManager->isParentStar(statement1, statement2);
}

bool PkbConcreteReader::hasParent() const {
    return this->readerManager->hasParent();
}

bool PkbConcreteReader::hasParentStmt(Statement& statement) const {
    return this->readerManager->hasParentStmt(statement);
}

bool PkbConcreteReader::hasParentStarStmt(Statement& statement) const {
    return this->readerManager->hasParentStarStmt(statement);
}

bool PkbConcreteReader::hasChildStmt(Statement& statement) const {
    return this->readerManager->hasChildStmt(statement);
}

bool PkbConcreteReader::hasChildStarStmt(Statement& statement) const {
    return this->readerManager->hasChildStarStmt(statement);
}