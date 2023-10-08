#include "NextStarSuchThatStrategy.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"
#include "QPS/QPSUtil.h"

NextStarSuchThatStrategy::NextStarSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader) : SuchThatStrategy(std::move(pkbReader)) {}

Result NextStarSuchThatStrategy::evaluateSynSyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    if (leftRef == rightRef) {
        auto leftEntityType = leftRef.getEntityType();
        auto leftSyn = leftRef.getRep();
        res.setTuples(pkbReader->getNextStarSameStmt(QPSUtil::entityToStmtMap.at(leftEntityType)));
        std::unordered_map<std::string, int> indices {{leftSyn, 0}};
        res.setSynIndices(indices);
        return res;
    }
    auto leftEntityType = leftRef.getEntityType();
    auto rightEntityType = rightRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    res.setTuples(pkbReader->getNextStarPair(QPSUtil::entityToStmtMap.at(leftEntityType),
                                         QPSUtil::entityToStmtMap.at(rightEntityType)));

    std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
    res.setSynIndices(indices);
    return res;
}

Result NextStarSuchThatStrategy::evaluateSynAny(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    if (rightRef.isRootType(RootType::Integer)) {
        auto rightRep = rightRef.getRep();
        Statement s = Statement(stoi(rightRep), StatementType::Stmt);
        res.setTuples(pkbReader->getNextStarTypeStmt(QPSUtil::entityToStmtMap.at(leftEntityType), s));
    } else {
        res.setTuples(pkbReader->getNextStarTypeWildcard(QPSUtil::entityToStmtMap.at(leftEntityType)));
    }
    std::unordered_map<std::string, int> indices{{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result NextStarSuchThatStrategy::evaluateAnySyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto rightEntityType = rightRef.getEntityType();
    auto rightSyn = rightRef.getRep();
    if (leftRef.isRootType(RootType::Integer)) {
        auto leftRep = leftRef.getRep();
        Statement s = Statement(stoi(leftRep), StatementType::Stmt);
        res.setTuples(pkbReader->getNextStarStmtType(s, QPSUtil::entityToStmtMap.at(rightEntityType)));
    } else {
        res.setTuples(pkbReader->getNextStarWildcardType(QPSUtil::entityToStmtMap.at(rightEntityType)));
    }
    std::unordered_map<std::string, int> indices{{rightSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result NextStarSuchThatStrategy::evaluateBoolean(Ref &leftRef, Ref &rightRef) const {
    Result res;
    bool isLeftInt = leftRef.isRootType(RootType::Integer);
    bool isRightInt = rightRef.isRootType(RootType::Integer);
    auto leftRep = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    if (isLeftInt && isRightInt) {
        Statement s1 = Statement(stoi(leftRep), StatementType::Stmt);
        Statement s2 = Statement(stoi(rightRep), StatementType::Stmt);
        res.setBoolResult(pkbReader->isNextStar(s1, s2));
    } else if (isLeftInt) {
        Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
        res.setBoolResult(pkbReader->hasAfterStarStmt(s));
    } else if (isRightInt) {
        Statement s = Statement(stoi(rightRep), StatementType::Stmt);
        res.setBoolResult(pkbReader->hasBeforeStarStmt(s));
    } else {
        res.setBoolResult(pkbReader->hasNextStar());
    }
    return res;
}
