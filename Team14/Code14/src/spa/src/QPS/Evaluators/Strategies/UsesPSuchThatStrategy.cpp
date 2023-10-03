#include "UsesPSuchThatStrategy.h"

#include <utility>
#include "Commons/Entities/Entity.h"

UsesPSuchThatStrategy::UsesPSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader) : SuchThatStrategy(std::move(pkbReader)) {}

Result UsesPSuchThatStrategy::evaluateSynSyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftSyn = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
//    res.setTuples(pkbReader->getUsesProcPair();

    std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
    res.setSynIndices(indices);
    return res;
}

Result UsesPSuchThatStrategy::evaluateSynAny(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftSyn = leftRef.getRep();
    if (rightRef.isRootType(RootType::Ident)) { // ident
        auto rightRep = rightRef.getRep();
        Variable v = Variable(rightRep);
//        res.setTuples(pkbReader->getUsesProcIdent(v));
    } else { // wildcard
//        res.setTuples(pkbReader->getUsesProc());
    }
    std::unordered_map<std::string, int> indices {{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result UsesPSuchThatStrategy::evaluateAnySyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    Procedure s = Procedure(leftRep);
//    res.setTuples(pkbReader->getUsesVar(p));

    std::unordered_map<std::string, int> indices{{rightSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result UsesPSuchThatStrategy::evaluateBoolean(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    Procedure p = Procedure(leftRep);
    if (rightRef.isRootType(RootType::Ident)) {
        auto rightRep = rightRef.getRep();
        Variable v = Variable(rightRep);
//        res.setBoolResult(pkbReader->isProcUsesVar(p, v));
    } else {
//        res.setBoolResult(pkbReader->hasUses(p));
    }
    return res;
}
