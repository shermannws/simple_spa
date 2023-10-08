#include "CallsSuchThatStrategy.h"

CallsSuchThatStrategy::CallsSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader) : SuchThatStrategy(std::move(pkbReader)) {}

std::shared_ptr<Result> CallsSuchThatStrategy::evaluateSynSyn(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    std::unordered_map<std::string, int> indices {{leftRef.getRep(), 0}, {rightRef.getRep(), 1}};
    res->setSynIndices(indices);
    //res->setTuples(pkbReader->getCalls());
    return res;
}

std::shared_ptr<Result> CallsSuchThatStrategy::evaluateSynAny(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    std::unordered_map<std::string, int> indices {{leftRef.getRep(), 0}};
    res->setSynIndices(indices);
    if (rightRef.isRootType(RootType::Wildcard)) {
        //res->setTuples(pkbReader->getCallers());
    }
    if (rightRef.isRootType(RootType::Ident)) {
        //res->setTuples(pkbReader->getCallers(rightRef.getRep()));
    }
    return res;
}

std::shared_ptr<Result> CallsSuchThatStrategy::evaluateAnySyn(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    std::unordered_map<std::string, int> indices {{rightRef.getRep(), 0}};
    res->setSynIndices(indices);
    if (leftRef.isRootType(RootType::Wildcard)) {
        //res->setTuples(pkbReader->getCallees());
    }
    if (leftRef.isRootType(RootType::Ident)) {
        //res->setTuples(pkbReader->getCallees(rightRef.getRep()));
    }
    return res;
}

std::shared_ptr<Result> CallsSuchThatStrategy::evaluateBoolean(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    bool isLeftIdent = leftRef.isRootType(RootType::Ident);
    bool isRightIdent = rightRef.isRootType(RootType::Ident);
    if (isLeftIdent && isRightIdent) {
        //res->setBoolResult(pkbReader->Calls(leftRef.getRep(), rightRef.getRep()));
    }
    else if (isLeftIdent) {
        //res->setBoolResult(pkbReader->isCaller(leftRef.getRep()));
    }
    else if (isRightIdent) {
        //res->setBoolResult(pkbReader->isCallee(rightRef.getRep()));
    } else {
        //res->setBoolResult(pkbReader->hasCalls());
    }
    return res;
}
