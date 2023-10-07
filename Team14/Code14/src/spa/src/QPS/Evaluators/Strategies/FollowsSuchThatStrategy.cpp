#include "FollowsSuchThatStrategy.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"
#include "QPS/QPSUtil.h"

FollowsSuchThatStrategy::FollowsSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader) : SuchThatStrategy(std::move(pkbReader)) {}

Result FollowsSuchThatStrategy::evaluateSynSyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    if (leftRef == rightRef) {
        res.setBoolResult(false);
        return res;
    }
    auto leftEntityType = leftRef.getEntityType();
    auto rightEntityType = rightRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    res.setTuples(pkbReader->getFollowsPair(QPSUtil::entityToStmtMap.at(leftEntityType),
                                            QPSUtil::entityToStmtMap.at(rightEntityType)));

    std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
    res.setSynIndices(indices);
    return res;
}

Result FollowsSuchThatStrategy::evaluateSynAny(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    if (rightRef.isRootType(RootType::Integer)) {
        auto rightRep = rightRef.getRep();
        Statement s = Statement(stoi(rightRep), StatementType::Stmt);
        res.setTuples(pkbReader->getFollowsTypeStmt(QPSUtil::entityToStmtMap.at(leftEntityType), s));
    } else {
        res.setTuples(pkbReader->getFollowsTypeWildcard(QPSUtil::entityToStmtMap.at(leftEntityType)));
    }
    std::unordered_map<std::string, int> indices{{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result FollowsSuchThatStrategy::evaluateAnySyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto rightEntityType = rightRef.getEntityType();
    auto rightSyn = rightRef.getRep();
    if (leftRef.isRootType(RootType::Integer)) {
        auto leftRep = leftRef.getRep();
        Statement s = Statement(stoi(leftRep), StatementType::Stmt);
        res.setTuples(pkbReader->getFollowsStmtType(s, QPSUtil::entityToStmtMap.at(rightEntityType)));
    } else {
        res.setTuples(pkbReader->getFollowsWildcardType(QPSUtil::entityToStmtMap.at(rightEntityType)));
    }
    std::unordered_map<std::string, int> indices{{rightSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result FollowsSuchThatStrategy::evaluateBoolean(Ref &leftRef, Ref &rightRef) const {
    Result res;
    bool isLeftInt = leftRef.isRootType(RootType::Integer);
    bool isRightInt = rightRef.isRootType(RootType::Integer);
    auto leftRep = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    if (isLeftInt && isRightInt) {
        Statement s1 = Statement(stoi(leftRep), StatementType::Stmt);
        Statement s2 = Statement(stoi(rightRep), StatementType::Stmt);
        res.setBoolResult(pkbReader->isFollows(s1, s2));
    } else if (isLeftInt) {
        Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
        res.setBoolResult(pkbReader->hasLatterStmt(s));
    } else if (isRightInt) {
        Statement s = Statement(stoi(rightRep), StatementType::Stmt);
        res.setBoolResult(pkbReader->hasFormerStmt(s));
    } else {
        res.setBoolResult(pkbReader->hasFollows());
    }
    return res;
}
