#include "ParentStarSuchThatStrategy.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"

Result ParentStarSuchThatStrategy::evaluateClause(std::shared_ptr<Clause> clause, std::shared_ptr<PkbReader> pkbReader) const {
    std::shared_ptr<SuchThatClause> suchThat = std::dynamic_pointer_cast<SuchThatClause>(clause);
    Ref leftRef = suchThat->getFirstParam();
    RootType leftRootType = leftRef.getRootType();
    QueryEntityType leftEntityType = leftRef.getEntityType();
    Ref rightRef = suchThat->getSecondParam();
    RootType rightRootType = rightRef.getRootType();
    QueryEntityType rightEntityType = rightRef.getEntityType();
    Result res;

    if (leftRootType == RootType::Synonym && rightRootType == RootType::Synonym && leftRef.getRep() == rightRef.getRep()) { // Parent*(s,s)
        res.setBoolResult(false);
    } else if (leftRootType == RootType::Synonym && rightRootType == RootType::Synonym) { // Parent*(s1,s2)
        std::string leftSyn = leftRef.getRep();
        std::string rightSyn = rightRef.getRep();
        res.setTuples(pkbReader->getParentStarPair(stmtMap.at(leftEntityType), stmtMap.at(rightEntityType)));

        std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
        res.setSynIndices(indices);

    } else if (leftRootType == RootType::Synonym && rightRootType == RootType::Integer) { // Parent*(s,1)
        std::string syn = leftRef.getRep();
        Statement s = Statement(stoi(rightRef.getRep()), StatementType::Stmt);
        res.setTuples(pkbReader->getParentStarTypeStmt(stmtMap.at(leftEntityType), s));

        std::unordered_map<std::string, int> indices{{syn, 0}};
        res.setSynIndices(indices);

    } else if (leftRootType == RootType::Synonym && rightRootType == RootType::Wildcard) { // Parent*(s,_)
        std::string syn = leftRef.getRep();
        res.setTuples(pkbReader->getParentStarTypeWildcard(stmtMap.at(leftEntityType)));

        std::unordered_map<std::string, int> indices{{syn, 0}};
        res.setSynIndices(indices);

    } else if (leftRootType == RootType::Integer && rightRootType == RootType::Synonym) { // Parent*(1,s)
        std::string syn = rightRef.getRep();
        Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
        res.setTuples(pkbReader->getParentStarStmtType(s, stmtMap.at(rightEntityType)));

        std::unordered_map<std::string, int> indices{{syn, 0}};
        res.setSynIndices(indices);

    } else if (leftRootType == RootType::Wildcard && rightRootType == RootType::Synonym) { // Parent*(_,s)
        std::string syn = rightRef.getRep();
        res.setTuples(pkbReader->getParentStarWildcardType(stmtMap.at(rightEntityType)));

        std::unordered_map<std::string, int> indices{{syn, 0}};
        res.setSynIndices(indices);

    } else if (leftRootType == RootType::Integer && rightRootType == RootType::Integer) { // Parent*(1,2)
        Statement s1 = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
        Statement s2 = Statement(stoi(rightRef.getRep()), StatementType::Stmt);
        res.setBoolResult(pkbReader->isParentStar(s1, s2));

    } else if (leftRootType == RootType::Integer && rightRootType == RootType::Wildcard) { // Parent*(1,_)
        Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
        res.setBoolResult(pkbReader->hasChildStarStmt(s));

    } else if (leftRootType == RootType::Wildcard && rightRootType == RootType::Integer) { // Parent*(_,1)
        Statement s = Statement(stoi(rightRef.getRep()), StatementType::Stmt);
        res.setBoolResult(pkbReader->hasParentStarStmt(s));

    } else if (leftRootType == RootType::Wildcard && rightRootType == RootType::Wildcard) { // Parent*(_,_)
        res.setBoolResult(pkbReader->hasParentStar());

    }

    return res;
}