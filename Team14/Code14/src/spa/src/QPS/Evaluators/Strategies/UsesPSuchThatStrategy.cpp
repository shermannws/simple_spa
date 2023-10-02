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

Result UsesPSuchThatStrategy::evaluateSynIdent(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftSyn = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    Variable v = Variable(rightRep);
//    res.setTuples(pkbReader->getUsesProcIdent(v));

    std::unordered_map<std::string, int> indices {{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result UsesPSuchThatStrategy::evaluateSynWild(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
//    res.setTuples(pkbReader->getUsesProc());

    std::unordered_map<std::string, int> indices{{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result UsesPSuchThatStrategy::evaluateIdentSyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    Procedure s = Procedure(leftRep);
//    res.setTuples(pkbReader->getUsesVar(p));

    std::unordered_map<std::string, int> indices{{rightSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result UsesPSuchThatStrategy::evaluateIdentIdent(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    Procedure p = Procedure(leftRep);
    Variable v = Variable(rightRep);
//    res.setBoolResult(pkbReader->isProcUsesVar(p, v));
    return res;
}

Result UsesPSuchThatStrategy::evaluateIdentWild(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    Procedure p = Procedure(leftRep);
//    res.setBoolResult(pkbReader->hasUses(p));
    return res;
}