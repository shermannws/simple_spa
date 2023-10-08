#include "CallsStarSuchThatStrategy.h"


CallsStarSuchThatStrategy::CallsStarSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader) : SuchThatStrategy(std::move(pkbReader)) {}

std::shared_ptr<Result> CallsStarSuchThatStrategy::evaluateSynSyn(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    std::unordered_map<std::string, int> indices {{leftRef.getRep(), 0}, {rightRef.getRep(), 1}};
    res->setSynIndices(indices);
    //res->setTuples(pkbReader->getCallsStar());
    return res;
}

std::shared_ptr<Result> CallsStarSuchThatStrategy::evaluateSynAny(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    std::unordered_map<std::string, int> indices {{leftRef.getRep(), 0}};
    res->setSynIndices(indices);
    if (rightRef.isRootType(RootType::Wildcard)) {
        //res->setTuples(pkbReader->getCallersStar());
    }
    if (rightRef.isRootType(RootType::Ident)) {
        //res->setTuples(pkbReader->getCallersStar(rightRef.getRep()));
    }
    return res;
}

std::shared_ptr<Result> CallsStarSuchThatStrategy::evaluateAnySyn(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    std::unordered_map<std::string, int> indices {{rightRef.getRep(), 0}};
    res->setSynIndices(indices);
    if (leftRef.isRootType(RootType::Wildcard)) {
        //res->setTuples(pkbReader->getCalleesStar());
    }
    if (leftRef.isRootType(RootType::Ident)) {
        //res->setTuples(pkbReader->getCalleesStar(rightRef.getRep()));
    }
    return res;
}

std::shared_ptr<Result> CallsStarSuchThatStrategy::evaluateBoolean(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    bool isLeftIdent = leftRef.isRootType(RootType::Ident);
    bool isRightIdent = rightRef.isRootType(RootType::Ident);
    if (isLeftIdent && isRightIdent) {
        //res->setBoolResult(pkbReader->CallsStar(leftRef.getRep(), rightRef.getRep()));
    }
    else if (isLeftIdent) {
        //res->setBoolResult(pkbReader->isCallerStar(leftRef.getRep()));
    }
    else if (isRightIdent) {
        //res->setBoolResult(pkbReader->isCalleeStar(rightRef.getRep()));
    } else {
        //res->setBoolResult(pkbReader->hasCallsStar());
    }
    return res;
}
