#include "ModifiesSSuchThatStrategy.h"
#include "Commons/Entities/Entity.h"

ModifiesSSuchThatStrategy::ModifiesSSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader) : SuchThatStrategy(std::move(pkbReader)) {}

Result ModifiesSSuchThatStrategy::evaluateSynSyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    res.setTuples(pkbReader->getModifiesStmtPair(stmtMap.at(leftEntityType)));

    std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
    res.setSynIndices(indices);
    return res;
}

Result ModifiesSSuchThatStrategy::evaluateSynAny(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    if (rightRef.isRootType(RootType::Ident)) { // ident
        auto rightRep = rightRef.getRep();
        Variable v = Variable(rightRep);
        res.setTuples(pkbReader->getModifiesTypeIdent(stmtMap.at(leftEntityType), v));
    } else { // wildcard
        res.setTuples(pkbReader->getModifiesStmt(stmtMap.at(leftEntityType)));
    }
    std::unordered_map<std::string, int> indices {{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result ModifiesSSuchThatStrategy::evaluateAnySyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    Statement s = Statement(stoi(leftRep), StatementType::Stmt);
    res.setTuples(pkbReader->getModifiesVar(s));

    std::unordered_map<std::string, int> indices{{rightSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result ModifiesSSuchThatStrategy::evaluateBoolean(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    Statement s = Statement(stoi(leftRep), StatementType::Stmt);
    if (rightRef.isRootType(RootType::Ident)) {
        auto rightRep = rightRef.getRep();
        Variable v = Variable(rightRep);
        res.setBoolResult(pkbReader->isStmtModifiesVar(s, v));
    } else {
        res.setBoolResult(pkbReader->hasModifies(s));
    }
    return res;
}
