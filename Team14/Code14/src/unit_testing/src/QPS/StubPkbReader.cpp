#include "StubPkbReader.h"

StubPkbReader::StubPkbReader() = default;

std::vector<Entity> StubPkbReader::getAllVariables() const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getAllConstants() const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getAllProcedures() const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getAllStatements() const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getAllRead() const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getAllPrint() const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getAllWhile() const {
    return std::vector<Entity>{
        Statement(10, StatementType::While),
        Statement(13, StatementType::While),
        Statement(15, StatementType::While),
    };
}

std::vector<Entity> StubPkbReader::getAllIf() const {
    return std::vector<Entity>();
}

std::vector<std::vector<Entity>> StubPkbReader::getUsesStmtPair(StatementType type) const {
    std::vector<Entity> pair1 = {Statement(1, StatementType::Assign), Variable("var")};
    std::vector<Entity> pair2 = {Statement(2, StatementType::Assign), Variable("var")};
    return std::vector<std::vector<Entity>>({pair1, pair2});
}

std::vector<std::vector<Entity>> StubPkbReader::getUsesProcPair() const {
    std::vector<Entity> pair1 = {Procedure("ProcedureName"), Variable("hello123")};
    std::vector<Entity> pair2 = {Procedure("ProcedureName2"), Variable("hello321")};
    return std::vector<std::vector<Entity>>({pair1, pair2});
}

std::vector<Entity> StubPkbReader::getUsesTypeIdent(StatementType type, Variable& var) const {
    return std::vector<Entity>{
        Statement(2, StatementType::If),
        Statement(4, StatementType::If),
        Statement(5, StatementType::If),
    };
}

std::vector<Entity> StubPkbReader::getUsesProcIdent(Variable& var) const {
    return std::vector<Entity>{
            Procedure("ProcedureName")
    };
};

std::vector<Entity> StubPkbReader::getUsesStmt(StatementType type) const {
    return std::vector<Entity>{
            Statement(1, StatementType::Assign),
            Statement(3, StatementType::Call),
    };
}

std::vector<Entity> StubPkbReader::getUsesProc() const {
    return {};
}

std::vector<Entity> StubPkbReader::getUsesVar(Statement& stmt) const {
    return std::vector<Entity>{
        Variable("name"),
        Variable("asdfghjkl")
    };
}

std::vector<Entity> StubPkbReader::getUsesVar(Procedure& proc) const {
    return std::vector<Entity>{
        Variable("proc"),
        Variable("anotherVar")
    };
}

bool StubPkbReader::isStmtUsesVar(Statement& stmt, Variable& var) const {
    return true;
}

bool StubPkbReader::isProcUsesVar(Procedure& proc, Variable& var) const {
    return false;
}

bool StubPkbReader::hasUses(Statement& stmt) const {
    return false;
}

bool StubPkbReader::hasUses(Procedure& proc) const {
    return true;
}

std::vector<std::vector<Entity>> StubPkbReader::getFollowsPair(StatementType formerType, StatementType latterType) const {
    return std::vector<std::vector<Entity>>();
}

std::vector<std::vector<Entity>> StubPkbReader::getFollowsStarPair(StatementType formerType, StatementType latterType) const {
    return std::vector<std::vector<Entity>>();
}

std::vector<Entity> StubPkbReader::getFollowsTypeStmt(StatementType type, Statement& statement) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getFollowsStarTypeStmt(StatementType type, Statement& statement) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getFollowsTypeWildcard(StatementType type) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getFollowsStarTypeWildcard(StatementType type) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getFollowsStmtType(Statement& statement, StatementType type) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getFollowsStarStmtType(Statement& statement, StatementType type) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getFollowsWildcardType(StatementType type) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getFollowsStarWildcardType(StatementType type) const {
    return std::vector<Entity>();
}

bool StubPkbReader::isFollows(Statement& statement1, Statement& statement2) const {
    return false;
}

bool StubPkbReader::isFollowsStar(Statement& statement1, Statement& statement2) const  {
    return false;
}

bool StubPkbReader::hasFollows() const {
    return false;
}

bool StubPkbReader::hasFollowsStar() const {
    return false;
}

bool StubPkbReader::hasLatterStmt(Statement& statement) const {
    return false;
}

bool StubPkbReader::hasFormerStmt(Statement& statement) const {
    return false;
}

bool StubPkbReader::hasLatterStarStmt(Statement& statement) const {
    return false;
}

bool StubPkbReader::hasFormerStarStmt(Statement& statement) const {
    return false;
}

std::vector<std::vector<Entity>> StubPkbReader::getModifiesStmtPair(StatementType type) const {
    return std::vector<std::vector<Entity>>();
}

std::vector<std::vector<Entity>> StubPkbReader::getModifiesProcPair() const {
    return {};
}

