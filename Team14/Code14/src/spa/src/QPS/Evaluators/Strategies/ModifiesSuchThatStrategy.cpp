#include "ModifiesSuchThatStrategy.h"
#include "Commons/Entities/Entity.h"

ModifiesSuchThatStrategy::ModifiesSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader) : SuchThatStrategy(std::move(pkbReader)) {}

Result ModifiesSuchThatStrategy::evaluateSynSyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    if (leftEntityType == QueryEntityType::Procedure) { // Modifies(p,v)
//        res.setTuples(pkbReader->getModifiesProcPair();
    } else { // Modifies(s,v)
        res.setTuples(pkbReader->getModifiesStmtPair(stmtMap.at(leftEntityType)));
    }
    std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
    res.setSynIndices(indices);
    return res;
}

Result ModifiesSuchThatStrategy::evaluateSynAny(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftSyn = leftRef.getRep();
    auto leftEntityType = leftRef.getEntityType();
    auto rightRep = rightRef.getRep();
    Variable v = Variable(rightRep);
    bool isLeftProc = leftEntityType == QueryEntityType::Procedure;
    bool isRightIdent = rightRef.isRootType(RootType::Ident);
    if (isRightIdent && isLeftProc) { // Modifies(p,"var")
//        res.setTuples(pkbReader->getModifiesProcIdent(v));
    } else if (isRightIdent) { // Modifies(s, "var")
        res.setTuples(pkbReader->getModifiesTypeIdent(stmtMap.at(leftEntityType), v));
    } else if (isLeftProc) { // Modifies(p,_)
//        res.setTuples(pkbReader->getModifiesProc());
    } else { // Modifies(s,_)
        res.setTuples(pkbReader->getModifiesStmt(stmtMap.at(leftEntityType)));
    }
    std::unordered_map<std::string, int> indices {{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result ModifiesSuchThatStrategy::evaluateAnySyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    if (leftRef.isRootType(RootType::Integer)) { // Modifies(int,v)
        Statement s = Statement(stoi(leftRep), StatementType::Stmt);
        res.setTuples(pkbReader->getModifiesVar(s));
    } else { // Modifies("proc",v)
        Procedure s = Procedure(leftRep);
//    res.setTuples(pkbReader->getModifiesVar(p));
    }

    std::unordered_map<std::string, int> indices{{rightSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result ModifiesSuchThatStrategy::evaluateBoolean(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    bool isLeftIdent = leftRef.isRootType(RootType::Ident);
    bool isRightIdent = rightRef.isRootType(RootType::Ident);
    if (isLeftIdent && isRightIdent) { // Modifies("proc","var")
        Procedure p = Procedure(leftRep);
        Variable v = Variable(rightRep);
//        res.setBoolResult(pkbReader->isProcModifiesVar(p, v));
    } else if (isLeftIdent) { // Modifies("proc",_)
//        res.setBoolResult(pkbReader->hasModifies(p));
    } else if (isRightIdent) { // Modifies(int,"var")
        Statement s = Statement(stoi(leftRep), StatementType::Stmt);
        Variable v = Variable(rightRep);
        res.setBoolResult(pkbReader->isStmtModifiesVar(s, v));
    } else { // Modifies(int,_)
        Statement s = Statement(stoi(leftRep), StatementType::Stmt);
        res.setBoolResult(pkbReader->hasModifies(s));
    }
    return res;
}
