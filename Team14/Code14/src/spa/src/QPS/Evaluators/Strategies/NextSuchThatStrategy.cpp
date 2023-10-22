#include "NextSuchThatStrategy.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"
#include "QPS/QPSUtil.h"

NextSuchThatStrategy::NextSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader)
    : SuchThatStrategy(std::move(pkbReader)) {}

std::shared_ptr<Result> NextSuchThatStrategy::evaluateSynSyn(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    if (leftRef == rightRef) {
        res->setTuples(std::vector<Entity>());
        return res;
    }
    auto leftEntityType = leftRef.getEntityType();
    auto rightEntityType = rightRef.getEntityType();
    res->setTuples(pkbReader->getNextPair(QPSUtil::entityToStmtMap.at(leftEntityType),
                                          QPSUtil::entityToStmtMap.at(rightEntityType)));
    return res;
}

std::shared_ptr<Result> NextSuchThatStrategy::evaluateSynAny(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    auto leftEntityType = leftRef.getEntityType();
    if (rightRef.isRootType(RootType::Integer)) {
        auto rightRep = rightRef.getRep();
        Statement s = Statement(stoi(rightRep), StatementType::Stmt);
        res->setTuples(pkbReader->getNextTypeStmt(QPSUtil::entityToStmtMap.at(leftEntityType), s));
    } else {
        res->setTuples(pkbReader->getNextTypeWildcard(QPSUtil::entityToStmtMap.at(leftEntityType)));
    }
    return res;
}

std::shared_ptr<Result> NextSuchThatStrategy::evaluateAnySyn(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    auto rightEntityType = rightRef.getEntityType();
    if (leftRef.isRootType(RootType::Integer)) {
        auto leftRep = leftRef.getRep();
        Statement s = Statement(stoi(leftRep), StatementType::Stmt);
        res->setTuples(pkbReader->getNextStmtType(s, QPSUtil::entityToStmtMap.at(rightEntityType)));
    } else {
        res->setTuples(pkbReader->getNextWildcardType(QPSUtil::entityToStmtMap.at(rightEntityType)));
    }
    return res;
}

std::shared_ptr<Result> NextSuchThatStrategy::evaluateBoolean(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    bool isLeftInt = leftRef.isRootType(RootType::Integer);
    bool isRightInt = rightRef.isRootType(RootType::Integer);
    auto leftRep = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    if (isLeftInt && isRightInt) {
        Statement s1 = Statement(stoi(leftRep), StatementType::Stmt);
        Statement s2 = Statement(stoi(rightRep), StatementType::Stmt);
        res->setBoolResult(pkbReader->isNext(s1, s2));
    } else if (isLeftInt) {
        Statement s = Statement(stoi(leftRep), StatementType::Stmt);
        res->setBoolResult(pkbReader->hasAfterStmt(s));
    } else if (isRightInt) {
        Statement s = Statement(stoi(rightRep), StatementType::Stmt);
        res->setBoolResult(pkbReader->hasBeforeStmt(s));
    } else {
        res->setBoolResult(pkbReader->hasNext());
    }
    return res;
}
