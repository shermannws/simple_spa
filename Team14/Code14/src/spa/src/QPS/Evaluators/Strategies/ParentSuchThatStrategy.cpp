#include "ParentSuchThatStrategy.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"
#include "QPS/QPSUtil.h"

ParentSuchThatStrategy::ParentSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader)
        : SuchThatStrategy(std::move(pkbReader)) {}

std::shared_ptr<Result> ParentSuchThatStrategy::evaluateSynSyn(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    if (leftRef == rightRef) {
        res->setTuples(std::vector<Entity>{});
        return res;
    }
    auto leftEntityType = leftRef.getEntityType();
    auto rightEntityType = rightRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    res->setTuples(pkbReader->getParentPair(QPSUtil::entityToStmtMap.at(leftEntityType),
                                            QPSUtil::entityToStmtMap.at(rightEntityType)));

    return res;
}

std::shared_ptr<Result> ParentSuchThatStrategy::evaluateSynAny(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    if (rightRef.isRootType(RootType::Integer)) {
        auto rightRep = rightRef.getRep();
        Statement s = Statement(stoi(rightRep), StatementType::Stmt);
        res->setTuples(pkbReader->getParentTypeStmt(QPSUtil::entityToStmtMap.at(leftEntityType), s));
    } else {
        res->setTuples(pkbReader->getParentTypeWildcard(QPSUtil::entityToStmtMap.at(leftEntityType)));
    }
    return res;
}

std::shared_ptr<Result> ParentSuchThatStrategy::evaluateAnySyn(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    auto rightEntityType = rightRef.getEntityType();
    auto rightSyn = rightRef.getRep();
    if (leftRef.isRootType(RootType::Integer)) {
        auto leftRep = leftRef.getRep();
        Statement s = Statement(stoi(leftRep), StatementType::Stmt);
        res->setTuples(pkbReader->getParentStmtType(s, QPSUtil::entityToStmtMap.at(rightEntityType)));
    } else {
        res->setTuples(pkbReader->getParentWildcardType(QPSUtil::entityToStmtMap.at(rightEntityType)));
    }
    return res;
}

std::shared_ptr<Result> ParentSuchThatStrategy::evaluateBoolean(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    bool isLeftInt = leftRef.isRootType(RootType::Integer);
    bool isRightInt = rightRef.isRootType(RootType::Integer);
    auto leftRep = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    if (isLeftInt && isRightInt) {
        Statement s1 = Statement(stoi(leftRep), StatementType::Stmt);
        Statement s2 = Statement(stoi(rightRep), StatementType::Stmt);
        res->setBoolResult(pkbReader->isParent(s1, s2));
    } else if (isLeftInt) {
        Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
        res->setBoolResult(pkbReader->hasChildStmt(s));
    } else if (isRightInt) {
        Statement s = Statement(stoi(rightRep), StatementType::Stmt);
        res->setBoolResult(pkbReader->hasParentStmt(s));
    } else {
        res->setBoolResult(pkbReader->hasParent());
    }
    return res;
}
