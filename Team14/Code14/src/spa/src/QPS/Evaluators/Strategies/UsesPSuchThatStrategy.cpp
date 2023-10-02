#include "UsesPSuchThatStrategy.h"
#include "Commons/Entities/Entity.h"

Result UsesPSuchThatStrategy::evaluateSynSyn(std::shared_ptr<PkbReader> pkbReader, Ref& leftRef, Ref& rightRef) const {
    Result res;
    auto leftSyn = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
//    res.setTuples(pkbReader->getUsesProcPair();

    std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
    res.setSynIndices(indices);
    return res;
}

Result UsesPSuchThatStrategy::evaluateSynIdent(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftSyn = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    Variable v = Variable(rightRep);
//    res.setTuples(pkbReader->getUsesProcIdent(v));

    std::unordered_map<std::string, int> indices {{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result UsesPSuchThatStrategy::evaluateSynWild(std::shared_ptr<PkbReader> pkbReader, Ref& leftRef, Ref& rightRef) const {
    Result res;
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
//    res.setTuples(pkbReader->getUsesProc());

    std::unordered_map<std::string, int> indices{{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result UsesPSuchThatStrategy::evaluateIdentSyn(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    Procedure s = Procedure(leftRep);
//    res.setTuples(pkbReader->getUsesVar(p));

    std::unordered_map<std::string, int> indices{{rightSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result UsesPSuchThatStrategy::evaluateIdentIdent(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    Procedure p = Procedure(leftRep);
    Variable v = Variable(rightRep);
//    res.setBoolResult(pkbReader->isProcUsesVar(p, v));
    return res;
}

Result UsesPSuchThatStrategy::evaluateIdentWild(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef,
                                               Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    Procedure p = Procedure(leftRep);
//    res.setBoolResult(pkbReader->hasUses(p));
    return res;
}