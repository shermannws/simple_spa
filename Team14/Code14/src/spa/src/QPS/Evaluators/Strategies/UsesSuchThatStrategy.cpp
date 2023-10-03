#include "UsesSuchThatStrategy.h"
#include "Commons/Entities/Entity.h"


Result UsesSuchThatStrategy::evaluateSynSyn(std::shared_ptr<PkbReader> pkbReader, Ref& leftRef, Ref& rightRef) const {
    Result res;
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    res.setTuples(pkbReader->getUsesStmtPair(stmtMap.at(leftEntityType)));

    std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
    res.setSynIndices(indices);
    return res;
}

Result UsesSuchThatStrategy::evaluateSynIdent(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    Variable v = Variable(rightRep);
    res.setTuples(pkbReader->getUsesTypeIdent(stmtMap.at(leftEntityType), v));

    std::unordered_map<std::string, int> indices {{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result UsesSuchThatStrategy::evaluateSynWild(std::shared_ptr<PkbReader> pkbReader, Ref& leftRef, Ref& rightRef) const {
    Result res;
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    res.setTuples(pkbReader->getUsesStmt(stmtMap.at(leftEntityType)));

    std::unordered_map<std::string, int> indices{{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result UsesSuchThatStrategy::evaluateIntSyn(std::shared_ptr<PkbReader> pkbReader, Ref& leftRef, Ref& rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    Statement s = Statement(stoi(leftRep), StatementType::Stmt);
    res.setTuples(pkbReader->getUsesVar(s));

    std::unordered_map<std::string, int> indices{{rightSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result UsesSuchThatStrategy::evaluateIntIdent(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    Statement s = Statement(stoi(leftRep), StatementType::Stmt);
    Variable v = Variable(rightRep);
    res.setBoolResult(pkbReader->isStmtUsesVar(s, v));
    return res;
}

Result UsesSuchThatStrategy::evaluateIntWild(std::shared_ptr<PkbReader> pkbReader, Ref& leftRef, Ref& rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
    res.setBoolResult(pkbReader->hasUses(s));
    return res;
}