std::vector<Entity> StubPkbReader::getModifiesTypeIdent(StatementType type, Variable& var) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getModifiesProcIdent(Variable& var) const {
    return {};
}

std::vector<Entity> StubPkbReader::getModifiesStmt(StatementType type) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getModifiesProc() const {
    return {};
}

std::vector<Entity> StubPkbReader::getModifiesVar(Statement& stmt) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getModifiesVar(Procedure& proc) const {
    return {};
}

bool StubPkbReader::isStmtModifiesVar(Statement& stmt, Variable& var) const {
    return false;
}

bool StubPkbReader::isProcModifiesVar(Procedure& proc, Variable& var) const {
    return false;
}

bool StubPkbReader::hasModifies(Statement& stmt) const {
    return false;
}

bool StubPkbReader::hasModifies(Procedure& proc) const {
    return false;
}

// Pattern queries i.e. pattern a (...,...)
// pattern a (_,_)
std::vector<Entity> StubPkbReader::getAllAssign() const {
    return std::vector<Entity>{Statement(1, StatementType::Assign),
                               Statement(2, StatementType::Assign),
                               Statement(3, StatementType::Assign)};
}

// pattern a (_, "x")
std::vector<Entity> StubPkbReader::getAssignStmtsByRhs(std::string& rhs, bool hasRhsWildCard) const {
    return std::vector<Entity>{Statement(4, StatementType::Assign),
                               Statement(5, StatementType::Assign)};
}

// pattern a (v, _)
std::vector<std::vector<Entity>> StubPkbReader::getAllAssignStmtVarPair() const {
    std::vector<Entity> pair1 = {Statement(1, StatementType::Assign), Variable("var1")};
    std::vector<Entity> pair2 = {Statement(1, StatementType::Assign), Variable("var2")};
    std::vector<Entity> pair3 = {Statement(2, StatementType::Assign), Variable("var3")};
    return std::vector<std::vector<Entity>>({pair1, pair2, pair3});
}

// pattern a (v, "x")
std::vector<std::vector<Entity>> StubPkbReader::getAssignStmtsVarPairByRhs(std::string& rhs, bool hasWildCard) const {
    std::vector<Entity> pair1 = {Statement(1, StatementType::Assign), Variable("var1")};
    std::vector<Entity> pair2 = {Statement(1, StatementType::Assign), Variable("var2")};
    std::vector<Entity> pair3 = {Statement(2, StatementType::Assign), Variable("var3")};
    return std::vector<std::vector<Entity>>({pair1, pair2, pair3});
}

// pattern a ("x", _)
std::vector<Entity> StubPkbReader::getAssignStmtsByLhs(Variable& lhs) const {
    return std::vector<Entity>{Statement(6, StatementType::Assign)};
}

// pattern a ("x", "x")
std::vector<Entity> StubPkbReader::getAssignStmtsByLhsRhs(Variable& lhs, std::string& rhs, bool hasRhsWildCard) const {
    if (lhs == Variable("noneCase")) {
        return std::vector<Entity>();
    }
    return std::vector<Entity>{Statement(100, StatementType::Assign),
                               Statement(100000, StatementType::Assign)};
}

std::vector<std::vector<Entity>> StubPkbReader::getParentPair(StatementType formerType, StatementType latterType) const {
    return std::vector<std::vector<Entity>>();
}

std::vector<std::vector<Entity>> StubPkbReader::getParentStarPair(StatementType formerType, StatementType latterType) const {
    return std::vector<std::vector<Entity>>();
}

std::vector<Entity> StubPkbReader::getParentTypeStmt(StatementType type, Statement& statement) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getParentStarTypeStmt(StatementType type, Statement& statement) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getParentTypeWildcard(StatementType type) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getParentStarTypeWildcard(StatementType type) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getParentStmtType(Statement& statement, StatementType type) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getParentStarStmtType(Statement& statement, StatementType type) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getParentWildcardType(StatementType type) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getParentStarWildcardType(StatementType type) const {
    return std::vector<Entity>();
}

bool StubPkbReader::isParent(Statement& statement1, Statement& statement2) const {
    return false;
}

bool StubPkbReader::isParentStar(Statement& statement1, Statement& statement2) const  {
    return false;
}

bool StubPkbReader::hasParent() const {
    return false;
}

bool StubPkbReader::hasParentStar() const {
    return false;
}

bool StubPkbReader::hasParentStmt(Statement& statement) const {
    return false;
}

bool StubPkbReader::hasParentStarStmt(Statement& statement) const {
    return false;
}

bool StubPkbReader::hasChildStmt(Statement& statement) const {
    return false;
}

bool StubPkbReader::hasChildStarStmt(Statement& statement) const {
    return false;
}