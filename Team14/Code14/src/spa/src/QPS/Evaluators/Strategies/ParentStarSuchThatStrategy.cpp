#include "ParentStarSuchThatStrategy.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"
#include "QPS/QPSUtil.h"


ParentStarSuchThatStrategy::ParentStarSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader) : SuchThatStrategy(std::move(pkbReader)) {}

Result ParentStarSuchThatStrategy::evaluateSynSyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    if (leftRef == rightRef) {
        res.setBoolResult(false);
        return res;
    }
    auto leftEntityType = leftRef.getEntityType();
    auto rightEntityType = rightRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    res.setTuples(pkbReader->getParentStarPair(QPSUtil::entityToStmtMap.at(leftEntityType),
                                               QPSUtil::entityToStmtMap.at(rightEntityType)));

    std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
    res.setSynIndices(indices);
    return res;
}

Result ParentStarSuchThatStrategy::evaluateSynAny(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    if (rightRef.isRootType(RootType::Integer)) {
        auto rightRep = rightRef.getRep();
        Statement s = Statement(stoi(rightRep), StatementType::Stmt);
        res.setTuples(pkbReader->getParentStarTypeStmt(QPSUtil::entityToStmtMap.at(leftEntityType), s));
    } else {
        res.setTuples(pkbReader->getParentStarTypeWildcard(QPSUtil::entityToStmtMap.at(leftEntityType)));
    }
    std::unordered_map<std::string, int> indices{{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result ParentStarSuchThatStrategy::evaluateAnySyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto rightEntityType = rightRef.getEntityType();
    auto rightSyn = rightRef.getRep();
    if (leftRef.isRootType(RootType::Integer)) {
        auto leftRep = leftRef.getRep();
        Statement s = Statement(stoi(leftRep), StatementType::Stmt);
        res.setTuples(pkbReader->getParentStarStmtType(s, QPSUtil::entityToStmtMap.at(rightEntityType)));
    } else {
        res.setTuples(pkbReader->getParentStarWildcardType(QPSUtil::entityToStmtMap.at(rightEntityType)));
    }
    std::unordered_map<std::string, int> indices{{rightSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result ParentStarSuchThatStrategy::evaluateBoolean(Ref &leftRef, Ref &rightRef) const {
    Result res;
    bool isLeftInt = leftRef.isRootType(RootType::Integer);
    bool isRightInt = rightRef.isRootType(RootType::Integer);
    auto leftRep = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    if (isLeftInt && isRightInt) {
        Statement s1 = Statement(stoi(leftRep), StatementType::Stmt);
        Statement s2 = Statement(stoi(rightRep), StatementType::Stmt);
        res.setBoolResult(pkbReader->isParentStar(s1, s2));
    } else if (isLeftInt) {
        Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
        res.setBoolResult(pkbReader->hasChildStarStmt(s));
    } else if (isRightInt) {
        Statement s = Statement(stoi(rightRep), StatementType::Stmt);
        res.setBoolResult(pkbReader->hasParentStarStmt(s));
    } else {
        res.setBoolResult(pkbReader->hasParentStar());
    }
    return res;
}
