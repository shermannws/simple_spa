#include "ModifiesSSuchThatStrategy.h"
#include "Commons/Entities/Entity.h"

Result ModifiesSSuchThatStrategy::evaluateSynSyn(std::shared_ptr<PkbReader> pkbReader, Ref& leftRef, Ref& rightRef) const {
    Result res;
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    res.setTuples(pkbReader->getModifiesStmtPair(stmtMap.at(leftEntityType)));

    std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
    res.setSynIndices(indices);
    return res;
}

Result ModifiesSSuchThatStrategy::evaluateSynIdent(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    Variable v = Variable(rightRep);
    res.setTuples(pkbReader->getModifiesTypeIdent(stmtMap.at(leftEntityType), v));

    std::unordered_map<std::string, int> indices {{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result ModifiesSSuchThatStrategy::evaluateSynWild(std::shared_ptr<PkbReader> pkbReader, Ref& leftRef, Ref& rightRef) const {
    Result res;
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    res.setTuples(pkbReader->getModifiesStmt(stmtMap.at(leftEntityType)));

    std::unordered_map<std::string, int> indices{{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result ModifiesSSuchThatStrategy::evaluateIntSyn(std::shared_ptr<PkbReader> pkbReader, Ref& leftRef, Ref& rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    Statement s = Statement(stoi(leftRep), StatementType::Stmt);
    res.setTuples(pkbReader->getModifiesVar(s));

    std::unordered_map<std::string, int> indices{{rightSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result ModifiesSSuchThatStrategy::evaluateIntIdent(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    Statement s = Statement(stoi(leftRep), StatementType::Stmt);
    Variable v = Variable(rightRep);
    res.setBoolResult(pkbReader->isStmtModifiesVar(s, v));
    return res;
}

Result ModifiesSSuchThatStrategy::evaluateIntWild(std::shared_ptr<PkbReader> pkbReader, Ref& leftRef, Ref& rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
    res.setBoolResult(pkbReader->hasModifies(s));
    return res;
}
