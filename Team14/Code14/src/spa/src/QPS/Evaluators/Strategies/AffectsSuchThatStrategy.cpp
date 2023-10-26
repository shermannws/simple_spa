#include "AffectsSuchThatStrategy.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"
#include "QPS/QPSUtil.h"

AffectsSuchThatStrategy::AffectsSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader)
    : SuchThatStrategy(std::move(pkbReader)) {}

std::shared_ptr<Result> AffectsSuchThatStrategy::evaluateSynSyn(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    if (leftRef == rightRef) {
        res->setTuples(std::vector<Entity>{});
        return res;
    }
    auto leftEntityType = leftRef.getEntityType();
    auto rightEntityType = rightRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    res->setTuples(pkbReader->getAffectsPair(QPSUtil::entityToStmtMap.at(leftEntityType),
                                             QPSUtil::entityToStmtMap.at(rightEntityType)));
    return res;
}

std::shared_ptr<Result> AffectsSuchThatStrategy::evaluateSynAny(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    if (rightRef.isRootType(RootType::Integer)) {
        auto rightRep = rightRef.getRep();
        Statement s = Statement(stoi(rightRep), StatementType::Stmt);
        res->setTuples(pkbReader->getAffectsTypeStmt(QPSUtil::entityToStmtMap.at(leftEntityType), s));
    } else {
        res->setTuples(pkbReader->getAffectsTypeWildcard(QPSUtil::entityToStmtMap.at(leftEntityType)));
    }
    return res;
}

std::shared_ptr<Result> AffectsSuchThatStrategy::evaluateAnySyn(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    auto rightEntityType = rightRef.getEntityType();
    auto rightSyn = rightRef.getRep();
    if (leftRef.isRootType(RootType::Integer)) {
        auto leftRep = leftRef.getRep();
        Statement s = Statement(stoi(leftRep), StatementType::Stmt);
        res->setTuples(pkbReader->getAffectsStmtType(s, QPSUtil::entityToStmtMap.at(rightEntityType)));
    } else {
        res->setTuples(pkbReader->getAffectsWildcardType(QPSUtil::entityToStmtMap.at(rightEntityType)));
    }
    return res;
}

std::shared_ptr<Result> AffectsSuchThatStrategy::evaluateBoolean(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    bool isLeftInt = leftRef.isRootType(RootType::Integer);
    bool isRightInt = rightRef.isRootType(RootType::Integer);
    auto leftRep = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    if (isLeftInt && isRightInt) {
        Statement s1 = Statement(stoi(leftRep), StatementType::Stmt);
        Statement s2 = Statement(stoi(rightRep), StatementType::Stmt);
        res->setBoolResult(pkbReader->isAffects(s1, s2));
    } else if (isLeftInt) {
        Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
        res->setBoolResult(pkbReader->hasAffectedStmt(s));
    } else if (isRightInt) {
        Statement s = Statement(stoi(rightRep), StatementType::Stmt);
        res->setBoolResult(pkbReader->hasAffectsStmt(s));
    } else {
        res->setBoolResult(pkbReader->hasAffects());
    }
    return res;
}
