#include "CallsSuchThatStrategy.h"

CallsSuchThatStrategy::CallsSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader) : SuchThatStrategy(std::move(pkbReader)) {}

std::shared_ptr<Result> CallsSuchThatStrategy::evaluateSynSyn(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    std::unordered_map<std::string, int> indices {{leftRef.getRep(), 0}, {rightRef.getRep(), 1}};
    res->setSynIndices(indices);
    //res->setTuples(pkbReader->getCallsPair());
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
        Procedure callee = Procedure(leftRef.getRep());
        //res->setTuples(pkbReader->getCallers(callee));
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
        Procedure caller = Procedure(leftRef.getRep());
        //res->setTuples(pkbReader->getCallees(caller));
    }
    return res;
}

std::shared_ptr<Result> CallsSuchThatStrategy::evaluateBoolean(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    bool isLeftIdent = leftRef.isRootType(RootType::Ident);
    bool isRightIdent = rightRef.isRootType(RootType::Ident);
    if (isLeftIdent && isRightIdent) {
        Procedure lhs = Procedure(leftRef.getRep());
        Procedure rhs = Procedure(rightRef.getRep());
        //res->setBoolResult(pkbReader->isCalls(lhs, rhs));
    }
    else if (isLeftIdent) {
        Procedure p = Procedure(leftRef.getRep());
        //res->setBoolResult(pkbReader->isCaller(p));
    }
    else if (isRightIdent) {
        Procedure p = Procedure(rightRef.getRep());
        //res->setBoolResult(pkbReader->isCallee(p));
    } else {
        //res->setBoolResult(pkbReader->hasCalls());
    }
    return res;
}
