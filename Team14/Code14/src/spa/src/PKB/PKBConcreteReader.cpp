#pragma once

#include "PkbConcreteReader.h"

PkbConcreteReader::PkbConcreteReader(
    std::shared_ptr<PkbReaderManager> readerManager
) {
    this->readerManager = readerManager;
}

std::vector<Entity> PkbConcreteReader::getAllAssign() const {
    return this->readerManager->getAllAssign();
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