#include "UsesSuchThatStrategy.h"
#include "Commons/Entities/Entity.h"
#include "QPS/QPSUtil.h"

UsesSuchThatStrategy::UsesSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader)
    : SuchThatStrategy(std::move(pkbReader)) {}

std::shared_ptr<Result>
UsesSuchThatStrategy::evaluateSynSyn(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    if (leftEntityType == QueryEntityType::Procedure) {// Uses(p,v)
        res->setTuples(pkbReader->getUsesProcPair());
    } else {// Uses(s,v)
        res->setTuples(pkbReader->getUsesStmtPair(
                QPSUtil::entityToStmtMap.at(leftEntityType)));
    }
    return res;
}

std::shared_ptr<Result>
UsesSuchThatStrategy::evaluateSynAny(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    auto leftSyn = leftRef.getRep();
    auto leftEntityType = leftRef.getEntityType();
    auto rightRep = rightRef.getRep();
    Variable v = Variable(rightRep);
    bool isLeftProc = leftEntityType == QueryEntityType::Procedure;
    bool isRightIdent = rightRef.isRootType(RootType::Ident);
    if (isRightIdent && isLeftProc) {// Uses(p,"var")
        res->setTuples(pkbReader->getUsesProcIdent(v));
    } else if (isRightIdent) {// Uses(s, "var")
        res->setTuples(pkbReader->getUsesTypeIdent(
                QPSUtil::entityToStmtMap.at(leftEntityType), v));
    } else if (isLeftProc) {// Uses(p,_)
        res->setTuples(pkbReader->getUsesProc());
    } else {// Uses(s,_)
        res->setTuples(pkbReader->getUsesStmt(
                QPSUtil::entityToStmtMap.at(leftEntityType)));
    }
    return res;
}

std::shared_ptr<Result>
UsesSuchThatStrategy::evaluateAnySyn(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    auto leftRep = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    if (leftRef.isRootType(RootType::Integer)) {// Uses(int,v)
        Statement s = Statement(stoi(leftRep), StatementType::Stmt);
        res->setTuples(pkbReader->getUsesVar(s));
    } else {// Uses("proc",v)
        Procedure p = Procedure(leftRep);
        res->setTuples(pkbReader->getUsesVar(p));
    }
    return res;
}

std::shared_ptr<Result>
UsesSuchThatStrategy::evaluateBoolean(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    auto leftRep = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    bool isLeftIdent = leftRef.isRootType(RootType::Ident);
    bool isRightIdent = rightRef.isRootType(RootType::Ident);
    if (isLeftIdent && isRightIdent) {// Uses("proc","var")
        Procedure p = Procedure(leftRep);
        Variable v = Variable(rightRep);
        res->setBoolResult(pkbReader->isProcUsesVar(p, v));
    } else if (isLeftIdent) {// Uses("proc",_)
        Procedure p = Procedure(leftRep);
        res->setBoolResult(pkbReader->hasUses(p));
    } else if (isRightIdent) {// Uses(int,"var")
        Statement s = Statement(stoi(leftRep), StatementType::Stmt);
        Variable v = Variable(rightRep);
        res->setBoolResult(pkbReader->isStmtUsesVar(s, v));
    } else {// Uses(int,_)
        Statement s = Statement(stoi(leftRep), StatementType::Stmt);
        res->setBoolResult(pkbReader->hasUses(s));
    }
    return res;
}
