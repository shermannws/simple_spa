#include "FollowsStarSuchThatStrategy.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"

FollowsStarSuchThatStrategy::FollowsStarSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader) : SuchThatStrategy(std::move(pkbReader)) {}

Result FollowsStarSuchThatStrategy::evaluateSynSyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    if (leftRef == rightRef) {
        res.setBoolResult(false);
        return res;
    }
    auto leftEntityType = leftRef.getEntityType();
    auto rightEntityType = rightRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    res.setTuples(pkbReader->getFollowsStarPair(stmtMap.at(leftEntityType), stmtMap.at(rightEntityType)));

    std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
    res.setSynIndices(indices);
    return res;
}

Result FollowsStarSuchThatStrategy::evaluateSynInt(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    Statement s = Statement(stoi(rightRep), StatementType::Stmt);
    res.setTuples(pkbReader->getFollowsStarTypeStmt(stmtMap.at(leftEntityType), s));

    std::unordered_map<std::string, int> indices{{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result FollowsStarSuchThatStrategy::evaluateSynWild(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    res.setTuples(pkbReader->getFollowsStarTypeWildcard(stmtMap.at(leftEntityType)));

    std::unordered_map<std::string, int> indices{{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result FollowsStarSuchThatStrategy::evaluateIntSyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    auto rightEntityType = rightRef.getEntityType();
    auto rightSyn = rightRef.getRep();
    Statement s = Statement(stoi(leftRep), StatementType::Stmt);
    res.setTuples(pkbReader->getFollowsStarStmtType(s, stmtMap.at(rightEntityType)));

    std::unordered_map<std::string, int> indices{{rightSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result FollowsStarSuchThatStrategy::evaluateWildSyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto rightEntityType = rightRef.getEntityType();
    auto rightSyn = rightRef.getRep();
    res.setTuples(pkbReader->getFollowsStarWildcardType(stmtMap.at(rightEntityType)));

    std::unordered_map<std::string, int> indices{{rightSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result FollowsStarSuchThatStrategy::evaluateIntWild(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
    res.setBoolResult(pkbReader->hasLatterStarStmt(s));
    return res;
}

Result FollowsStarSuchThatStrategy::evaluateWildInt(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto rightRep = rightRef.getRep();
    Statement s = Statement(stoi(rightRep), StatementType::Stmt);
    res.setBoolResult(pkbReader->hasFormerStarStmt(s));
    return res;
}

Result FollowsStarSuchThatStrategy::evaluateIntInt(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    Statement s1 = Statement(stoi(leftRep), StatementType::Stmt);
    Statement s2 = Statement(stoi(rightRep), StatementType::Stmt);
    res.setBoolResult(pkbReader->isFollowsStar(s1, s2));
    return res;
}

Result FollowsStarSuchThatStrategy::evaluateWildWild(Ref &leftRef, Ref &rightRef) const {
    Result res;
    res.setBoolResult(pkbReader->hasFollowsStar());
    return res;
}

