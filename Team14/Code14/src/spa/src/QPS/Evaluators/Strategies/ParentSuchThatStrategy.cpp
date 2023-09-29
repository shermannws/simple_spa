#include "ParentSuchThatStrategy.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"

Result ParentSuchThatStrategy::evaluateSynSyn(std::shared_ptr<PkbReader> pkbReader, Ref& leftRef, Ref& rightRef) const {
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

Result ParentSuchThatStrategy::evaluateSynInt(std::shared_ptr<PkbReader> pkbReader, Ref& leftRef, Ref& rightRef) const {
    Result res;
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    Statement s = Statement(stoi(rightRep), StatementType::Stmt);
    res.setTuples(pkbReader->getParentTypeStmt(stmtMap.at(leftEntityType), s));

    std::unordered_map<std::string, int> indices{{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result ParentSuchThatStrategy::evaluateSynWild(std::shared_ptr<PkbReader> pkbReader, Ref& leftRef, Ref& rightRef) const {
    Result res;
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    res.setTuples(pkbReader->getParentTypeWildcard(stmtMap.at(leftEntityType)));

    std::unordered_map<std::string, int> indices{{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result ParentSuchThatStrategy::evaluateIntSyn(std::shared_ptr<PkbReader> pkbReader, Ref& leftRef, Ref& rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    auto rightEntityType = rightRef.getEntityType();
    auto rightSyn = rightRef.getRep();
    Statement s = Statement(stoi(leftRep), StatementType::Stmt);
    res.setTuples(pkbReader->getParentStmtType(s, stmtMap.at(rightEntityType)));

    std::unordered_map<std::string, int> indices{{rightSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result ParentSuchThatStrategy::evaluateWildSyn(std::shared_ptr<PkbReader> pkbReader, Ref& leftRef, Ref& rightRef) const {
    Result res;
    auto rightEntityType = rightRef.getEntityType();
    auto rightSyn = rightRef.getRep();
    res.setTuples(pkbReader->getParentWildcardType(stmtMap.at(rightEntityType)));

    std::unordered_map<std::string, int> indices{{rightSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result ParentSuchThatStrategy::evaluateIntWild(std::shared_ptr<PkbReader> pkbReader, Ref& leftRef, Ref& rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
    res.setBoolResult(pkbReader->hasChildStmt(s));
    return res;
}

Result ParentSuchThatStrategy::evaluateWildInt(std::shared_ptr<PkbReader> pkbReader, Ref& leftRef, Ref& rightRef) const {
    Result res;
    auto rightRep = rightRef.getRep();
    Statement s = Statement(stoi(rightRep), StatementType::Stmt);
    res.setBoolResult(pkbReader->hasParentStmt(s));
    return res;
}

Result ParentSuchThatStrategy::evaluateIntInt(std::shared_ptr<PkbReader> pkbReader, Ref& leftRef, Ref& rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    Statement s1 = Statement(stoi(leftRep), StatementType::Stmt);
    Statement s2 = Statement(stoi(rightRep), StatementType::Stmt);
    res.setBoolResult(pkbReader->isParent(s1, s2));
    return res;
}

Result ParentSuchThatStrategy::evaluateWildWild(std::shared_ptr<PkbReader> pkbReader, Ref& leftRef, Ref& rightRef) const {
    Result res;
    res.setBoolResult(pkbReader->hasParent());
    return res;
}

