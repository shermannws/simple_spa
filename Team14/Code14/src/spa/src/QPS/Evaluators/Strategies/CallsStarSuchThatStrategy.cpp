#include "CallsStarSuchThatStrategy.h"


CallsStarSuchThatStrategy::CallsStarSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader) : SuchThatStrategy(std::move(pkbReader)) {}

std::shared_ptr<Result> CallsStarSuchThatStrategy::evaluateSynSyn(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    if (leftRef == rightRef) {
        return res;
    }
    res->setTuples(pkbReader->getCallsStarPair());
    return res;
}

std::shared_ptr<Result> CallsStarSuchThatStrategy::evaluateSynAny(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    if (rightRef.isRootType(RootType::Wildcard)) {
        res->setTuples(pkbReader->getCallersStar());
    }
    if (rightRef.isRootType(RootType::Ident)) {
        Procedure callee = Procedure(rightRef.getRep());
        res->setTuples(pkbReader->getCallersStar(callee));
    }
    return res;
}

std::shared_ptr<Result> CallsStarSuchThatStrategy::evaluateAnySyn(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    if (leftRef.isRootType(RootType::Wildcard)) {
        res->setTuples(pkbReader->getCalleesStar());
    }
    if (leftRef.isRootType(RootType::Ident)) {
        Procedure caller = Procedure(leftRef.getRep());
        res->setTuples(pkbReader->getCalleesStar(caller));
    }
    return res;
}

std::shared_ptr<Result> CallsStarSuchThatStrategy::evaluateBoolean(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    bool isLeftIdent = leftRef.isRootType(RootType::Ident);
    bool isRightIdent = rightRef.isRootType(RootType::Ident);
    if (isLeftIdent && isRightIdent) {
        Procedure lhs = Procedure(leftRef.getRep());
        Procedure rhs = Procedure(rightRef.getRep());
        res->setBoolResult(pkbReader->isCallsStar(lhs, rhs));
    }
    else if (isLeftIdent) {
        Procedure p = Procedure(leftRef.getRep());
        res->setBoolResult(pkbReader->isCallerStar(p));
    }
    else if (isRightIdent) {
        Procedure p = Procedure(rightRef.getRep());
        res->setBoolResult(pkbReader->isCalleeStar(p));
    } else {
        res->setBoolResult(pkbReader->hasCallsStar());
    }
    return res;
}
