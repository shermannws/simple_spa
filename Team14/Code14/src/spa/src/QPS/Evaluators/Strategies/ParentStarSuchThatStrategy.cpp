#include "ParentStarSuchThatStrategy.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"


ParentStarSuchThatStrategy::ParentStarSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader) : SuchThatStrategy(std::move(pkbReader)) {}

Result ParentStarSuchThatStrategy::evaluateSynSyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    if (leftRef == rightRef) {
        res.setBoolResult(false);
        return res;
    }
    auto leftEntityType = leftRef.getEntityType();
    auto rightEntityType = rightRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    auto rightSyn = rightRef.getRep();
    res.setTuples(pkbReader->getParentStarPair(stmtMap.at(leftEntityType), stmtMap.at(rightEntityType)));

    std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
    res.setSynIndices(indices);
    return res;
}

Result ParentStarSuchThatStrategy::evaluateSynInt(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    Statement s = Statement(stoi(rightRep), StatementType::Stmt);
    res.setTuples(pkbReader->getParentStarTypeStmt(stmtMap.at(leftEntityType), s));

    std::unordered_map<std::string, int> indices{{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result ParentStarSuchThatStrategy::evaluateSynWild(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftEntityType = leftRef.getEntityType();
    auto leftSyn = leftRef.getRep();
    res.setTuples(pkbReader->getParentStarTypeWildcard(stmtMap.at(leftEntityType)));

    std::unordered_map<std::string, int> indices{{leftSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result ParentStarSuchThatStrategy::evaluateIntSyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    auto rightEntityType = rightRef.getEntityType();
    auto rightSyn = rightRef.getRep();
    Statement s = Statement(stoi(leftRep), StatementType::Stmt);
    res.setTuples(pkbReader->getParentStarStmtType(s, stmtMap.at(rightEntityType)));

    std::unordered_map<std::string, int> indices{{rightSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result ParentStarSuchThatStrategy::evaluateWildSyn(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto rightEntityType = rightRef.getEntityType();
    auto rightSyn = rightRef.getRep();
    res.setTuples(pkbReader->getParentStarWildcardType(stmtMap.at(rightEntityType)));

    std::unordered_map<std::string, int> indices{{rightSyn, 0}};
    res.setSynIndices(indices);
    return res;
}

Result ParentStarSuchThatStrategy::evaluateIntWild(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
    res.setBoolResult(pkbReader->hasChildStarStmt(s));
    return res;
}

Result ParentStarSuchThatStrategy::evaluateWildInt(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto rightRep = rightRef.getRep();
    Statement s = Statement(stoi(rightRep), StatementType::Stmt);
    res.setBoolResult(pkbReader->hasParentStarStmt(s));
    return res;
}

Result ParentStarSuchThatStrategy::evaluateIntInt(Ref &leftRef, Ref &rightRef) const {
    Result res;
    auto leftRep = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    Statement s1 = Statement(stoi(leftRep), StatementType::Stmt);
    Statement s2 = Statement(stoi(rightRep), StatementType::Stmt);
    res.setBoolResult(pkbReader->isParentStar(s1, s2));
    return res;
}

Result ParentStarSuchThatStrategy::evaluateWildWild(Ref &leftRef, Ref &rightRef) const {
    Result res;
    res.setBoolResult(pkbReader->hasParentStar());
    return res;
}

