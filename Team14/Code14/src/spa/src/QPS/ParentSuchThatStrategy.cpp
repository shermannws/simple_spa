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
    ResultType type;
    std::vector<std::vector<Entity>> tuples;

    if (leftRootType == RootType::Synonym && rightRootType == RootType::Synonym) { // Parent(s1,s2)
        std::string leftSyn = leftRef.getRep();
        std::string rightSyn = rightRef.getRep();
        tuples = pkbReader->getParentPair(stmtMap.at(leftEntityType), stmtMap.at(rightEntityType));

        std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
        res.setSynIndices(indices);

        type = ResultType::Tuples;
    } else if (leftRootType == RootType::Synonym && rightRootType == RootType::Integer) { // Parent(s,1) // one answer
        std::string syn = leftRef.getRep();
        Statement s = Statement(stoi(rightRef.getRep()), StatementType::Stmt);
        auto data = pkbReader->getParentTypeStmt(stmtMap.at(leftEntityType), s);
        tuples.emplace_back(data);

        std::unordered_map<std::string, int> indices{{syn, 0}};
        res.setSynIndices(indices);

        type = ResultType::Tuples;

    } else if (leftRootType == RootType::Synonym && rightRootType == RootType::Wildcard) { // Parent(s,_)
        std::string syn = leftRef.getRep();
        auto data = pkbReader->getParentTypeWildcard(stmtMap.at(leftEntityType));
        for (const auto& ent : data) {
            std::vector<Entity> tuple_vector {ent};
            tuples.emplace_back(tuple_vector);
        }

        std::unordered_map<std::string, int> indices{{syn, 0}};
        res.setSynIndices(indices);

        type = ResultType::Tuples;

    } else if (leftRootType == RootType::Integer && rightRootType == RootType::Synonym) { // Parent(1,s)
        std::string syn = rightRef.getRep();
        Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
        auto data = pkbReader->getParentStmtType(s, stmtMap.at(rightEntityType));
        tuples.emplace_back(data);

        std::unordered_map<std::string, int> indices{{syn, 0}};
        res.setSynIndices(indices);

        type = ResultType::Tuples;

    } else if (leftRootType == RootType::Wildcard && rightRootType == RootType::Synonym) { // Parent(_,s)
        std::string syn = rightRef.getRep();
        auto data = pkbReader->getParentWildcardType(stmtMap.at(rightEntityType));
        for (const auto& ent : data) {
            std::vector<Entity> tuple_vector {ent};
            tuples.emplace_back(tuple_vector);
        }

        std::unordered_map<std::string, int> indices{{syn, 0}};
        res.setSynIndices(indices);

        type = ResultType::Tuples;

    } else if (leftRootType == RootType::Integer && rightRootType == RootType::Wildcard) { // Parent(1,_)
        Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
        res.setBoolResult(pkbReader->hasChildStmt(s));
        type = ResultType::Boolean;

    } else if (leftRootType == RootType::Wildcard && rightRootType == RootType::Integer) { // Parent(_,1)
        Statement s = Statement(stoi(rightRef.getRep()), StatementType::Stmt);
        res.setBoolResult(pkbReader->hasParentStmt(s));
        type = ResultType::Boolean;

    } else if (leftRootType == RootType::Integer && rightRootType == RootType::Integer) { // Parent(1,2)
        Statement s1 = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
        Statement s2 = Statement(stoi(rightRef.getRep()), StatementType::Stmt);
        res.setBoolResult(pkbReader->isParent(s1, s2));
        type = ResultType::Boolean;

    } else if (leftRootType == RootType::Wildcard && rightRootType == RootType::Wildcard) { // Parent(_,_)
        res.setBoolResult(pkbReader->hasParent());
        type = ResultType::Boolean;

    }

    res.setType(type);
    res.setTuples(tuples);
    return res;
}