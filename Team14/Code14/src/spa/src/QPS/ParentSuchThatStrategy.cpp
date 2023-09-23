#include "ParentSuchThatStrategy.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"

Result ParentSuchThatStrategy::evaluateClause(std::shared_ptr<Clause> clause, std::shared_ptr<PkbReader> pkbReader) const {
    std::shared_ptr<SuchThatClause> suchThat = std::dynamic_pointer_cast<SuchThatClause>(clause);
    Ref leftRef = suchThat->getFirstParam();
    RootType leftRootType = leftRef.getRootType();
    QueryEntityType leftEntityType = leftRef.getEntityType();
    Ref rightRef = suchThat->getSecondParam();
    RootType rightRootType = rightRef.getRootType();
    QueryEntityType rightEntityType = rightRef.getEntityType();
    Result res;

    if (leftRootType == RootType::Synonym && rightRootType == RootType::Synonym) { // Parent(s1,s2)
        std::string leftSyn = leftRef.getRep();
        std::string rightSyn = rightRef.getRep();
        res.setTuples(pkbReader->getParentPair(stmtMap.at(leftEntityType), stmtMap.at(rightEntityType)));

        std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
        res.setSynIndices(indices);

    } else if (leftRootType == RootType::Synonym && rightRootType == RootType::Integer) { // Parent(s,1) // one answer
        std::string syn = leftRef.getRep();
        Statement s = Statement(stoi(rightRef.getRep()), StatementType::Stmt);
        res.setTuples(pkbReader->getParentTypeStmt(stmtMap.at(leftEntityType), s));

        std::unordered_map<std::string, int> indices{{syn, 0}};
        res.setSynIndices(indices);

    } else if (leftRootType == RootType::Synonym && rightRootType == RootType::Wildcard) { // Parent(s,_)
        std::string syn = leftRef.getRep();
        res.setTuples(pkbReader->getParentTypeWildcard(stmtMap.at(leftEntityType)));

        std::unordered_map<std::string, int> indices{{syn, 0}};
        res.setSynIndices(indices);

    } else if (leftRootType == RootType::Integer && rightRootType == RootType::Synonym) { // Parent(1,s)
        std::string syn = rightRef.getRep();
        Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
        res.setTuples(pkbReader->getParentStmtType(s, stmtMap.at(rightEntityType)));

        std::unordered_map<std::string, int> indices{{syn, 0}};
        res.setSynIndices(indices);

    } else if (leftRootType == RootType::Wildcard && rightRootType == RootType::Synonym) { // Parent(_,s)
        std::string syn = rightRef.getRep();
        res.setTuples(pkbReader->getParentWildcardType(stmtMap.at(rightEntityType)));

        std::unordered_map<std::string, int> indices{{syn, 0}};
        res.setSynIndices(indices);

    } else if (leftRootType == RootType::Integer && rightRootType == RootType::Wildcard) { // Parent(1,_)
        Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
        res.setBoolResult(pkbReader->hasChildStmt(s));

    } else if (leftRootType == RootType::Wildcard && rightRootType == RootType::Integer) { // Parent(_,1)
        Statement s = Statement(stoi(rightRef.getRep()), StatementType::Stmt);
        res.setBoolResult(pkbReader->hasParentStmt(s));

    } else if (leftRootType == RootType::Integer && rightRootType == RootType::Integer) { // Parent(1,2)
        Statement s1 = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
        Statement s2 = Statement(stoi(rightRef.getRep()), StatementType::Stmt);
        res.setBoolResult(pkbReader->isParent(s1, s2));

    } else if (leftRootType == RootType::Wildcard && rightRootType == RootType::Wildcard) { // Parent(_,_)
        res.setBoolResult(pkbReader->hasParent());
    }

    return res;
}