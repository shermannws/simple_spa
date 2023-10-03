#include "ParentSuchThatStrategy.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"

ParentSuchThatStrategy::ParentSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader) : SuchThatStrategy(std::move(pkbReader)) {}

Result ParentSuchThatStrategy::evaluateSynSyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    if (leftRef == rightRef) {
        res.setBoolResult(false);
        return res;
    }
    auto leftEntityType = leftRef.getEntityType();
    auto rightEntityType = rightRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    res.setTuples(pkbReader->getParentPair(stmtMap.at(leftEntityType), stmtMap.at(rightEntityType)));

    std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
    res.setSynIndices(indices);
    return res;
}

Result ParentSuchThatStrategy::evaluateSynAny(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    if (rightRef.isRootType(RootType::Integer)) {
        auto rightRep = rightRef.getRep();
        Statement s = Statement(stoi(rightRep), StatementType::Stmt);
        res.setTuples(pkbReader->getParentTypeStmt(stmtMap.at(leftEntityType), s));
    } else {
        res.setTuples(pkbReader->getParentTypeWildcard(stmtMap.at(leftEntityType)));
    }
    std::unordered_map<std::string, int> indices{{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result ParentSuchThatStrategy::evaluateAnySyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto rightEntityType = rightRef.getEntityType();
    auto rightSyn = rightRef.getRep();
    if (leftRef.isRootType(RootType::Integer)) {
        auto leftRep = leftRef.getRep();
        Statement s = Statement(stoi(leftRep), StatementType::Stmt);
        res.setTuples(pkbReader->getParentStmtType(s, stmtMap.at(rightEntityType)));
    } else {
        res.setTuples(pkbReader->getParentWildcardType(stmtMap.at(rightEntityType)));
    }
    std::unordered_map<std::string, int> indices{{rightSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result ParentSuchThatStrategy::evaluateBoolean(Ref &leftRef, Ref &rightRef) const {
    Result res;
    bool isLeftInt = leftRef.isRootType(RootType::Integer);
    bool isRightInt = rightRef.isRootType(RootType::Integer);
    auto leftRep = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    if (isLeftInt && isRightInt) {
        Statement s1 = Statement(stoi(leftRep), StatementType::Stmt);
        Statement s2 = Statement(stoi(rightRep), StatementType::Stmt);
        res.setBoolResult(pkbReader->isParent(s1, s2));
    } else if (isLeftInt) {
        Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
        res.setBoolResult(pkbReader->hasChildStmt(s));
    } else if (isRightInt) {
        Statement s = Statement(stoi(rightRep), StatementType::Stmt);
        res.setBoolResult(pkbReader->hasParentStmt(s));
    } else {
        res.setBoolResult(pkbReader->hasParent());
    }
    return res;
}

