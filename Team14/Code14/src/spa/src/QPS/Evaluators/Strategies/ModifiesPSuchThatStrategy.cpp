#include "ModifiesPSuchThatStrategy.h"
#include "Commons/Entities/Entity.h"

ModifiesPSuchThatStrategy::ModifiesPSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader) : SuchThatStrategy(std::move(pkbReader)) {}

Result ModifiesPSuchThatStrategy::evaluateSynSyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftSyn = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
//    res.setTuples(pkbReader->getModifiesProcPair();

    std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
    res.setSynIndices(indices);
    return res;
}

Result ModifiesPSuchThatStrategy::evaluateSynAny(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftSyn = leftRef.getRep();
    if (rightRef.isRootType(RootType::Ident)) { // ident
        auto rightRep = rightRef.getRep();
        Variable v = Variable(rightRep);
//        res.setTuples(pkbReader->getModifiesProcIdent(v));
    } else { // wildcard
//        res.setTuples(pkbReader->getModifiesProc());
    }
    std::unordered_map<std::string, int> indices {{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result ModifiesPSuchThatStrategy::evaluateAnySyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    Procedure s = Procedure(leftRep);
//    res.setTuples(pkbReader->getModifiesVar(p));

    std::unordered_map<std::string, int> indices{{rightSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result ModifiesPSuchThatStrategy::evaluateBoolean(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    Procedure p = Procedure(leftRep);
    if (rightRef.isRootType(RootType::Ident)) {
        auto rightRep = rightRef.getRep();
        Variable v = Variable(rightRep);
//        res.setBoolResult(pkbReader->isProcModifiesVar(p, v));
    } else {
//        res.setBoolResult(pkbReader->hasModifies(p));
    }
    return res;
}
